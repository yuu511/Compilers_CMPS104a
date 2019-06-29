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

ac3 *p_stmt(astree *expr, symbol_table *current, string label);

// first available reg
int reg_count = -1;

reg::reg(string *ident_){
  ident = ident_; 
  stride = nullptr;
}

reg::reg(string *stride_, int reg_number_){
  reg_number = reg_number_;
  stride = stride_;
  ident = nullptr;
}

string reg::str(){
  string ret="";
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
  delete ident;
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
  delete op;
  delete t1;
  delete t2;
}

ac3::ac3 (astree *expr_,reg *t0_ ){
  expr = expr_;
  t0 = t0_;
  label = new string ("");
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

// given a binop, return a stride
string get_stride(astree *expr,symbol_table *current){
  // default: :i
  string ret = ":i";
  astree *left = expr->children[0];
  switch(left->symbol){
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
      symbol *type_l = master->global->find(left->children[0]->lexinfo)->second;
      if (type_l->attributes[static_cast<int>(attr::INT)])
        ret = "i";
      if (type_l->attributes[static_cast<int>(attr::CHAR)])
        ret = "c";
      if (type_l->attributes[static_cast<int>(attr::TYPEID)] ||
          type_l->attributes[static_cast<int>(attr::STRING)] ||
	  type_l->attributes[static_cast<int>(attr::ARRAY)])
        ret = "p";
    }
      break;
    case TOK_IDENT: {
      symbol *ident_l;
      if(master->global->count(left->lexinfo)){
        ident_l = master->global->find(left->lexinfo)->second;
      }
      if(current->count(left->lexinfo)){
        ident_l = current->find(left->lexinfo)->second;
      }
      if (ident_l->attributes[static_cast<int>(attr::INT)])
        ret = "i";
      if (ident_l->attributes[static_cast<int>(attr::CHAR)])
        ret = "c";
      if (ident_l->attributes[static_cast<int>(attr::TYPEID)] ||
          ident_l->attributes[static_cast<int>(attr::STRING)] ||
	  ident_l->attributes[static_cast<int>(attr::ARRAY)])
        ret = "p";
    }
      break;
  }

  astree *right = expr->children[1];
  switch(right->symbol){
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
    case TOK_NE: {
      ret = ":i";
    }
      break;

    case TOK_CHARCON: {
      ret = ":c";
    }
      break;
      
    case TOK_STRINGCON:
    case TOK_NULLPTR:
    case TOK_ALLOC:
    case TOK_INDEX:
    case TOK_ARROW: {
      ret = ":p";
    }
      break;
    case TOK_CALL: {
      symbol *type_r = master->global->find(right->children[0]->lexinfo)->second;
      if (type_r->attributes[static_cast<int>(attr::INT)])
        ret = "i";
      if (type_r->attributes[static_cast<int>(attr::CHAR)])
        ret = "c";
      if (type_r->attributes[static_cast<int>(attr::TYPEID)] ||
          type_r->attributes[static_cast<int>(attr::STRING)] ||
	  type_r->attributes[static_cast<int>(attr::ARRAY)])
        ret = "p"; 
    }
      break;
    case TOK_IDENT: {
      symbol *ident_r;
      if(master->global->count(right->lexinfo)){
        ident_r = master->global->find(right->lexinfo)->second;
      }
      if(current->count(right->lexinfo)){
        ident_r = current->find(right->lexinfo)->second;
      }
      if (ident_r->attributes[static_cast<int>(attr::INT)])
        ret = "i";
      if (ident_r->attributes[static_cast<int>(attr::CHAR)])
        ret = "c";
      if (ident_r->attributes[static_cast<int>(attr::TYPEID)] ||
          ident_r->attributes[static_cast<int>(attr::STRING)] ||
	  ident_r->attributes[static_cast<int>(attr::ARRAY)])
        ret = "p";
   }
      break;
  }
  return ret;
}


// helper function for assignment
ac3 *asg_int(astree *expr, symbol_table *current, string label){
  ac3_table *found = table_lookup->find(current)->second;
  astree *ident = expr->children[0];
  astree *assignment = expr->children[1];
  ac3 *ac = new ac3(expr);
  if (expr->symbol == TOK_TYPE_ID){
    ident = expr->children[1];
    assignment = expr->children[2];
  }
  // parse the expressions
  // check the two children
  if (assignment->children.size() > 1){
    string *t0 = new string(*(ident->lexinfo));   
    ac->t0 = new reg(t0);
    // must parse
    if (assignment->children[0]->children.size() > 1){
      string *stride = new string (get_stride(assignment->children[0],current));
      ac->t1 = new reg(stride,reg_count);
      p_stmt(assignment->children[0],current,"");
      ++reg_count;
    } 
    else {
      string *t1 = new string(*(assignment->children[0]->lexinfo)); 
      ac->t1 =new reg(t1);
    }
    if (assignment->children[1]->children.size() > 1){
      string *stride = new string (get_stride(assignment->children[1],current));
      ac->t1 = new reg(stride,reg_count);
      p_stmt(assignment->children[1],current,"");
      ++reg_count;
    } 
    else {
      string *t2 = new string(*(assignment->children[1]->lexinfo)); 
      ac->t2 =new reg(t2);
    }
    ac->op = new string(*(assignment->lexinfo));
  }
  // case of a single assignment e.g. x = 5;
  else {
    string *t0 = new string(*(ident->lexinfo));   
    string *t1 = new string(*(assignment->lexinfo));
    ac->t0 = new reg(t0);
    ac->t1 = new reg(t1);
  }
  *(ac->label) = label;
  ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
  found->push_back(ac);
  return ac;
}

// if 'tok_type_id'  it's an variable declaration
// else if '=' it's an assignment
ac3 *p_assignment(astree *expr, symbol_table *current, string label){
  ac3_table *found = table_lookup->find(current)->second;
  // a typeid can have no assignment (int x, for example)
  size_t min = 1;
  astree *ident = expr->children[0];
  if (expr->symbol == TOK_TYPE_ID){
    ident = expr->children[1];
    min = 2;
  }
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
  else {
    string *name = new string (*(ident->lexinfo));
    ac3 *ac = new ac3(expr,new reg(name));
    ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(ac);
    return ac;
  }
  return nullptr;
}

ac3 *p_binop(astree *expr, symbol_table *current, string label){

}

// return the first statement generated by the functions.
ac3 *p_stmt(astree *expr, symbol_table *current, string label){
  switch (expr->symbol){
    case '=':
    case TOK_TYPE_ID:
      return p_assignment(expr,current,label);
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case TOK_EQ:
    case TOK_NE:
    case TOK_LT:
    case TOK_LE:
    case TOK_GT:
    case TOK_GE:
      return p_binop(expr,current,label);



    default:
      ac3 *ac = new ac3(expr);
      return ac;
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
  p_assignment(child,table->global,"");
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
          string label = "";
          string t0="";
          string t1="";
          string op="";
          string t2="";
          if (stmt->label) label = *(stmt->label);
          if (stmt->t0) t0 = stmt->t0->str();
          if (stmt->t1) t1 = stmt->t1->str();
          if (stmt->op) op = *(stmt->op);
          if (stmt->t2) t2 = stmt->t2->str();
          fprintf(out,"%-10s %s = %s %s %s\n",
                      label.c_str(),
                      t0.c_str(),
                      t1.c_str(),
                      op.c_str(),
                      t2.c_str());
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
      } else {
        errprintf ("3ac: invalid function definition. Stopping address code generation \n");
	return;
      }
      // no duplicate functions
      if (found!=nullptr && !(table_lookup->count(found))){
        ac3_table *new_function = new ac3_table;
	table_lookup->emplace(found,new_function);
	all_functions->push_back(make_pair(name->lexinfo,new_function));
        reg_count = 0;
        for (astree *stmt: child->children[2]->children) p_stmt(stmt,found,"");
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

