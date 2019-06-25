#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

vector<const string*> *all_strings  = new vector <const string*>();
ac3_table *all_globals = new ac3_table; 

vector<pair<const string*,ac3_table*>> *all_functions 
= new vector<pair<const string*,ac3_table*>>();

unordered_map <symbol_table*, ac3_table*> *table_lookup = 
new unordered_map<symbol_table*, ac3_table*>;

ac3::ac3(symbol *sym_, astree *expr_){
  sym = sym_;
  expr = expr_;
}

ac3::~ac3(){
  delete ret;
  delete op;
  delete t1;
  delete t2;
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

void emit_struct(all_tables *table,FILE *out){
  if (table->struct_t == nullptr){
    errprintf("ac_struct called on null struct_table");
    return;
  }
  for (auto itor: *(table->struct_t)){
    translate_struct(itor.first,itor.second,out);  
  }
}

// requires the typeid to be parsed,
// and symbol table containing the 
// context of the variable to be parsed in question
void parse_initialization(astree *child,symbol_table *current){
  ac3_table *found = table_lookup->find(current)->second;
  astree *ident_node = child->children[1];
  string name = ident_node->lexinfo->c_str();
  name += ":";
  attr_bitset a = child->attributes;
  ac3 *ac;
  if (child->children.size() > 2 ){
    astree *assignment = child->children[2];
    string *ret = new string();
    string *t1 = new string();
    symbol *sym;
    if (a[static_cast<int>(attr::ARRAY)]){
      if (assignment->symbol == TOK_ALLOC){
          
      }
      else if (assignment->symbol == TOK_NULLPTR){
        t1->append(assignment->lexinfo->c_str());
      }
      ret->append(ident_node->lexinfo->c_str());
      sym = current->find(ident_node->lexinfo)->second;
      ac = new ac3(sym,child);
      ac->ret = ret;
      ac->t1 = t1;
      ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(ac);
      return;
    }
    if (a[static_cast<int>(attr::TYPEID)]){
      if (assignment->symbol == TOK_ALLOC){
        t1->append("call malloc (");   
        t1->append("sizeof struct ");
        t1->append(assignment->children[0]->lexinfo->c_str());
        t1->append(")");
      }
      else if (assignment->symbol == TOK_NULLPTR){
        t1->append(assignment->lexinfo->c_str());
      }
      ret->append(ident_node->lexinfo->c_str());
      sym = current->find(ident_node->lexinfo)->second;
      ac = new ac3(sym,child);
      ac->ret = ret;
      ac->t1 = t1;
      ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(ac);
      return;
    }
    if (a[static_cast<int>(attr::STRING)]){
      if (assignment->symbol == TOK_ALLOC){
        if (assignment->children.size() == 2){
          if (assignment->children[1]->children.size() > 0){

          }
          else {
            assignment = child->children[2]->children[1];   
            return;
          }
        }
      }
      else if (assignment->symbol == TOK_NULLPTR) {
        t1->append(assignment->lexinfo->c_str());
      }
      else if (assignment->symbol == TOK_STRINGCON) {
        t1->append("(.s");
        t1->append(to_string(all_strings->size()));
        t1->append(")");
        all_strings->push_back(assignment->lexinfo);
      }
      ret->append(ident_node->lexinfo->c_str());
      sym = current->find(ident_node->lexinfo)->second;
      ac = new ac3(sym,child);
      ac->ret = ret;
      ac->t1 = t1;
      ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(ac);
      return;
    }
    if (a[static_cast<int>(attr::INT)]){
      if (assignment->children.size() > 2){
        // parse the expr
      } 
      else {
        t1->append(assignment->lexinfo->c_str());
      }
      ret->append(ident_node->lexinfo->c_str());
      sym = current->find(ident_node->lexinfo)->second;
      ac = new ac3(sym,child);
      ac->ret = ret;
      ac->t1 = t1;
      ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
      found->push_back(ac);
      return;
    }
  }
  else {
    symbol *sym = current->find(ident_node->lexinfo)->second;
    ac = new ac3(sym,child); 
    string *ret = new string();
    ret->append(ident_node->lexinfo->c_str());
    ac->ret = ret;
    ac->itype.set(static_cast<int>(instruction::ASSIGNMENT));
    found->push_back(ac);
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
  parse_initialization(child,table->global);
}

void ac_function (astree *child, symbol_table *found){
  ac3_table *current = table_lookup->find(found)->second;
}

//emit all string constants.
void emit_string(FILE *out){
  int i = 0;
  for (auto itor: *all_strings){
    fprintf (out,".s%d%-7s %s\n",i,":",itor->c_str());
    i++;
  }
}

void emit_globaldef(FILE *out){
  for (auto itor: *all_globals){
    string name = *(itor->ret);
    name += ":";
    fprintf (out,"%-10s .%s %s",
             name.c_str(),
             "global",
             parse_typesize(itor->sym).c_str());
    if (itor->t1 !=nullptr){
      fprintf (out,"%s",itor->t1->c_str());
    }
    fprintf (out,"\n");
  }
}

void emit_functions(all_tables *table, FILE *out){
  // print out all functions
  for (auto itor: *all_functions){
    symbol *ret = table->global->find(itor.first)->second;
    string fname;
    fname.append(itor.first->c_str());
    fname.append(":");
    //print out the function header    
    fprintf(out,"%-10s .function %s\n",
    fname.c_str(), parse_typesize(ret).c_str()); 
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
    else if (child->symbol == TOK_FUNCTION 
             && !(child->attributes[static_cast<int>(attr::PROTOTYPE)])) {
      // else process the function (non-prototype)
      astree *name = child->children[0]->children[1];
      symbol_table *found = table->master->find(name->lexinfo)->second;
      // no duplicate functions
      if (found!=nullptr && !(table_lookup->count(found))){
        ac3_table *new_function = new ac3_table;
	table_lookup->emplace(found,new_function);
	all_functions->push_back(make_pair(name->lexinfo,new_function));
        ac_function(child,found);
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

void emit_3ac(astree *s, all_tables *table, FILE *out){
  table_lookup->emplace(table->global,all_globals);
  ac_traverse(s,table,out);
}
