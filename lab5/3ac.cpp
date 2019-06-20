#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "auxlib.h"

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

void emit_3ac(astree *s, symbol_table *struct_table, 
  unordered_map<const string*,symbol_table*> *master,FILE *out){
  ac_struct(struct_table,out);
}
