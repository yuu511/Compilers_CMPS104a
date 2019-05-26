#include <bitset>
#include <unordered_set>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;
#include "auxlib.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"

vector <symbol_table*> stack;
vector <symbol_table*> master;
symbol_table *struct_t = new symbol_table();
int current_block = 0;
int next_block = 1;

string dump_attributes(attr_bitset a){
  string st;
  for (size_t i = 0; i<a.size();i++){
    if (a[i]){
      switch(i) {
        case static_cast<int>(attr::VOID):
          st.append ("VOID ");
          break;
        case static_cast<int>(attr::INT):
          st.append ("INT ");
          break;
        case static_cast<int>(attr::NULLPTR_T):
          st.append ("NULLPTR_T ");
          break;
        case static_cast<int>(attr::STRING):
          st.append ("STRING ");
          break;
        case static_cast<int>(attr::STRUCT):
          st.append ("STRUCT ");
          break;
        case static_cast<int>(attr::ARRAY):
          st.append ("ARRAY ");
          break;
        case static_cast<int>(attr::FUNCTION):
          st.append ("FUNCTION ");
          break;
        case static_cast<int>(attr::VARIABLE):
          st.append ("VARIABLE ");
          break;
        case static_cast<int>(attr::FIELD):
          st.append ("FIELD ");
          break;
        case static_cast<int>(attr::TYPEID):
          st.append ("TYPEID ");
          break;
        case static_cast<int>(attr::PARAM):
          st.append ("PARAM ");
          break;
        case static_cast<int>(attr::LOCAL):
          st.append ("LOCAL ");
          break;
        case static_cast<int>(attr::LVAL):
          st.append ("LVAL ");
          break;
        case static_cast<int>(attr::CONST):
          st.append ("CONST ");
          break;
        case static_cast<int>(attr::VREG):
          st.append ("VREG ");
          break;
        case static_cast<int>(attr::VADDR):
          st.append ("VADDR ");
          break;
      }
    }
  }
  return st;
}

string dump_table_fields(symbol_table *s){
  string st;
  if (s != nullptr){
      for(auto itor: *s){
         st += dump_attributes(itor.second->attributes); 
         // if ptr (to a struct)
         if (itor.second->attributes[static_cast<int>(attr::STRUCT)]){
           string scc = string(itor.second->sname->c_str());
           st.append(scc); 
           st.append(" ");
         }
         // ident
         st.append(string(itor.first->c_str()));
      }
  }
  return st;
}

void dump_symbol (symbol *sym, FILE* outfile) {
  string f="";
  if (sym->fields != nullptr){
    f = dump_table_fields(sym->fields);
  }
  fprintf (outfile, "->%s\n->%zd\n->%s\n->%zd.%zd.%zd\n->%zd\n->\n",
           dump_attributes(sym->attributes).c_str(),
           sym->sequence, 
           f.c_str(),
           sym->lloc.filenr,sym->lloc.linenr,sym->lloc.offset,
           sym->block_nr);
}

void p_typeid(astree *s){ 
  // symbol *sym = new symbol(s,current_block);
  // if (s->children[3]!=nullptr)
  //   fprintf(stderr,"varaiable declaration!\n");
  // else fprintf(stderr,"no var decl!\n");
}

int type_enum (int t_code){
  switch (t_code) {
    case TOK_VOID:
      return static_cast<int>(attr::VOID);
    case TOK_INT:
      return static_cast<int>(attr::STRING);
    case TOK_STRING:
      return static_cast<int>(attr::INT);
    case TOK_STRUCT:
      return static_cast<int>(attr::STRUCT);
  }
  return -1;
}

void p_struct (astree *s){
  symbol *sym = new symbol(s,0);
  sym->attributes.set(static_cast<int>(attr::STRUCT));
  const string* name = s->children[0]->lexinfo; 

  // add to struct table first, then process fields.
  if (struct_t->find(name)!=struct_t->end()){
    if ((*struct_t)[name]->fields == nullptr){
      struct_t->emplace(name,sym);  
    } 
    else {
      errprintf ("struct %s defined already: %zd.%zd.%zd\n",
                  name->c_str(),sym->lloc.filenr,
                  sym->lloc.linenr,sym->lloc.offset);
    }  
  }
  else {
    struct_t->emplace(name,sym);  
  }
  for (unsigned int i = 1; i < s->children.size(); i++){
    if (sym->fields == nullptr)
      sym->fields = new symbol_table();
    astree *c = s->children[i];
    symbol *f = new symbol(c,0); 
    int t_code;
    const string *id;
    const string *s_name;

    // if a pointer is found, adjust identifier and type code accordingly.
    if (c->children[0]->symbol == TOK_ARRAY){
      f->attributes.set(static_cast<int>(attr::ARRAY));
      if (c->children[0]->children[0]->symbol == TOK_PTR){
        t_code = TOK_STRUCT;
        s_name = c->children[0]->children[0]->children[0]->lexinfo;
        c->sname = f->sname = s_name;
        id = c->children[1]->lexinfo;
      }
      else {
        t_code = c->children[0]->children[0]->symbol;
        id = c->children[1]->lexinfo;
      }
    }
    else {
      if (c->children[0]->symbol == TOK_PTR){
        t_code = TOK_STRUCT;
        s_name = c->children[0]->children[0]->lexinfo;
        c->sname = f->sname = s_name;
        id = c->children[1]->lexinfo;
      }
      else {
        t_code = c->children[0]->symbol;
        id = c->children[1]->lexinfo;
      }
    }
    if (t_code == TOK_VOID){
      errprintf("struct fields may not be void:%zd.%zd.%zd\n",
                  sym->lloc.filenr, sym->lloc.linenr,
                  sym->lloc.offset);
    }
    f->attributes.set(static_cast<int>(attr::FIELD));
    f->attributes.set(type_enum(t_code));
    // checking for multiple fields
    if (sym->fields->find(id)!=sym->fields->end()){
      errprintf("%s defined multiple times in struct %s :%zd.%zd.%zd\n",
                 id, name,
                 sym->lloc.filenr, sym->lloc.linenr,
                 sym->lloc.offset);

    }
    else {
      sym->fields->emplace(id,f);
    }
    // checking pointer validity
    if (f->sname != nullptr){
      if (struct_t->find(s_name)==struct_t->end()){
        errprintf ("struct %s not found in field ptr: %zd.%zd.%zd\n",
                    s_name->c_str(),f->lloc.filenr,
                    f->lloc.linenr,f->lloc.offset);
      }
    }
  }
  struct_t->emplace(name,sym);
  dump_symbol(sym,stderr);
}

// Main function,handles all members of language
void gen_table(astree *s){
  switch(s->symbol){
    case TOK_ROOT:
      stack.push_back(new symbol_table());
      master.push_back(stack.back());
      for (astree* child: s->children) gen_table(child);        
      break;
    case TOK_BLOCK:
      for (astree* child: s->children) gen_table(child);        
      break;
    case TOK_TYPE_ID:
      return p_typeid(s);
    case TOK_STRUCT:
      return p_struct(s);
  }
}

void free_symbol(){
  for(auto itor: *struct_t){
    if (itor.second->fields != nullptr){
      for (auto itor2: *(itor.second->fields))
        delete itor2.second;
      delete itor.second->fields;
    }
    delete itor.second;
  }
  struct_t->clear(); 
  delete struct_t;

  for (auto itor: master){
    delete itor;
  }
  master.clear();
}


