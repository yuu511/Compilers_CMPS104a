#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

vector<const string*> *all_strings  = new vector <const string*>();
vector<string*> *all_globals  = new vector <string*>();
vector<string*> *all_functions  = new vector <string*>();

string parse_typesize(symbol *sym){
  attr_bitset a = sym->attributes;
  string st = "";
  if (a[static_cast<int>(attr::INT)]){
    st.append("int ");
    return st;
  }
  if (a[static_cast<int>(attr::TYPEID)]){
    st.append ("struct ");
    if (sym -> sname !=nullptr){
      st.append (sym->sname->c_str());
      st.append (" ");
    }
    return st;
  }
  if (a[static_cast<int>(attr::STRING)] || a[static_cast<int>(attr::ARRAY)]){
    st.append ("ptr ");
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
        parse_typesize(itor.second).c_str(),
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

void ac_globalvar(astree *child, unordered_map<const string*, symbol_table*> *master, FILE *out){
  for (size_t i =0; i< child->attributes.size(); i++){
    if (child->attributes[i]){
      switch(i){
        case static_cast<int>(attr::INT):
          if (child->children.size() > 2 ){
            //parse the expr
            // manipulate string for string padding
            string name = child->children[1]->lexinfo->c_str();
            name += ":";
            if (child->children[2]->children.size() == 0){
              fprintf (out,"%-10s .global int %s\n",
                       name.c_str(),
                       child->children[2]->lexinfo->c_str());
            }
            else {
              errprintf ("global variable may not have non-static value assigned to it\n");
            }
          }
          else {
            string name = child->children[1]->lexinfo->c_str();
            name += ":";
            fprintf (out,"%-10s .global int\n",name.c_str());
          }
          break;
        case static_cast<int>(attr::STRING):
          if (child->children.size() > 2 ){
            //parse the expr
            if (child->children[2]->children.size() == 0){
              all_strings->push_back(child->children[2]->lexinfo);
            }
            else {
              errprintf ("global variable may not have non-static value assigned to it\n");
            }
          } else {
            string name = child->children[1]->lexinfo->c_str();
            name += ":";
            fprintf (out,"%-10s .global string\n",name.c_str());
          }
          break;
      }
    }
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
