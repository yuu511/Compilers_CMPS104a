#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

vector<const string*> *all_strings  = new vector <const string*>();

ac3_table *all_globals = new ac3_table; 

vector<pair<const string*,ac3_table*>> *all_functions = 
new vector<pair<const string*,ac3_table*>>();

unordered_map <symbol_table*, ac3_table*> *table_lookup = 
new unordered_map<symbol_table*, ac3_table*>;

all_tables *master;

void p_stmt(astree *expr, symbol_table *current, string *label);
ac3 *p_expr(astree *expr, symbol_table *current, string *label,const string *init);

// first available reg
int reg_count = -1;
// first while
int while_count = -1;
//first int
int if_count = 0;

reg::reg(const string *ident_){
  ident = ident_; 
  stride = nullptr;
  unop = nullptr;
}

reg::reg(string *stride_, int reg_number_){
  reg_number = reg_number_;
  stride = stride_;
  ident = nullptr;
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
  else {
    ret.append("$t");
    ret.append(to_string(reg_number));
    if (stride){
      ret.append(*stride);
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


// helper function for assignment
ac3 *asg_int(astree *expr, symbol_table *current, string *label){
  astree *ident = expr->children[0];
  astree *assignment = expr->children[1];
  if (expr->symbol == TOK_TYPE_ID){
    ident = expr->children[1];
    assignment = expr->children[2];
  }
  ac3 *ac = p_expr(assignment,current,label,ident->lexinfo);   
  ac->label = label;
  ac->expr = expr;
  return ac;
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
    expr->symbol == TOK_TYPE_ID 
    ? ident = expr->children[1] : ident = expr->children[0]; 
    ac3 *ac =new ac3(expr);
    ac->t0 = new reg(ident->lexinfo);
    ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(ac);
  }
  return nullptr;
}

ac3 *p_binop(astree *expr, symbol_table *current, string *label,const string *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac = new ac3(expr); 
  found->push_back(ac);
  ac->label = label;
  ac->op = expr->lexinfo;
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  // if a varaiable for expr exists, store it in variable
  if (init) 
    ac->t0 = new reg(init);
  // otherwise, store in the first available register.
  else { 
    ac->t0 = new reg(new string(stride_binop(expr,current)),reg_count);
    ++reg_count;
  }
  // parse the expressions
  // check the two children
    if (expr->children[0]->children.size() > 1
        || expr->children[0]->symbol == TOK_CALL){
      string *stride = new string (stride_binop(expr->children[0],current));
      ac->t1 = new reg(stride,reg_count);
      p_expr(expr->children[0],current,label,nullptr);
    } 
    else if (expr->children[0]->children.size() == 1){
      if (expr->children[0]->children[0]->children.size() > 1){
        string *stride = 
          new string(stride_binop(expr->children[0]->children[0],current));
        reg *unary = new reg(stride,reg_count);
        unary->unop = new string(*(expr->children[0]->lexinfo));
        ac->t1 = unary;
        p_expr(expr->children[0]->children[0],current,label,nullptr);
      }
      else {
        reg *unary = new reg(expr->children[0]->children[0]->lexinfo);
        unary->unop = new string(*(expr->children[0]->lexinfo));
        ac->t1 = unary;
      }
    }
    else {
      ac->t1 =new reg(expr->children[0]->lexinfo);
    }

    if (expr->children[1]->children.size() > 1
        || expr->children[1]->symbol == TOK_CALL){
      string *stride = new string (stride_binop(expr->children[1],current));
      ac->t2 = new reg(stride,reg_count);
      p_expr(expr->children[1],current,label,nullptr);
    } 
    else if (expr->children[1]->children.size() == 1){
      if (expr->children[1]->children[0]->children.size() > 1){
        string *stride = 
          new string(stride_binop(expr->children[1]->children[0],current));
        reg *unary = new reg(stride,reg_count);
        unary->unop = new string(*(expr->children[1]->lexinfo));
        ac->t2 = unary;
        p_expr(expr->children[1]->children[0],current,label,nullptr);
      }
      else {
        reg *unary = new reg(expr->children[1]->children[0]->lexinfo);
        unary->unop = new string(*(expr->children[1]->lexinfo));
        ac->t2 = unary;
      }
    }
    else {
      ac->t2 =new reg(expr->children[1]->lexinfo);
    }
    return ac;
}


ac3 *p_unop(astree *expr, symbol_table *current, string *label,const string *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac =new ac3(expr);
  found->push_back(ac);

  // if a varaiable for expr exists, store it in variable
  if (init) 
    ac->t0 = new reg(init);
  // otherwise, store in the first available register.
  else {
    ac->t0 = new reg(new string(":i"),reg_count);
    ++reg_count;
  }
  if (expr->children[0]->children.size() > 1){
    string *stride = new string(stride_binop(expr->children[0],current));
    reg *unary = new reg(stride,reg_count);
    unary->unop = new string(*(expr->lexinfo));
    ac->t1 = unary;
    p_expr(expr->children[0],current,label,nullptr);
  }
  else {
    reg *unary = new reg(expr->children[0]->lexinfo);
    unary->unop = new string(*(expr->lexinfo));
    ac->t1 = unary;
  }
  ac->label = label;
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  return ac;
}

ac3 *p_polymorphic(astree *expr, symbol_table *current, string *label,const string *init){
  if (expr->children.size() > 1){
    return p_binop(expr,current,label,init);
  }
  else if (expr->children.size() == 1) {
    return p_unop(expr,current,label,init);
  }
  // should never happen
  errprintf ("p_polymorphic called on expr with size 0");
  return nullptr;
}

ac3 *p_static_int(astree *expr, symbol_table *current, string *label,const string *init){
  ac3_table *found = table_lookup->find(current)->second;
  ac3 *ac = new ac3(expr); 
  if (init) 
    ac->t0 = new reg(init);
  // otherwise, store in the first available register.
  else 
    ac->t0 = new reg(new string(":i"),reg_count);
  ac->label = label; 
  ac->t1 = new reg(expr->lexinfo);  
  found->push_back(ac);
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  return ac;
}

//ac3 *p_call(astree *expr, symbol_table *current, string *label,const string *init){
//
//}


void p_if(astree *expr, symbol_table *current, string *label){ 
  ac3_table *found = table_lookup->find(current)->second;
}

void p_while(astree *expr, symbol_table *current, string *label){ 
  ++while_count;
  int orig_while = while_count;
  ac3_table *found = table_lookup->find(current)->second;

  // if label exists, this while statement is enclosed within
  // an if or while statement. emit the label to encapsulate this while.
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
  astree *condition = expr->children[0];
  astree *block = expr->children[1];
  // parse expression, get regsister of return
  
  ac3 *while_expr = p_expr(condition,current,wh_header,nullptr);
  reg *stored;
  if (while_expr && while_expr->t0){
    if (while_expr->t0->stride && while_expr->t0->reg_number){
      stored = while_expr->t0;
    }
    else {
      errprintf ("invalid expression passed in while loop"); 
      return;
    }
  } 
  else {
    errprintf("invalid expression passed in while loop");
    return;
  }

  /* goto statement */
  reg *ret = new reg(new string(*(stored->stride)),stored->reg_number);
  ret->unop = stored->unop;
  ac3 *wh_goto = new ac3 (condition,ret); 
  wh_goto->label = new string(goto_label);
  wh_goto->itype.set(static_cast<int>(instruction::GOTO));
  found->push_back(wh_goto);

  /* first statement */
  string *first_label = new string(".do" + to_string(orig_while) + ":");
  if (block->children.size() > 0){
    p_stmt(block->children[0],current,first_label); 
    // parse the rest of the statements
    for (size_t i = 1; i < block->children.size(); ++i){
      p_stmt(block->children[i],current,nullptr);
    }
  } 
  else {
    ac3 *vacuous_while = new ac3(block);
    vacuous_while->label = first_label;
    vacuous_while->itype.set(static_cast<int>(instruction::LABEL_ONLY));
    found->push_back(vacuous_while);
  }

  /* loop statment */
  ac3 *loop_stmt = new ac3 (block);
  loop_stmt->label = new string(while_label);
  loop_stmt->itype.set(static_cast<int>(instruction::GOTO));
  found->push_back(loop_stmt);

  /* while end label */
  ac3 *closing_stmt = new ac3(expr);
  closing_stmt->label = new string(goto_label + ":");
  closing_stmt->itype.set(static_cast<int>(instruction::LABEL_ONLY));
  found->push_back(closing_stmt);
}


// return expression will be init if init not nullptr,
// else assign the return to a register
ac3 *p_expr(astree *expr, symbol_table *current, string *label,const string *init){
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
      return p_binop(expr,current,label,init);
      break;
    case '+':
    case '-':
      return p_polymorphic(expr,current,label,init);
      break;
    case TOK_NOT:
      return p_unop(expr,current,label,init);
      break;
    case TOK_CHARCON:
    case TOK_INTCON:
      return p_static_int(expr,current,label,init);
      break;
    // case TOK_CALL:
    //   return p_call(expr,current,label,init);
    //   break;
  }
  errprintf ("non-recognized expression parsed:%s \n "
             , parser::get_tname(expr->symbol));
  ac3 *ac = new ac3(expr);
  return ac;
}

// return the first statement generated by the functions.
void p_stmt(astree *expr, symbol_table *current, string *label){
  switch (expr->symbol){
    case '=':
      p_assignment(expr,current,label);
      break;
    case TOK_TYPE_ID:
      // ignore non-init vardecl e.g. int x;
      if (expr->children.size() > 2)
        p_assignment(expr,current,label);
      break;
    case TOK_IF:
      p_if(expr,current,label);
      break;
    case TOK_WHILE:
      p_while(expr,current,label);
      break;
    default:
      p_expr(expr,current,label,nullptr);
      break;
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
    i++;
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
                 stmt->label ? stmt->label->c_str()    : "",
                 stmt->t0 ? "if not" : "" ,
                 stmt->t0 ? stmt->t0->str().c_str() : "" );
      }
      if (stmt->itype[static_cast<int>(instruction::LABEL_ONLY)]){
        // [LABEL]
        fprintf (out,"%s\n", stmt->label ? stmt->label->c_str() : "");
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
        for (astree *stmt: child->children[2]->children) p_stmt(stmt,found,nullptr);
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

