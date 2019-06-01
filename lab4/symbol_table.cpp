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

symbol::symbol (astree* ast_, size_t block_nr_){
  attributes = ast_->attributes;  
  sequence = 0;
  fields = ast_->struct_ptr;
  lloc = ast_->lloc;
  block_nr = block_nr_;
  parameters = nullptr;
  sname = nullptr;
}

symbol::~symbol(){
  if (fields != nullptr){ 
    for (auto itor: *fields){
        delete itor.second;
    }
    fields->clear();
    delete fields;
  }
}

string dump_attributes(attr_bitset a){
  string st;
  for (size_t i = 0; i<a.size();i++){
    if (a[i]){
      switch(i) {
        case static_cast<int>(attr::VOID):
          st.append ("void ");
          break;
        case static_cast<int>(attr::INT):
          st.append ("int ");
          break;
        case static_cast<int>(attr::NULLPTR_T):
          st.append ("nullptr_t ");
          break;
        case static_cast<int>(attr::STRING):
          st.append ("string ");
          break;
        case static_cast<int>(attr::STRUCT):
          st.append ("struct ");
          break;
        case static_cast<int>(attr::ARRAY):
          st.append ("array ");
          break;
        case static_cast<int>(attr::FUNCTION):
          st.append ("function ");
          break;
        case static_cast<int>(attr::VARIABLE):
          st.append ("variable ");
          break;
        case static_cast<int>(attr::FIELD):
          st.append ("field ");
          break;
        case static_cast<int>(attr::TYPEID):
          st.append ("typeid ");
          break;
        case static_cast<int>(attr::PARAM):
          st.append ("param ");
          break;
        case static_cast<int>(attr::LOCAL):
          st.append ("local ");
          break;
        case static_cast<int>(attr::LVAL):
          st.append ("lval ");
          break;
        case static_cast<int>(attr::CONST):
          st.append ("const ");
          break;
        case static_cast<int>(attr::VREG):
          st.append ("vreg ");
          break;
        case static_cast<int>(attr::VADDR):
          st.append ("vaddr ");
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
         st.append(" ");
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

int type_enum (int t_code){
  switch (t_code) {
    case TOK_VOID:
      return static_cast<int>(attr::VOID);
    case TOK_INT:
      return static_cast<int>(attr::INT);
    case TOK_STRING:
      return static_cast<int>(attr::STRING);
    case TOK_STRUCT:
      return static_cast<int>(attr::STRUCT);
    case TOK_IDENT:
      return static_cast<int>(attr::TYPEID);
  }
  return -1;
}

int struct_exists(const string *sname,location l){
  if (sname != nullptr){
    if (struct_t->find(sname)!=struct_t->end()){
      return 1;
    }
    errprintf ("struct %s not found in field ptr: %zd.%zd.%zd\n",
               sname->c_str(), l.filenr,
               l.linenr, l.offset);
  }
  return 0;
}

int struct_valid(symbol *structsym){
  if (structsym != nullptr) {
    if (structsym->attributes[static_cast<int>(attr::STRUCT)]){
       if (struct_t->find(structsym->sname)->second->fields != nullptr){
         return 1; 
       }
       errprintf("incomplete struct referenced: %s\n",
                 structsym->sname->c_str());
       return 0;
    }
  }
  errprintf("incorrect usage of struct_valid");
  return 0;
}


void p_struct (astree *s){
  symbol *sym = new symbol(s,0);
  sym->attributes.set(static_cast<int>(attr::STRUCT));
  const string* name =  s->children[0]->lexinfo; 
  sym->sname = name;

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

    // if a pointer is found, 
    // adjust identifier and type code accordingly.
    if (c->children[0]->symbol == TOK_ARRAY){
      f->attributes.set(static_cast<int>(attr::ARRAY));
      if (c->children[0]->children[0]->symbol == TOK_PTR){
        f->attributes.set(static_cast<int>(attr::TYPEID));
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
        f->attributes.set(static_cast<int>(attr::TYPEID));
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
    if (t_code == TOK_VOID) {
       errprintf ("VOID may not be a struct param:%zd.%zd.%zd\n",
                   f->lloc.filenr, f->lloc.linenr,
                   f->lloc.offset);
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
    struct_exists(f->sname,f->lloc);
  }
  struct_t->emplace(sym->sname,sym);
  dump_symbol(sym,stderr);
}

void p_function (astree *s){
  symbol *sym = new symbol(s,current_block);
  symbol_table* block = nullptr;
  sym->attributes.set(static_cast<int>(attr::FUNCTION));
  int ret;
  const string *fname;
  const string *sname;

  if (s->children[0]->children[0]->symbol == TOK_ARRAY){
    sym->attributes.set(static_cast<int>(attr::ARRAY));
    if (s->children[0]->children[0]->children[0]->symbol == TOK_PTR){
      sym->attributes.set(static_cast<int>(attr::STRUCT));
      s->sname = sym-> sname = sname =
      s->children[0]->children[0]->children[0]->children[0]->lexinfo;
      if (struct_exists(sname,sym->lloc)){
        struct_valid(sym);
      }
      ret=s->children[0]->children[1]->symbol;
      fname=s->children[0]->children[1]->lexinfo;
    }
    else {
       ret = s->children[0]->children[0]->children[0]->symbol;        
       fname = s->children[0]->children[1]->lexinfo; 
    }
  }
  else {
    ret = TOK_ARRAY;
    if (s->children[0]->children[0]->symbol == TOK_PTR){
      sym->attributes.set(static_cast<int>(attr::STRUCT));
      sname=s->children[0]->children[0]->children[0]->lexinfo;
      s->sname = sym->sname = sname;
      if (struct_exists(sname,sym->lloc)){
        struct_valid(sym);
      }
      ret=s->children[0]->children[1]->symbol;
      fname=s->children[0]->children[1]->lexinfo;
    }
    else {
      ret = s->children[0]->children[0]->symbol;
      fname = s->children[0]->children[1]->lexinfo;
    }
  }
  sym->attributes.set(type_enum(ret));
  current_block = next_block; 
  next_block++;
  block = new symbol_table();
  if (s->children[1]->children.size()>0){
    for (unsigned int i = 0; i < s->children[1]->children.size(); i++){
      astree *c = s->children[1]->children[i];
      symbol *f = new symbol(c,current_block); 
      int t_code;
      const string *id;
      const string *s_name;

      // if a pointer is found, adjust identifier 
      // and type code accordingly.
      if (c->children[0]->symbol == TOK_ARRAY){
        f->attributes.set(static_cast<int>(attr::ARRAY));
        if (c->children[0]->children[0]->symbol == TOK_PTR){
          f->attributes.set(static_cast<int>(attr::TYPEID));
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
          f->attributes.set(static_cast<int>(attr::TYPEID));
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
      if (t_code == TOK_VOID) {
         errprintf ("VOID may not be a function param:%zd.%zd.%zd\n",
                     f->lloc.filenr, f->lloc.linenr,
                     f->lloc.offset);
      }
      f->attributes.set(static_cast<int>(attr::FIELD));
      f->attributes.set(type_enum(t_code));
    }
    sym->parameters->push_back(sym);
  }

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
    case TOK_STRUCT:
      return p_struct(s);
    case TOK_FUNCTION:
      return p_function(s);
  }
}

void free_symbol(){
  for (auto itor: *struct_t){
      delete itor.second;
  }
  struct_t->clear();
  delete struct_t;

  while (not master.empty()){
    symbol_table *sym_t = master.back();
    master.pop_back();
    for (auto itor: *sym_t){
      delete itor.second;
    }
    delete sym_t;
  }

  master.clear();
}


