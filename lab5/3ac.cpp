#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

vector<string> *all_strings  = new vector <string>();

string parse_typesize(symbol *sym){
  attr_bitset a = sym->attributes;
  string st = "";
  if (a[static_cast<int>(attr::INT)]){
    st.append("int ");
    return st;
  }
  if (a[static_cast<int>(attr::STRING)] || a[static_cast<int>(attr::ARRAY)]){
    st.append ("ptr ");
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
  fprintf (out, "\n");
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
            if (child->children[2]->children.size() == 0){
              fprintf (out,"%s: .global int %s\n",
                       child->children[1]->lexinfo->c_str(),
                       child->children[2]->lexinfo->c_str());
            }
            else {
              errprintf ("global variable may not have non-static value assigned to it\n");
            }
          }
          else {
            fprintf (out,"%s: .global int\n",child->children[1]->lexinfo->c_str());
          }
          break;
        case static_cast<int>(attr::STRING):
          if (child->children.size() > 2 ){

          } else {
            
          }
          break;
      }
    }
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
}

void emit_3ac(astree *s, symbol_table *struct_table, unordered_map<const string*,symbol_table*> *master,FILE *out){
  ac_struct(struct_table,out);
  ac_traverse(s,master,out);
}
