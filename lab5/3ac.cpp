#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"
#include <algorithm>

// quick lookup between a function's symbol table and 3ac statements
unordered_map <symbol_table*, ac3_table*> *table_lookup =  new unordered_map<symbol_table*, ac3_table*>;

// all symbol tables (generated in previous module symbol_table.cpp)
all_tables *all_sym;

// all 3ac tables
all_3ac *all_ac;

/* global counters for registers and labels */
int reg_count, while_count, if_count = 0;
int err_count = 0;

void p_stmt(astree *expr, symbol_table *current, string *label);
ac3 *p_expr(astree *expr, symbol_table *current);

// 1. identifier
reg::reg(const string *ident_){
  ident = ident_; 
  index = -1;
  parameters = nullptr;
  typesize = nullptr;
  field = nullptr;
  name = nullptr;
  selection_index = nullptr;
  unop = nullptr;
}

// 2. temp register
reg::reg(string *stride, int reg_number_){
  ident = nullptr;
  index = reg_number_;
  parameters = nullptr;
  typesize = nullptr;
  field = nullptr;
  name = stride;
  selection_index = nullptr;
  unop = nullptr;
}

// 3. function
reg::reg(string *fname, vector<reg*> *parameters_){
  ident = nullptr;
  index = -1;
  parameters= parameters_;
  typesize = nullptr;
  field = nullptr;
  name = fname;
  selection_index = nullptr;
  unop = nullptr;
}

// 4. typesize
reg::reg(string *typesize_, string *szof){
  ident = nullptr;
  index = -1;
  parameters = nullptr;
  typesize = typesize_;
  field = nullptr;
  name = nullptr;
  selection_index = nullptr;
  unop = szof;
}

// 5. string ptr
reg::reg(int string_index_){
  ident = nullptr;
  index = string_index_;
  parameters = nullptr;
  typesize = nullptr;
  field = nullptr;
  name = nullptr;
  selection_index = nullptr;
  unop = nullptr;
}

// 7. selection
reg::reg(reg *selection_index_,const string *sname_, const string *field_){
  ident = sname_;
  index = -1;
  parameters = nullptr;
  typesize = nullptr;
  field = field_;
  name = nullptr;
  selection_index = selection_index_;
  unop = nullptr;
}

string reg::str(){
  string ret="";
  if (unop != nullptr){
    ret.append(*unop);
    //add space (for readability)
    if (*unop == "sizeof" ||
        *unop == "not"){
      ret.append(" ");
    }
  }
  if (ident){
    ret.append(*ident);
  }
  else if (index != -1 && name){
    ret.append("$t");
    ret.append(to_string(index));
    ret.append(*name);
  }
  else if (parameters && name){
    ret.append("call ");
    ret.append(*name);
    ret.append("(");
    if (parameters->size() > 0){
      ret.append(parameters->at(0)->str());
      for (size_t i = 1; i < parameters->size(); i++){
        ret.append(",");
        ret.append(parameters->at(i)->str());
      }
    }
    ret.append(")");
  } 
  else if (typesize){
    ret.append(*typesize);
  }
  else if (index != -1){
    ret.append("(.s");
    ret.append(to_string(index));
    ret.append(")");
  }
  else if (selection_index && ident && field){
    ret.append(selection_index->str());
    ret.append("->");
    ret.append(*ident);
    ret.append(".");
    ret.append(*field);
  }
  return ret;
}

reg::~reg(){
  if (parameters){
    for (auto itor : *parameters){
      delete itor;
    }
  }
  delete parameters;
  delete typesize;
  delete name;
  delete selection_index;
  delete unop;
}

reg *reg::deep_copy(){
  reg *r= new reg(ident);  
  r->index = index;
  if (parameters){
    r->parameters = new vector<reg*>();
    for (auto itor: *parameters){
      r->parameters->push_back(itor->deep_copy());
    }
  }
  if (typesize) r->typesize = new string(*typesize);
  r->field = field;
  if (name) r-> name = new string (*name);
  if (selection_index) r-> selection_index = selection_index->deep_copy();
  if (unop) r->unop = new string(*unop);
  return r;
}

all_3ac::all_3ac(ac3_table *all_globals_, 
               vector<pair<const string*,ac3_table*>> *all_functions_,
               vector<const string*> *all_strings_){
  all_globals = all_globals_;
  all_functions = all_functions_;
  all_strings = all_strings_;
}

void free_3ac(){
  delete table_lookup;
  if (all_ac){
    for (auto itor : *(all_ac->all_functions)){
      for (auto itor2: *itor.second) {
        delete itor2; 
      }
      delete itor.second;
    }
    for (auto itor: *(all_ac->all_globals)){
      delete itor;
    }
    delete all_ac->all_globals;
    delete all_ac->all_functions;
    delete all_ac->all_strings;
    delete all_ac;
  }
}

ac3::~ac3(){
  delete label;
  delete t0;
  delete op;
  delete t1;
  delete t2;
}

ac3::ac3 (astree *expr_,reg *t0_ ){
  expr = expr_;
  t0 = t0_;
  label = nullptr;
  op = nullptr;
  t1 = nullptr;
  t2 = nullptr;
}

// parse types of either symbol or astree
template <class Type> string parse_typesize(const Type &o){ 
  attr_bitset a = o->attributes;
  const string *sname = o->sname;
  string st = "";
  if (a[static_cast<int>(attr::TYPEID)]){
    st.append ("struct ");
    if (sname != nullptr){
      st.append (sname->c_str());
      st.append (" ");
    }
    return st;
  }
  if (a[static_cast<int>(attr::STRING)] || a[static_cast<int>(attr::ARRAY)]){
    st.append ("ptr ");
    return st;
  }
  if (a[static_cast<int>(attr::INT)]){
    st.append("int ");
    return st;
  }
  // void return
  return st;
}

// parse expression, and return a register that it is stored in
reg *expr_reg (astree *expr, symbol_table *current){
  ac3 *parsed_expr  = p_expr(expr,current);
  if (parsed_expr && parsed_expr->t0){
    return parsed_expr->t0->deep_copy(); 
  }
  else {
    errprintf("3ac: invalid expression passed in loop\n");
    ++err_count;
    return nullptr;
  }
  return nullptr;
}

// recurse down until you find a non-equals symbol,return it
astree *recurse_non_equal(astree *expr){
  if (expr->symbol == '='){
    return recurse_non_equal(expr->children[1]);
  }
  return expr;
}

// special helper function for astree_stride for index only
string *astree_stride_symbol_index(symbol *found){
  if (found->attributes[static_cast<int>(attr::STRING)]){
    return new string (":c");
  }
  else if (found->attributes[static_cast<int>(attr::TYPEID)]){
    return new string (":p");
  }
  else if (found->attributes[static_cast<int>(attr::INT)]){
    return new string (":i");
  }
  ++err_count;
  errprintf ("3ac: Invalid symbol parsed for astree_stride_symbol_index");
  return nullptr;
}

//helper function for astree_stride
string *astree_stride_symbol_array(symbol *found){
  if ( found->attributes[static_cast<int>(attr::ARRAY)]
      || found->attributes[static_cast<int>(attr::STRING)]
      || found->attributes[static_cast<int>(attr::TYPEID)]){
      return new string(":p");
  } 
  else if (found->attributes[static_cast<int>(attr::CHAR)]){
    return new string (":c");
  } 
  else if (found->attributes[static_cast<int>(attr::INT)]){
    return new string(":i");
  }
  ++err_count; 
  errprintf ("3ac: Invalid symbol parsed for astree_stride_symbol_array\n");
  return nullptr;
}

// parse an astree expression for a expr stride
string *astree_stride(symbol_table *current,astree *expr){
  symbol *found = nullptr;
  switch (expr->symbol){
    case TOK_CHARCON:
      return new string(":c");
    case TOK_STRINGCON:
    case TOK_NULLPTR:
    case TOK_ALLOC:
      return new string(":p");
    case TOK_INTCON:
    case TOK_LT:
    case TOK_LE:
    case TOK_GT:
    case TOK_GE:
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
    case TOK_NOT:
    case TOK_EQ:
    case TOK_NE:
      return new string(":i");
    case TOK_IDENT:
      if (current->count(expr->lexinfo))
        found = current->find(expr->lexinfo)->second;
      else if (all_sym->global->count(expr->lexinfo))
        found = all_sym->global->find(expr->lexinfo)->second;
      return astree_stride_symbol_array(found);
    case TOK_CALL:
      // find function definition in global table
      found = all_sym->global->find(expr->children[0]->lexinfo)->second;
      return astree_stride_symbol_array(found);
    case TOK_INDEX:
      // if(current->count(expr->children[0]->lexinfo))
      //   found = current->find(expr->children[0]->lexinfo)->second;
      // else if (all_sym->global->count(expr->children[0]->lexinfo))
      //   found = all_sym->global->find(expr->children[0]->lexinfo)->second;
      // return astree_stride_symbol_index(found);
      return new string(":c");
    case TOK_ARROW:
      // get symbol of struct
      found = all_sym->struct_t->find(expr->sname)->second;
      // get symbol of struct parameter
      found = found->fields->find(expr->children[1]->lexinfo)->second;
      return astree_stride_symbol_array(found);
    case '=':
      astree *noneq = recurse_non_equal(expr);
      return astree_stride(current,noneq);
  }
  errprintf ("3AC: INVALID EXPR parsed in astree_stride\n");
  ++err_count;
  return nullptr;
}

reg *parse_variable(astree *expr, symbol_table *current){
  reg *selection = nullptr;
  if (expr->children.size()){
    if (expr->symbol == TOK_ARROW){
      reg *ret; 
      if (expr->children[0]->children.size()){
        ret = new reg(astree_stride(current,expr->children[0]),reg_count);
        p_expr(expr->children[0],current);
      }
      else {
        ret = new reg(expr->children[0]->lexinfo);
      }
      selection = new reg(ret,expr->sname,expr->children[1]->lexinfo);
    }
    else if (expr->symbol == TOK_INDEX){

    }
  }
  else
    selection = new reg(expr->lexinfo);
  return selection;
}

// assign int to ident
ac3 *asg_int(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  // bot of statements
  ac3 *bot;
  // get index of top of statements
  size_t top = found->size();

  astree *ident = expr->symbol == TOK_TYPE_ID ? expr->children[1] : expr->children[0];
  astree *parse = expr->symbol == TOK_TYPE_ID ? expr->children[2] : expr->children[1];

  if (parse->children.size()){  
    bot = new ac3(expr);
    reg *bot_reg = expr_reg(parse,current);
    if (bot_reg){
      bot->t0 = parse_variable(ident,current);
      bot->t1 = bot_reg;
      bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(bot);
      found->at(top)->label = label; 
    }
    else {
      errprintf ("3ac: parsing expr failed: %s \n",expr->lexinfo->c_str());
      ++err_count;
      return nullptr;
    }
  }
  else {
    bot = new ac3(expr);
    bot->t0 = parse_variable(ident,current);
    bot->t1 = new reg(parse->lexinfo);
    bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(bot);
    found->at(top)->label = label; 
  }
  return bot;
}

// gets the typesize for an ALLOC array call
// and allocs a string representation
string *alloc_array_typesize(astree *expr){
  string *ret = new string();
  astree *type = expr->children[0]->children[0];
  switch (type->symbol){
    case TOK_INT:
      ret->append("int");
      break;
    case TOK_STRING:
      ret->append("ptr");
      break;
    case TOK_PTR:
      ret->append("struct ");
      ret->append(*(type->children[0]->lexinfo));
      break;
  }
  return ret;
}

ac3 *alloc_array(astree *expr,symbol_table *current, reg *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot = new ac3(expr);
  ac3 *parsed_sz = new ac3(expr);
  reg *malloc_number;
  astree *alloc_sz = expr->children[1];
  // the size to malloc (stored in a reg)
  reg *ret = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;
  parsed_sz->t0 = ret;  
  if (alloc_sz->children.size()){
    malloc_number = expr_reg(alloc_sz,current);
  } 
  else {
    malloc_number = new reg(alloc_sz->lexinfo);
  }
  parsed_sz->t1 = malloc_number;
  parsed_sz->op = new string("*");
  parsed_sz->t2 = new reg(alloc_array_typesize(expr),new string("sizeof"));
  parsed_sz->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(parsed_sz);

  // malloc function call
  vector<reg*> *malloc_params = new vector <reg*>();
  malloc_params->push_back(ret->deep_copy());
  bot->t0 = init;
  bot->t1 = new reg(new string ("malloc"),malloc_params);
  bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(bot);
  return bot;
}

ac3 *alloc_struct(astree *expr,symbol_table *current, reg *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot = new ac3(expr);
  vector <reg*> *malloc_params = new vector<reg*>();
  string *struct_name = new string("struct " + *(expr->children[0]->lexinfo));
  malloc_params->push_back(new reg(struct_name,new string("sizeof")));
  bot->t0 = init;
  bot->t1 = new reg(new string("malloc"),malloc_params);
  bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(bot);
  return bot;
}

ac3 *alloc_string(astree *expr,symbol_table *current, reg *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot = new ac3(expr);
  reg *malloc_number;
  astree *alloc_sz = expr->children[1];
  vector <reg*> *malloc_params = new vector<reg*>();
  if (alloc_sz->children.size()){
    malloc_number = expr_reg(alloc_sz,current);
  }
  else {
    malloc_number = new reg(alloc_sz->lexinfo);
  }
  malloc_params->push_back(malloc_number);
  bot->t0 = init;
  bot->t1 = new reg(new string("malloc"),malloc_params);
  bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(bot);
  return bot;
}

ac3 *asg_array(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot;
  size_t top = found->size();

  astree *ident = expr->symbol == TOK_TYPE_ID ? expr->children[1] : expr->children[0];
  astree *parse = expr->symbol == TOK_TYPE_ID ? expr->children[2] : expr->children[1];

  if (parse->children.size()){
    if (parse->symbol == TOK_ALLOC){
      reg *ret = new reg(ident->lexinfo);
      bot = alloc_array(parse,current,ret);
      found->at(top)->label = label;
    }
    else {
      reg *ret_reg = expr_reg(parse,current);
      bot = new ac3(expr);
      bot->t0 = parse_variable(ident,current);
      bot->t1 = ret_reg;
      bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(bot);
      found->at(top)->label = label;
    }
  }
  else {
    bot = new ac3(expr);
    bot->t0 = parse_variable(ident,current);
    bot->t1 = new reg(parse->lexinfo);
    bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(bot);
    found->at(top)->label = label;
  }
  return bot;
}

ac3 *asg_struct(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot;
  size_t top = found->size();

  astree *ident = expr->symbol == TOK_TYPE_ID ? expr->children[1] : expr->children[0];
  astree *parse = expr->symbol == TOK_TYPE_ID ? expr->children[2] : expr->children[1];

  if (parse->children.size()){
    if (parse->symbol == TOK_ALLOC){
      reg *ret = new reg(ident->lexinfo);
      bot = alloc_struct(parse,current,ret);
      found->at(top)->label = label;
    }
    else {
      reg *ret_reg = expr_reg(parse,current);
      bot = new ac3(expr);
      bot->t0 = parse_variable(ident,current);
      bot->t1 = ret_reg;
      bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(bot);
      found->at(top)->label = label;
    }
  }
  else {
    bot = new ac3(expr);
    bot->t0 = parse_variable(ident,current);
    bot->t1 = new reg(parse->lexinfo);
    bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(bot);
    found->at(top)->label = label;
  }
  return bot;
}

reg *p_string_reg(astree *expr){
  reg *t1;
  vector<const string*>::iterator it;
  it = find(all_ac->all_strings->begin(),all_ac->all_strings->end(),expr->lexinfo);
  if (it != all_ac->all_strings->end()){
    t1 = new reg(it - all_ac->all_strings->begin()); 
  }
  else {
    t1 = new reg(all_ac->all_strings->size());
    all_ac->all_strings->push_back(expr->lexinfo);
  }
  return t1;
}

ac3 *p_string (astree *expr, symbol_table *current, reg *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot = new ac3(expr);
  bot->t0 = init;
  bot->t1 = p_string_reg(expr);
  bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(bot);
  return bot;
}

ac3 *asg_string(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot;
  size_t top = found->size();

  astree *ident = expr->symbol == TOK_TYPE_ID ? expr->children[1] : expr->children[0];
  astree *parse = expr->symbol == TOK_TYPE_ID ? expr->children[2] : expr->children[1];

  if (parse->children.size()){
    if (parse->symbol == TOK_ALLOC){
      reg *ret = new reg(ident->lexinfo);
      bot = alloc_string(parse,current,ret);
      found->at(top)->label = label;
    }
    else {
      reg *ret_reg = expr_reg(parse,current);
      bot = new ac3(expr);
      bot->t0 = parse_variable(ident,current);
      bot->t1 = ret_reg;
      bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(bot);
      found->at(top)->label = label;
    }
  }
  else {
    if (parse->symbol == TOK_STRINGCON){
      bot = p_string(parse,current,parse_variable(ident,current));
      found->at(top)->label = label;
    }
    else {
      bot = new ac3(expr);
      bot->t0 = parse_variable(ident,current);
      bot->t1 = new reg(parse->lexinfo);
      bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(bot);
      found->at(top)->label = label;
    }
  }
  return bot;
}

// check type, and call approriate parsing function
ac3 *asg_check_type(astree *expr, symbol_table *current, string *label){
  attr_bitset a = expr->attributes;
  if (a[static_cast<int>(attr::ARRAY)]){
    return asg_array(expr,current,label);
  }
  if (a[static_cast<int>(attr::TYPEID)]){
    return asg_struct(expr, current,label);
  }
  if (a[static_cast<int>(attr::STRING)]){
    return asg_string(expr,current,label);
  }
  if (a[static_cast<int>(attr::INT)]){
    return asg_int(expr,current,label);
  }
  errprintf ("3ac: Type not found for assignment \n");
  ++err_count;
  return nullptr;
}

// if 'tok_type_id'  it's an variable declaration
// else if '=' it's an assignment
ac3 *p_assignment(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ret = nullptr;
  if (expr->children.size() > (expr->symbol == TOK_TYPE_ID ? 2 : 1)){
    ret = asg_check_type(expr,current,label);
    return ret;
  }  
  // lone declaration e.g. int x;
  // only for global variables: 
  // we won't process local definitions (already done by the symbol table)
  else {
    astree *ident;
    expr->symbol == TOK_TYPE_ID ? ident = expr->children[1] : ident = expr->children[0]; 
    ac3 *ac =new ac3(expr);
    ac->t0 = new reg(ident->lexinfo);
    ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(ac);
  }
  return nullptr;
}

ac3 *p_binop(astree *expr, symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac = new ac3(expr); 
  ac->op = new string(*(expr->lexinfo));
  ac->t0 = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;
  // parse the expressions
  // check the two children
  astree *left = expr->children[0];
  if (left->children.size()) {
    ac->t1 = new reg(astree_stride(current,left),reg_count);
    p_expr(left,current);
  } 
  else {
    ac->t1 =new reg(left->lexinfo);
  }
  
  astree *right = expr->children[1];
  if (right->children.size()){
    ac->t2 = new reg(astree_stride(current,right),reg_count);
    p_expr(right,current);
  } 
  else {
    ac->t2 =new reg(right->lexinfo);
  }
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(ac);
  return ac;
}

ac3 *p_unop(astree *expr, symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac =new ac3(expr);
  ac->t0 = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;

  astree *assignment = expr->children[0];
  if (assignment->children.size()){
    reg *unary = new reg(astree_stride(current,assignment),reg_count);
    unary->unop = new string(*(expr->lexinfo));
    ac->t1 = unary;
    p_expr(assignment,current);
  }
  else {
    reg *unary = new reg(assignment->lexinfo);
    unary->unop = new string(*(expr->lexinfo));
    ac->t1 = unary;
  }
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(ac);
  return ac;
}

ac3 *p_polymorphic(astree *expr, symbol_table *current){
  if (expr->children.size() > 1){
    return p_binop(expr,current);
  }
  else if (expr->children.size() == 1) {
    return p_unop(expr,current);
  }
  // should never happen
  errprintf("3ac :p_polymorphic called on expr with size 0\n");
  ++err_count;
  return nullptr;
}

ac3 *p_static_val(astree *expr, symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac = new ac3(expr); 
  ac->t0 = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;
  ac->t1 = new reg(expr->lexinfo);  
  found->push_back(ac);
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  return ac;
}

ac3 *p_call(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  size_t index = found->size();
  ac3 *bot = new ac3(expr);
  vector <reg*> *args = new vector <reg*>();
  if (expr->children.size() > 1){
    for (size_t i = 1; i < expr->children.size(); i++){
      reg *push;
      if (expr->children[i]->children.size()){
        reg *stored = expr_reg(expr->children[i],current);
        if (stored){
          push = stored;
	    }
        else {
          errprintf ("3ac: return expression incorrectly parsed!\n");
          ++err_count;
          return nullptr;
        }
      } 
      else {
        push = new reg(expr->children[i]->lexinfo);  
      }
      args->push_back(push);
    }
    reg *fname = new reg(new string (*(expr->children[0]->lexinfo)),args);
    bot->t1 = fname; 
  } 
  else {
    reg *fname = new reg(new string (*(expr->children[0]->lexinfo)),args);
    bot->t1 = fname;
  }
  bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(bot);
  found->at(index)->label = label;
  return bot;
}

ac3 *p_arrow(astree *expr, symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *bot = new ac3(expr);
  bot->t0 = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;
  reg *ret; 
  if (expr->children[0]->children.size()){
    ret = new reg(astree_stride(current,expr->children[0]),reg_count);
    p_expr(expr->children[0],current);
  }
  else {
    ret = new reg(expr->children[0]->lexinfo);
  }
  reg *selection = new reg(ret,expr->sname,expr->children[1]->lexinfo);
  bot->t1 = selection;
  bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(bot);
  return bot;
}

// extra arguments for function call as an expression
ac3 *p_string_expr (astree *expr, symbol_table *current){
  // store function call in register
  reg *ret = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;
  ac3 *str = p_string(expr,current,ret);  
  return str;
}

// extra arguments for function call as an expression
ac3 *p_call_expr (astree *expr, symbol_table *current){
  // store function call in register
  reg *ret = new reg(astree_stride(current,expr),reg_count);
  ++reg_count;
  ac3 *call = p_call(expr,current,nullptr);  
  if (call)
    call->t0 = ret;
  else{
    errprintf("3ac: call not parsed correctly\n");
    ++err_count;
  }
  return call;
}

// check validity of loop condition
int check_loop_validity (astree *s){
  if (s == nullptr)
    return 0;
  switch (s->symbol){
    case TOK_EQ:
    case TOK_NE:
    case TOK_GT:
    case TOK_GE:
    case TOK_LT:
    case TOK_LE:
    case TOK_NOT:
    case TOK_IDENT:
    case TOK_INTCON:
    case TOK_CHARCON:
    case TOK_NULLPTR:
      return 1;
  }
  return 0;
}

ac3 *p_if(astree *expr, symbol_table *current, string *label){ 
  astree *condition = expr->children[0];
  astree *if_statement = expr->children[1];
  if (!check_loop_validity(condition)){
    errprintf("3ac: invalid expr in loop!\n");
    ++err_count;
    return nullptr;
  }
  int orig_if = if_count;
  ++if_count;
  ac3_table *found = table_lookup->find(current)->second;

  // if label exists, this if statement is enclosed within
  // another if or while statement. emit the label to encapsulate this if.
  if (label){
    ac3 *encapsulate = new ac3(expr);
    encapsulate->label = label;
    encapsulate->itype.set(static_cast<int>(instruction::LABEL_ONLY));
    found->push_back(encapsulate);
  }
 
  /* if header */
  size_t top = found->size();
  string *if_header = new string(".if" + to_string(orig_if) + ":");
  // if an else statement exists, then we must go to it.
  // otherwise, just go to the end of the if statment.
  string selection;
  expr->children.size() > 2 ? selection = ".el" : selection = ".fi"; 
  string goto_label = selection + to_string(orig_if);
  reg *stored = expr_reg(condition,current);

  // add label to element at saved index
  found->at(top)->label = if_header;

  /* goto statement */
  reg *ret = stored;
  ac3 *if_goto = new ac3 (condition,ret); 
  if_goto->label = new string(goto_label);
  if_goto->itype.set(static_cast<int>(instruction::GOTO));
  found->push_back(if_goto);

  /* first statement */
  string *first_label = new string(".th" + to_string(orig_if) + ":");
  p_stmt(if_statement,current,first_label);

  /* else parsing */
  string exit_label = ".fi" + to_string(orig_if);
  // if there is an else block
  if (expr->children.size() > 2){
    // emit the goto for the case that the if statement is true
    ac3 *if_true = new ac3 (expr->children[1]);
    if_true->label = new string(exit_label);
    if_true->itype.set(static_cast<int>(instruction::GOTO));
    found->push_back(if_true);
    // emit the else statement alternative
    string *else_label = new string (goto_label + ":");
    astree *else_statement = expr->children[2];
    p_stmt(else_statement,current,else_label);
  }

  /* emit ending label */
  ac3 *closing_stmt = new ac3(expr);
  closing_stmt->label = new string(exit_label + ":");
  closing_stmt->itype.set(static_cast<int>(instruction::LABEL_ONLY));
  found->push_back(closing_stmt);

  return closing_stmt;
}


ac3 *p_while(astree *expr, symbol_table *current, string *label){ 
  astree *condition = expr->children[0];
  astree *statement = expr->children[1];
  // check validity of expression in loop condition
  if (!check_loop_validity(condition)){
    errprintf("3ac: invalid expr in loop!\n");
    ++err_count;
    return nullptr;
  }

  int orig_while = while_count;
  ++while_count;
  ac3_table *found = table_lookup->find(current)->second;

  // if label exists, this while statement is enclosed within
  // another if or while statement. emit the label to encapsulate this while.
  if (label){
    ac3 *encapsulate = new ac3(expr);
    encapsulate->label = label;
    encapsulate->itype.set(static_cast<int>(instruction::LABEL_ONLY));
    found->push_back(encapsulate);
  }

  /* while header */
  string while_label = ".wh" + to_string(orig_while);
  string goto_label = ".od" + to_string(orig_while);

  string *wh_header = new string(while_label + ":");
  // get next index
  size_t top = found->size();
  reg *stored = expr_reg(condition,current);

  // add label to element at saved index
  found->at(top)->label = wh_header;

  /* goto statement */
  reg *ret = stored;
  ret->unop = stored->unop;
  ac3 *wh_goto = new ac3 (condition,ret); 
  wh_goto->label = new string(goto_label);
  wh_goto->itype.set(static_cast<int>(instruction::GOTO));
  found->push_back(wh_goto);

  /* first statement */
  string *first_label = new string(".do" + to_string(orig_while) + ":");
  p_stmt(statement,current,first_label); 

  /* loop statment */
  ac3 *loop_stmt = new ac3 (statement);
  loop_stmt->label = new string(while_label);
  loop_stmt->itype.set(static_cast<int>(instruction::GOTO));
  found->push_back(loop_stmt);

  /* while end label */
  ac3 *closing_stmt = new ac3(expr);
  closing_stmt->label = new string(goto_label + ":");
  closing_stmt->itype.set(static_cast<int>(instruction::LABEL_ONLY));
  found->push_back(closing_stmt);
  return closing_stmt;
}

// equals in the context of an expr
ac3 *p_equals(astree *expr, symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac = new ac3(expr);
  astree *left = expr->children[0];
  ac->t0 = parse_variable(left,current);
  astree *right = expr->children[1];
  // find first non-equal symbol
  astree *final_val = recurse_non_equal(right);
  if (right->children.size()){
    if (final_val->children.size()){
      ac->t1 = new reg(astree_stride(current,final_val),reg_count);
      p_expr(right,current);
    } 
    else {
      if (final_val->symbol == TOK_STRINGCON){
        ac->t1 = p_string_reg(final_val);
        p_expr(right,current);
      } 
      else {
        ac->t1 = new reg(final_val->lexinfo);
        p_expr(right,current);
      }
    }
  } 
  else {
    if (right->symbol == TOK_STRINGCON){
      ac->t1 = p_string_reg(right);
    }
    else {
      ac->t1 =new reg(right->lexinfo);
    }
  }
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(ac);
  return ac;
}

// helper function for p_alloc (for cases where alloc is part of an expression)
ac3 *p_alloc(astree *expr, symbol_table *current){
  reg *ret = new reg (astree_stride(current,expr),reg_count);
  ++reg_count;
  switch (expr->children[0]->symbol){
    case TOK_ARRAY:
      return alloc_array(expr,current,ret);
    case TOK_IDENT:
      return alloc_struct(expr,current,ret);
    case TOK_STRING:
      return alloc_string(expr,current,ret);
  }
  errprintf("3AC: p_alloc failed: SYMBOL:%s\n");
  ++err_count;
  return nullptr;
}

void p_block(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  if (expr->children.size()){
    p_stmt(expr->children[0],current,label); 
    // parse the rest of the statements
    for (size_t i = 1; i < expr->children.size(); ++i){
      p_stmt(expr->children[i],current,nullptr);
    }
  }
  else{
    if (label){
      ac3 *vacuous_block = new ac3(expr);
      vacuous_block->label = label;
      vacuous_block->itype.set(static_cast<int>(instruction::LABEL_ONLY));
      found->push_back(vacuous_block);
    }
  }
}

ac3 *p_return(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  size_t top = found->size();
  ac3 *bot;
  if (expr->children.size()){
    astree *assignment = expr->children[0];
    bot = new ac3(expr);
    if (assignment->children.size()){
      reg *stored = expr_reg(assignment,current);
      if (stored)
        bot->t0 = stored;
      else {
        errprintf ("3ac: return expression incorrectly parsed!");
        ++err_count;
	    return nullptr;
      }
    }
    else {
      bot->t0 = new reg(assignment->lexinfo);
    }
    bot->itype.set(static_cast<int>(instruction::RETURN));
    found->push_back(bot);
    found->at(top)->label = label;
  } 
  else {
    bot = new ac3(expr);
    bot->itype.set(static_cast<int>(instruction::RETURN));
    found->push_back(bot);
    found->at(top)->label = label;
  }
  return bot;
}

// large switch statement for expressions
ac3 *p_expr(astree *expr, symbol_table *current){
  switch (expr->symbol){
    case '=':
      return p_equals(expr,current);
      break;
    case '*':
    case '/':
    case '%':
    case TOK_EQ:
    case TOK_NE:
    case TOK_LT:
    case TOK_LE:
    case TOK_GT:
    case TOK_GE:
      return p_binop(expr,current);
      break;
    case '+':
    case '-':
      return p_polymorphic(expr,current);
      break;
    case TOK_NOT:
      return p_unop(expr,current);
      break;
    case TOK_CHARCON:
    case TOK_INTCON:
    case TOK_NULLPTR:
    case TOK_IDENT:
      return p_static_val(expr,current);
      break;
    case TOK_STRINGCON:
      return p_string_expr(expr,current); 
      break;
    case TOK_CALL:
      return p_call_expr(expr,current);
      break;
    case TOK_ALLOC:
      return p_alloc(expr,current);
      break;
    case TOK_ARROW:
      return p_arrow(expr,current);
      break;
  }
  errprintf ("3ac: non-recognized expression parsed:%s \n "
             , parser::get_tname(expr->symbol));
  ++err_count;
  return nullptr;
}

//helper function for p_expr (for cases where expressions are parsed without assignment)
ac3 *p_expression(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  size_t index = found->size();
  ac3 *ac = p_expr(expr,current);
  if(ac)
    found->at(index)->label = label;
  fprintf (stderr, "3ac: warning: expr parsed without assignment: %s:\n",expr->lexinfo->c_str()); 
  return ac;
}

// parse a statement
void p_stmt(astree *expr, symbol_table *current, string *label){
  ac3 *ac = nullptr;
  switch (expr->symbol){
    case TOK_BLOCK:
      p_block(expr,current,label);
      return;
    case '=':
      ac = p_assignment(expr,current,label);
      break;
    case TOK_TYPE_ID:
      // ignore non-init vardecl e.g. int x;
      if (expr->children.size() > 2)
        ac = p_assignment(expr,current,label);
      else if (expr->children.size() == 2)
        return;
      break;
    case TOK_IF:
      ac = p_if(expr,current,label);
      break;
    case TOK_WHILE:
      ac = p_while(expr,current,label);
      break;
    case TOK_RETURN:
      ac = p_return(expr,current,label);
      break;
    case TOK_CALL:
      ac = p_call(expr,current,label);
      break;
    default:
      ac = p_expression(expr,current,label);
      break;
  }
  if (!ac){
    errprintf ("3ac: invalid statement passed :%s\n",expr->lexinfo->c_str());
    ++err_count;
    return;
  }
}

void ac_globalvar(astree *child, all_tables *table){
  if (child->children.size() > 2){
    astree *assignment = child->children[2];
    if (assignment->symbol == TOK_ALLOC){
      if (child->children[0]->symbol != TOK_PTR){
        errprintf ("3ac: global variable may not have non-static value assigned to it\n");
        ++err_count;
        return;
      }
    }
    else if (assignment->children.size()){
      errprintf ("3ac: global variable may not have non-static value assigned to it\n");
      ++err_count;
      return;
    }
  }
  p_assignment(child,table->global,nullptr);
}

// helper function for emit struct
void translate_struct (const string *name, symbol *sym, FILE *out){
  if (sym == nullptr ){
    errprintf ("3ac: invalid symbol for parsing structs\n");
    ++err_count;
    return;
  }
  fprintf(out, ".struct %s\n",name->c_str());
  if (sym->fields != nullptr){
    for (auto itor: *(sym->fields)){
      fprintf (out,".field %s%s\n", 
        parse_typesize(itor.second).c_str(),
        itor.first->c_str());
    }
  }
  fprintf (out, ".end \n");
}

// // emit structs
void emit_struct(FILE *out){
  if (all_sym->struct_t == nullptr){
    errprintf("3ac: ac_struct called on null struct_table\n");
    ++err_count;
    return;
  }
  for (auto itor: *(all_sym->struct_t)){
    translate_struct(itor.first,itor.second,out);  
  }
}
 
// emit string constants here
void emit_string(FILE *out){
  int i = 0;
  for (auto itor: *(all_ac->all_strings)){
    fprintf (out,".s%d%-7s %s\n",i,":",itor->c_str());
    ++i;
  }
}
 
// emit global definitions here
void emit_globaldef(FILE *out){
  for (auto itor: *(all_ac->all_globals)){
    string name = *(itor->t0->ident);
    name += ":";
    fprintf (out,"%-10s %s %s",
             name.c_str(),
             ".global",
             parse_typesize(itor->expr).c_str());
    if (itor->t1 !=nullptr){
      fprintf (out,"%s",itor->t1->str().c_str());
    }
    fprintf (out,"\n");
  }
}

void emit_functions(FILE *out){
  // print out all functions
  for (auto itor: *(all_ac->all_functions)){
    // get symbol associated with function and
    // symbol table associated with functions block
    symbol *type = all_sym->global->find(itor.first)->second;
    symbol_table *block = all_sym->master->find(itor.first)->second;
    
    // function name
    string fname;
    fname.append(itor.first->c_str());
    fname.append(":");
     
    //print out the function header    
    fprintf(out,"%-10s .function %s\n",
            fname.c_str(), 
	        parse_typesize(type).c_str()); 
     
    //print out the function params and variables
    string f_vlabel = ".param";
    for (size_t i = 0; i < block->size(); i++){
      for (auto itor2: *block){
         // params should come before variables by design, 
            // so only check for when the transition arrives
         if (itor2.second->sequence == i){
           if (itor2.second->attributes[static_cast<int>(attr::LOCAL)]){
             f_vlabel = ".local";
           }
           fprintf (out,"%-10s %s %s%s\n",
                    "",
                    f_vlabel.c_str(),
                    parse_typesize(itor2.second).c_str(),
                    itor2.first->c_str());
           continue;
         }
      }
    }
    // fetch statements associated with function
    ac3_table *found;
    if (table_lookup->count(block))
      found = table_lookup->find(block)->second;
    else{
      errprintf ("3ac: ac3 table not found for function %s\n",fname.c_str());
      ++err_count;
      continue;
    }
    // print them
    for (auto stmt: *found){
      if (stmt->itype[static_cast<int>(instruction::ASSIGNMENT)]){
          // [LABEL] T0 = T1 OPERATOR T2
          // = only appears if t1 exists
          fprintf(out,"%-10s %s%s%s %s %s\n",
                  stmt->label ? stmt->label->c_str() : "",
                  stmt->t0 ? stmt->t0->str().c_str() : "" ,
                  stmt->t1 && stmt->t0 ? " = " : "",
                  stmt->t1 ? stmt->t1->str().c_str() : "",
                  stmt->op ? stmt->op->c_str() : "",
                  stmt->t2 ? stmt->t2->str().c_str() : "");
      }
      if (stmt->itype[static_cast<int>(instruction::GOTO)]){
        // goto [LABEL] if not [t0]
        // if not appears only if t0 exists
        fprintf (out,"%-10s goto %s%s%s\n",
                 "",
                 stmt->label ? stmt->label->c_str() : "",
                 stmt->t0 ? " if not " : "" ,
                 stmt->t0 ? stmt->t0->str().c_str() : "" );
      }
      if (stmt->itype[static_cast<int>(instruction::LABEL_ONLY)]){
        // [LABEL]
        fprintf (out,"%s\n", stmt->label ? stmt->label->c_str() : "");
      }
      if (stmt->itype[static_cast<int>(instruction::RETURN)]){
        // return [EXPR]
	    fprintf (out, "%-10s return %s\n",
	         stmt->label ? stmt->label->c_str() : "",
	         stmt->t0 ? stmt->t0->str().c_str(): "" );
      }
    }
    //print out the ending statements
    fprintf (out,"%-10s return\n","");
    fprintf (out,"%-10s .end\n","");
  }
}


void ac_traverse(astree *s){
  for (astree *child: s->children){
    if (child->symbol == TOK_TYPE_ID){
      // process the global variable
      ac_globalvar(child,all_sym);
    }
    // else process the function
    // ensure the function is valid, and not a prototype
    else if (child->symbol == TOK_FUNCTION 
             && !(child->attributes[static_cast<int>(attr::PROTOTYPE)])
             && all_sym->global->count(child->children[0]->children[1]->lexinfo)){
      astree *name = child->children[0]->children[1];
      symbol_table *found;
      // find symbol table associated with function
      if (all_sym->master->find(name->lexinfo) != all_sym->master->end()){
        found = all_sym->master->find(name->lexinfo)->second;
      } 
      else {
        errprintf ("3ac: invalid function definition. Stopping address code generation \n");
        ++err_count;
	    return;
      }
      // no duplicate functions
      if (found!=nullptr && !(table_lookup->count(found))){
        ac3_table *new_function = new ac3_table;
	    table_lookup->emplace(found,new_function);
	    all_ac->all_functions->push_back(make_pair(name->lexinfo,new_function));
        reg_count = 0;
        p_stmt(child->children[2],found,nullptr);
        // for (astree *stmt: child->children[2]->children) p_stmt(stmt,found,nullptr);
      }
      else {
        errprintf("3ac: function already defined\n");
        ++err_count;
      }
    }
  }
}

all_3ac *return_3ac(){
  return all_ac;
}

void emit_all3ac(FILE *out){
  emit_struct(out);
  emit_string(out);
  emit_globaldef(out);
  emit_functions(out);
}

int generate_3ac(astree *root, all_tables *table){
  if (root == nullptr || table == nullptr){
    errprintf ("3ac: parse failed, or invalid table"
    "stopping generation of assembly\n");
    ++err_count;
    return 1;
  }
  all_sym = table;
  // all string constants used
  vector<const string*> *all_strings  = new vector <const string*>();
  // all globals
  ac3_table *all_globals = new ac3_table; 
  // all function
  vector<pair<const string*,ac3_table*>> *all_functions = 
  new vector<pair<const string*,ac3_table*>>();
 
  // link global symbol table with blobal statement table
  table_lookup->emplace(table->global,all_globals);
  all_ac = new all_3ac(all_globals,all_functions,all_strings);
  ac_traverse(root);
  if (err_count){
    errprintf ("NUMBER OF ERRORS REPORTED: %d\n",err_count);
    return 1;
  }
  return 0;
}

