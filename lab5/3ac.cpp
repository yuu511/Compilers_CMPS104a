#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

vector<const string*> *all_strings  = new vector <const string*>();
vector<string*> *all_globals  = new vector <string*>();
vector<string*> *all_functions  = new vector <string*>();

// parse types of either symbol or astree
// kind of turned into a mess because you need
// a structure name for structure types.
string parse_typesize(symbol *sym,astree *ast){ 
  // xnor (throws an error if both nullptr or pointer exists for both)
  if (!(sym) == !(ast)){
    errprintf ("parse_typesize called incorrectly");
  }
  attr_bitset a;
  const string* sname;
  sym == nullptr ? (a = ast->attributes, sname = ast->sname)  : (a = sym->attributes, sname = sym->sname);
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
        parse_typesize(itor.second,nullptr).c_str(),
        itor.first->c_str());
    }
  }
  fprintf (out, ".end \n");
}

void ac_struct(symbol_table *struct_table,FILE *out){
  if (struct_table == nullptr){
    errprintf("ac_struct called on null struct_table");
    return;
  }
  for (auto itor: *struct_table){
    translate_struct(itor.first,itor.second,out);  
  }
}

void parse_assignment(astree *child, FILE *out,string label){
  astree *ident_node = child->children[1];
  string name = ident_node->lexinfo->c_str();
  name += ":";
  attr_bitset a = child->attributes;
  astree *assignment = child->children[2];
  if (child->children.size() > 2 ){
    if (a[static_cast<int>(attr::ARRAY)]){
    }
    if (a[static_cast<int>(attr::TYPEID)]){
    }
    if (a[static_cast<int>(attr::STRING)]){
      if (child->children[2]->symbol == TOK_ALLOC){
        if (child->children[2]->children.size() == 2){
          if (child->children[2]->children[1]->children.size() > 0){

          }
          else {
            assignment = child->children[2]->children[1];   
            fprintf (out,"%-10s %s %smalloc(%s)\n",
                     name.c_str(),
                     label.c_str(),
                     parse_typesize(nullptr,child).c_str(),
                     assignment->lexinfo->c_str());
             return;
          }
        }
      }
      else {
        
      }
    }
    if (a[static_cast<int>(attr::INT)]){
      if (assignment->children.size() > 2){
        // parse the expr
      } 
      else {
        fprintf (out,"%-10s %s %s%s\n",
                 name.c_str(),
                 label.c_str(),
                 parse_typesize(nullptr,child).c_str(),
                 assignment->lexinfo->c_str());
      }
      return;
    }
  }
  else {
    fprintf (out,"%-10s .%s %s\n",
             name.c_str(),
             label.c_str(),
             parse_typesize(nullptr,child).c_str());
  }
}

void ac_globalvar(astree *child, unordered_map<const string*, symbol_table*> *master, FILE *out){
  if (child->children.size() > 2){
    if (child->children[2]->children.size() == 0){
      parse_assignment(child,out,".global");
    }
    else {
      if (child->children[2]->symbol == TOK_ALLOC){
        if (child->children[2]->children.size() == 2){
         if (child->children[2]->children[1]->children.size() != 0){
           errprintf ("global variable may not have non-static value assigned to it\n");
           return;
         }
        }
      }
      parse_assignment(child,out,".global");
    }
  }
  else {
    parse_assignment(child,out,".global");
  }
}

//emit all string constants.
void emit_string(FILE *out){
  int i = 0;
  for (auto itor: *all_strings){
    fprintf (out,".s%d%-7s %s\n",i,":",itor->c_str());
    i++;
  }
}

void ac_traverse(astree *s, unordered_map<const string*, symbol_table*> *master, FILE *out){
  if ( s == nullptr || master == nullptr || out == nullptr ){
    errprintf("ac_traverse called on uninitialized structure!\n");
    return;
  }
  for (astree *child: s->children){
    if (child->symbol == TOK_TYPE_ID){
      // process the global variable
      ac_globalvar(child,master,out);
    }
    else {
      // else process the function
    }
  }
  // emit string constants here
  emit_string(out);
}

void emit_3ac(astree *s, symbol_table *struct_table, unordered_map<const string*,symbol_table*> *master,FILE *out){
  ac_struct(struct_table,out);
  ac_traverse(s,master,out);
}

void free_3ac(){
  delete(all_strings);
  delete(all_globals);
  delete(all_functions);
}
