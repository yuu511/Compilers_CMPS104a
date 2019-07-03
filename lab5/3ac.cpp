#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

// all string constants used
vector<const string*> *all_strings  = new vector <const string*>();

ac3_table *all_globals = new ac3_table; 

vector<pair<const string*,ac3_table*>> *all_functions = 
new vector<pair<const string*,ac3_table*>>();

// for quick O(1) lookup between a function's
// symbol table and 3ac representation
unordered_map <symbol_table*, ac3_table*> *table_lookup = 
new unordered_map<symbol_table*, ac3_table*>;

// all symbol tables (generated in previous module symbol_table.cpp)
all_tables *master;

// first available reg (resets with function)
int reg_count = -1;
// first while
int while_count = 0;
// first if
int if_count = 0;

void p_stmt(astree *expr, symbol_table *current, string *label);
ac3 *p_expr(astree *expr, symbol_table *current);

reg::reg(const string *ident_){
  ident = ident_; 
  reg_number = -1;
  stride = nullptr;
  fname = nullptr;
  parameters = nullptr;
  unop = nullptr;
}

reg::reg(string *stride_, int reg_number_){
  reg_number = reg_number_;
  stride = stride_;
  ident = nullptr;
  fname = nullptr;
  parameters = nullptr;
  unop = nullptr;
}

reg::reg(string *fname_, vector<reg*> *parameters_){
  fname = fname_;
  parameters= parameters_;
  ident = nullptr;
  reg_number = -1;
  stride = nullptr;
  unop = nullptr;
}

string reg::str(){
  string ret="";
  if (unop != nullptr){
    ret.append(*unop);
  }
  if (ident != nullptr){
    ret.append(*ident);
  }
  else if (reg_number != -1) {
    ret.append("$t");
    ret.append(to_string(reg_number));
    if (stride){
      ret.append(*stride);
    }
  }
  else if (fname != nullptr){
    if (parameters){
      ret.append(*fname);
      ret.append("(");
      for (auto itor: *parameters){
        ret.append(itor->str());
	ret.append(",");
      }
      ret.append(")");
    } 
    else {
      ret.append("(" + *fname + ")");
    }
  }
  return ret;
}

reg::~reg(){
  delete stride;
  delete unop;
}

void free_3ac(){
  for (auto itor : *table_lookup){
    for( auto itor2: *itor.second){
      delete itor2;
    }
    delete itor.second;
  }
  delete table_lookup;
  delete all_functions;
  delete all_strings;
}

ac3::~ac3(){
  delete label;
  delete t0;
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

string get_stride(astree *expr,symbol_table *current){
  string ret = "";
  switch(expr->symbol){
    case TOK_INTCON:
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
    case '=':
    case TOK_LT:
    case TOK_LE:
    case TOK_GT:
    case TOK_GE:
    case TOK_NOT:
    case TOK_EQ:
    case TOK_NE:{
      ret = ":i";
    }
      break;
    case TOK_CHARCON:{
      ret = ":c";
    }
      break;
    case TOK_STRINGCON:
    case TOK_NULLPTR:
    case TOK_ALLOC:
    case TOK_INDEX:
    case TOK_ARROW:{
      ret = ":p";
    }
      break;
    case TOK_CALL:{
      symbol *type = master->global->find(expr->lexinfo)->second;
      if (type->attributes[static_cast<int>(attr::INT)])
        ret = ":i";
      if (type->attributes[static_cast<int>(attr::CHAR)])
        ret = ":c";
      if (type->attributes[static_cast<int>(attr::TYPEID)] ||
          type->attributes[static_cast<int>(attr::STRING)] ||
	      type->attributes[static_cast<int>(attr::ARRAY)])
        ret = ":p";
    }
      break;
    case TOK_IDENT: {
      symbol *ident;
      if(master->global->count(expr->lexinfo)){
        ident = master->global->find(expr->lexinfo)->second;
      }
      if(current->count(expr->lexinfo)){
        ident = current->find(expr->lexinfo)->second;
      }
      if (ident->attributes[static_cast<int>(attr::INT)])
        ret = ":i";
      if (ident->attributes[static_cast<int>(attr::CHAR)])
        ret = ":c";
      if (ident->attributes[static_cast<int>(attr::TYPEID)] ||
          ident->attributes[static_cast<int>(attr::STRING)] ||
	  ident->attributes[static_cast<int>(attr::ARRAY)])
        ret = ":p";
    }
      break;
  }
  return ret;
}

// given a binary operation, return a stride
string stride_binop(astree *expr,symbol_table *current){
  string left = get_stride(expr->children[0],current);
  string right = get_stride(expr->children[1],current);
  if (left == ":c" && right == ":c"){
    return ":c";  
  }
  if (left == ":p" && right == ":p"){
    return ":p";
  }
  return ":i";
}

// parse expression, and return a register that it is stored in
reg *expr_reg (astree *expr, symbol_table *current){
  ac3 *parsed_expr  = p_expr(expr,current);
  reg *stored = nullptr;
  if (parsed_expr && parsed_expr->t1){
    if (parsed_expr->t0->stride != nullptr  && parsed_expr->t0->reg_number != -1){
      stored = parsed_expr->t0;
    }
    else {
      errprintf ("expression passed is not a register!");
      return nullptr;
    }
  } 
  else {
    errprintf("invalid expression passed in loop");
    return nullptr;
  }
  return stored;
}

// helper function for assignment
ac3 *asg_int(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  // bot of statements
  ac3 *bot;
  astree *ident;
  astree *parse;
  // get index of top of statements
  size_t top = found->size();

  if (expr->symbol == '='){
    ident = expr->children[0];
    parse = expr->children[1];
  }
  else if (expr->symbol == TOK_TYPE_ID) {
    ident = expr->children[1];
    parse = expr->children[2];
  } 
  else {
    errprintf ("ASSIGNMENT called on non = or TOK_TYPE_ID\n");
    return nullptr;
  }

  if (parse->children.size() > 0){  
    bot = new ac3(expr);
    reg *bot_reg = nullptr;
    ac3 *new_assignment = p_expr(parse,current);   
    if (new_assignment && new_assignment->t0){
      if (new_assignment->t0->stride && new_assignment->t0->reg_number != -1){
        bot_reg = 
 	new reg(new string(*(new_assignment->t0->stride)),new_assignment->t0->reg_number);
      }
      else {
        errprintf("invalid reg for assignment parsed\n");
	return nullptr;
      }
    }
    if (bot_reg){
      bot->t0 = new reg(ident->lexinfo);
      bot->t1 = bot_reg;
      bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(bot);
      found->at(top)->label = label; 
      return new_assignment;
    }
    else {
      errprintf ("parsing expr failed: %s \n",expr->lexinfo->c_str());
      return nullptr;
    }
  }
  else {
    bot = new ac3(expr);
    bot->t0 = new reg(ident->lexinfo);
    bot->t1 = new reg(parse->lexinfo);
    bot->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(bot);
    found->at(top)->label = label; 
  }
  return bot;
}

// if 'tok_type_id'  it's an variable declaration
// else if '=' it's an assignment
ac3 *p_assignment(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  size_t min;
  expr->symbol == TOK_TYPE_ID ? min = 2 : min = 1;
  if (expr->children.size() > min){
    attr_bitset a = expr->attributes;
    if (a[static_cast<int>(attr::ARRAY)]){
      // return asg_array(expr,current,label);
    }
    if (a[static_cast<int>(attr::TYPEID)]){
      // return asg_typeid(expr, current,label);
    }
    if (a[static_cast<int>(attr::STRING)]){
     // return asg_string(expr,current,label);
    }
    if (a[static_cast<int>(attr::INT)]){
      return asg_int(expr,current,label);
    }
  }  
  // only for global variables 
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
  ac->op = expr->lexinfo;
  ac->t0 = new reg(new string (":i"),reg_count);
  ++reg_count;
  // parse the expressions
  // check the two children
  astree *left = expr->children[0];
  if (left->children.size() > 0) {
    ac->t1 = new reg(new string(":i"),reg_count);
    p_expr(left,current);
  } 
  else {
    ac->t1 =new reg(left->lexinfo);
  }
  
  astree *right = expr->children[1];
  if (right->children.size() > 0){
    ac->t2 = new reg(new string(":i"),reg_count);
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
  ac->t0 = new reg(new string(":i"),reg_count);
  ++reg_count;

  astree *assignment = expr->children[0];
  if (assignment->children.size() > 0){
    reg *unary = new reg(new string(":i"),reg_count);
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
  errprintf("p_polymorphic called on expr with size 0");
  return nullptr;
}

ac3 *p_static_int(astree *expr, symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac = new ac3(expr); 
  ac->t0 = new reg(new string(":i"),reg_count);
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
  if (expr->children.size() > 1){
    vector <reg*> *args = new vector <reg*>();
    for (size_t i = 1; i < expr->children.size(); i++){
      reg *push;
      if (expr->children[i]->children.size() > 0){
        reg *stored = expr_reg(expr->children[i],current);
        if (stored){
          push = new reg(new string(*(stored->stride)),stored->reg_number);
	}
        else {
          errprintf ("return expression incorrectly parsed!");
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
    reg *fname = new reg(new string (*(expr->children[0]->lexinfo)));
    bot->t1 = fname;
  }
  bot->itype.set(static_cast<int>(instruction::CALL));
  found->push_back(bot);
  found->at(index)->label = label;
  return bot;
}

// extra arguments for function call as an expression
ac3 *p_call_expr (astree *expr, symbol_table *current){
  // store function call in register
  reg *ret = new reg(new string(":i"),reg_count);
  ++reg_count;
  ac3 *call = p_call(expr,current,nullptr);  
  if (call)
    call->t0 = ret;
  else
    errprintf("call not pared correctly");
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
    errprintf("invalid expr in loop!\n");
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
  reg *ret = new reg(new string(*(stored->stride)),stored->reg_number);
  ret->unop = stored->unop;
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
    errprintf("invalid expr in loop!\n");
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
  reg *ret = new reg(new string(*(stored->stride)),stored->reg_number);
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

// add a label to the expr if it exists.
ac3 *p_expr(astree *expr, symbol_table *current){
  switch (expr->symbol){
    case '=':
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
      return p_static_int(expr,current);
      break;
    case TOK_CALL:
      return p_call_expr(expr,current);
      break;
  }
  errprintf ("non-recognized expression parsed:%s \n "
             , parser::get_tname(expr->symbol));
  return nullptr;
}

void p_block(astree *expr, symbol_table *current, string *label){
  ac3_table *found = table_lookup->find(current)->second;
  if (expr->children.size() > 0){
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
  if (expr->children.size() > 0){
    astree *assignment = expr->children[0];
    bot = new ac3(expr);
    if (assignment->children.size() > 0){
      reg *stored = expr_reg(assignment,current);
      if (stored)
        bot->t0 = new reg(new string(*(stored->stride)),stored->reg_number);
      else {
        errprintf ("return expression incorrectly parsed!");
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

// return the first statement generated by the functions.
void p_stmt(astree *expr, symbol_table *current, string *label){
  ac3 *ac;
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
      ac3_table *found = table_lookup->find(current)->second;
      size_t index = found->size();
      ac = p_expr(expr,current);
      if (ac)
        found->at(index)->label = label;
      break;
  }
  if (!ac){
    errprintf ("invalid statment passed :%s",expr->lexinfo->c_str());
    return;
  }
}

void ac_globalvar(astree *child, all_tables *table){
  if (child->children.size() > 2){
    astree *assignment = child->children[2];
    if (assignment->symbol == TOK_ALLOC){
      if (child->children[0]->symbol != TOK_PTR){
        errprintf ("global variable may not have non-static value assigned to it\n");
        return;
      }
    }
    else if (assignment->children.size()>0){
      errprintf ("global variable may not have non-static value assigned to it\n");
      return;
    }
  }
  p_assignment(child,table->global,nullptr);
}

// helper function for emit struct
void translate_struct (const string *name, symbol *sym, FILE *out){
  if (sym == nullptr ){
    errprintf ("invalid symbol for parsing structs");
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

// emit structs
void emit_struct(all_tables *table,FILE *out){
  if (table->struct_t == nullptr){
    errprintf("ac_struct called on null struct_table");
    return;
  }
  for (auto itor: *(table->struct_t)){
    translate_struct(itor.first,itor.second,out);  
  }
}

// emit string constants here
void emit_string(FILE *out){
  int i = 0;
  for (auto itor: *all_strings){
    fprintf (out,".s%d%-7s %s\n",i,":",itor->c_str());
    ++i;
  }
}

// emit global definitions here
void emit_globaldef(FILE *out){
  for (auto itor: *all_globals){
    string name = *(itor->t0->ident);
    name += ":";
    fprintf (out,"%-10s %s %s",
             name.c_str(),
             ".global",
             parse_typesize(itor->expr).c_str());
    if (itor->t1 !=nullptr){
      fprintf (out,"%s",itor->t1->ident->c_str());
    }
    fprintf (out,"\n");
  }
}

void emit_functions(all_tables *table, FILE *out){
  // print out all functions
  for (auto itor: *all_functions){
    // get symbol associated with function and
    // symbol table associated with functions block
    symbol *type = table->global->find(itor.first)->second;
    symbol_table *block = table->master->find(itor.first)->second;
    
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
      errprintf ("ac3 table not found for function %s",fname.c_str());
      continue;
    }
    // print them
    for (auto stmt: *found){
      if (stmt->itype[static_cast<int>(instruction::ASSIGNMENT)]){
          // [LABEL] T0 = T1 OPERATOR T2
          // = only appears if t1 exists
          fprintf(out,"%-10s %s %s %s %s %s\n",
                  stmt->label ? stmt->label->c_str() : "",
                  stmt->t0 ? stmt->t0->str().c_str() : "" ,
                  stmt->t1 ? "=" : "",
                  stmt->t1 ? stmt->t1->str().c_str() : "",
                  stmt->op ? stmt->op->c_str() : "",
                  stmt->t2 ? stmt->t2->str().c_str() : "");
      }
      if (stmt->itype[static_cast<int>(instruction::GOTO)]){
        // goto [LABEL] if not [t0]
        // if not appears only if t0 exists
        fprintf (out,"%-10s goto %s %s %s\n",
                 "",
                 stmt->label ? stmt->label->c_str() : "",
                 stmt->t0 ? "if not" : "" ,
                 stmt->t0 ? stmt->t0->str().c_str() : "" );
      }
      if (stmt->itype[static_cast<int>(instruction::LABEL_ONLY)]){
        // [LABEL]
        fprintf (out,"%s\n", stmt->label ? stmt->label->c_str() : "");
      }
      if (stmt->itype[static_cast<int>(instruction::RETURN)]){
        // return [EXPR]
	fprintf (out, "%-10s return %s\n",
	         "",
	         stmt->t0 ? stmt->t0->str().c_str(): "" );
      }
      if (stmt->itype[static_cast<int>(instruction::CALL)]){
        // call [FNAME] ( [ [ARG1] , [ARG2] , ... , [ARGN] ] )
	fprintf (out, "%-10s %s%scall %s\n",
	         stmt->label ? stmt->label->c_str() : "",
                 stmt->t0 ? stmt->t0->str().c_str() : "",  
                 stmt->t0 ? " = " : "",  
		 stmt->t1 ? stmt->t1->str().c_str() : "");

      }
    }
    //print out the ending statements
    fprintf (out,"%-10s return\n","");
    fprintf (out,"%-10s .end\n","");
  }
}


void ac_traverse(astree *s, all_tables *table, FILE *out){
  if ( s == nullptr || table == nullptr || out == nullptr ){
    errprintf("ac_traverse called on uninitialized structure!\n");
    return;
  }
  for (astree *child: s->children){
    if (child->symbol == TOK_TYPE_ID){
      // process the global variable
      ac_globalvar(child,table);
    }
    // else process the function
    // ensure the function is valid, and not a prototype
    else if (child->symbol == TOK_FUNCTION 
             && !(child->attributes[static_cast<int>(attr::PROTOTYPE)])
             && table->global->count(child->children[0]->children[1]->lexinfo)){
      astree *name = child->children[0]->children[1];
      symbol_table *found;
      // find symbol table associated with function
      if (table->master->find(name->lexinfo) != table->master->end()){
        found = table->master->find(name->lexinfo)->second;
      } 
      else {
        errprintf ("3ac: invalid function definition. Stopping address code generation \n");
	    return;
      }
      // no duplicate functions
      if (found!=nullptr && !(table_lookup->count(found))){
        ac3_table *new_function = new ac3_table;
	    table_lookup->emplace(found,new_function);
	    all_functions->push_back(make_pair(name->lexinfo,new_function));
        reg_count = 0;
        p_stmt(child->children[2],found,nullptr);
        // for (astree *stmt: child->children[2]->children) p_stmt(stmt,found,nullptr);
      }
      else {
        errprintf("3ac: function already defined\n");
      }
    }
  }
  // emit structs
  emit_struct(table,out);
  // emit string constants here
  emit_string(out);
  // emit global definitions here
  emit_globaldef(out);
  //emit function definitions here
  emit_functions(table,out);
}

void emit_3ac(astree *root, all_tables *table, FILE *out){
  if (root == nullptr || table == nullptr || out == nullptr){
    errprintf ("parse failed, or invalid table or file ptr called,"
    "stopping generation of assembly\n");
    return;
  }
  master = table;
  table_lookup->emplace(table->global,all_globals);
  ac_traverse(root,table,out);
}

