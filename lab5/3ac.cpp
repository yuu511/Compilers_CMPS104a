#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"
#include "auxlib.h"

vector<const string*> *all_strings  = new vector <const string*>();
vector <ac3*> *all_globals = new vector <ac3*>(); 

ac3::ac3(symbol *sym_, astree *expr_){
  sym = sym_;
  expr = expr_;
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

void ac_struct(all_tables *table,FILE *out){
  if (table->struct_t == nullptr){
    errprintf("ac_struct called on null struct_table");
    return;
  }
  for (auto itor: *(table->struct_t)){
    translate_struct(itor.first,itor.second,out);  
  }
}

void parse_assignment(all_tables *table,astree *child, FILE *out,string label){
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
      if (assignment->symbol == TOK_ALLOC){
        if (assignment->children.size() == 2){
          if (assignment->children[1]->children.size() > 0){

          }
          else {
            assignment = child->children[2]->children[1];   
            // fprintf (out,"%-10s %s %smalloc(%s)\n",
            //          name.c_str(),
            //          label.c_str(),
            //          parse_typesize(child).c_str(),
            //          assignment->lexinfo->c_str());
             return;
          }
        }
      }
      else if (assignment->symbol == TOK_NULLPTR) {
        fprintf (out,"%-10s %s %s%s\n",
                 name.c_str(),
                 label.c_str(),
                 parse_typesize(child).c_str(),
                 "0");
        
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
                 parse_typesize(child).c_str(),
                 assignment->lexinfo->c_str());
      }
      return;
    }
  }
  else {
    // fprintf (out,"%-10s .%s %s\n",
    //          name.c_str(),
    //          label.c_str(),
    //          parse_typesize(child).c_str());
  }
}

void ac_globalvar(astree *child, all_tables *table, FILE *out){
  if (child->children.size() > 2){
    astree *assignment = child->children[2];
    if (assignment->children.size() != 0){
      if (assignment->symbol == TOK_ALLOC){
        if (assignment->children.size() == 2){
         if (assignment->children[1]->children.size() != 0){
           errprintf ("global variable may not have non-static value assigned to it\n");
           return;
         }
        }
      }
      else if (assignment->children.size()>0){
        errprintf ("global variable may not have non-static value assigned to it\n");
        return;
      }
    }
  }
  parse_assignment(table,child,out,".global");
}

//emit all string constants.
void emit_string(FILE *out){
  int i = 0;
  for (auto itor: *all_strings){
    fprintf (out,".s%d%-7s %s\n",i,":",itor->c_str());
    i++;
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
      ac_globalvar(child,table,out);
    }
    else {
      // else process the function
    }
  }
  // emit string constants here
  emit_string(out);
  // emit global definitions here

  //emit function definitions here
}

void emit_3ac(astree *s, all_tables *table, FILE *out){
  ac_struct(table,out);
  ac_traverse(s,table,out);
}

void free_3ac(){
}
