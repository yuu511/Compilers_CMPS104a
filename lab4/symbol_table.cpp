#include <bitset>
#include <unordered_set>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;
#include "auxlib.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"

symbol_table *global = new symbol_table();
symbol_table *local;
symbol_table *struct_t = new symbol_table();
vector<symbol_table*> master;
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
  if (yydebug) {
    fprintf(stderr, "Deleting symbol...\n");
    symbol::dump_symbol(stderr,this);
  }
  if (fields != nullptr){ 
    for (auto itor: *fields){
        delete itor.second;
    }
    fields->clear();
    delete fields;
  }
  if (parameters != nullptr){
    for (auto itor: *parameters){
      delete itor;
    }
    delete parameters;
  }
}

// have to print struct differently depending if it's in a struct field
// vs in a function parameter/statement according to the spec
string dump_attributes(symbol *sym,int func_tid=0,int struct_tid=0){
  attr_bitset a = sym->attributes;
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
	  if (struct_tid){
	    if (sym->sname != nullptr){
	      st.append (sym->sname->c_str());
	      st.append (" ");
	    }
	  }
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
         st += dump_attributes(itor.second); 
         // ident
         st.append(string(itor.first->c_str()));
         st.append(" ");
      }
  }
  return st;
}

void symbol::dump_symbol (FILE* outfile,symbol *sym){
  string f="";
  if (sym->fields != nullptr){
    f = dump_table_fields(sym->fields);
  }
  fprintf (outfile, "%p->{%zd.%zd.%zd}\nattrib: %s\nfields:%s\n",
           static_cast<const void*> (sym),
           sym->lloc.filenr,
	   sym->lloc.linenr,
	   sym->lloc.offset,
           dump_attributes(sym).c_str(),
	   f.c_str());
}

int type_enum (int t_code){
  switch (t_code){
    case TOK_VOID:
      return static_cast<int>(attr::VOID);
    case TOK_INT:
      return static_cast<int>(attr::INT);
    case TOK_STRING:
      return static_cast<int>(attr::STRING);
    case TOK_IDENT:
      return static_cast<int>(attr::STRUCT);
  }
  return -1;
}

int struct_exists(const string *sname){
  if (sname != nullptr){
    if (struct_t->find(sname)!=struct_t->end()){
      return 1;
    }
  }
  return 0;
}

int struct_valid(const string *sname, location lloc){
  if (struct_exists(sname)){
    if (struct_t->find(sname)->second->fields != nullptr){
      return 1; 
    }
    else {
      errprintf("incomplete struct referenced: %s: (%zd.%zd.%zd)\n",
                 sname->c_str(),
                 lloc.filenr,
                 lloc.linenr,
                 lloc.offset);
    }
  }
  else {
      errprintf("nonexistent struct referenced: %s: (%zd.%zd.%zd)\n",
                 sname->c_str(),
                 lloc.filenr,
                 lloc.linenr,
                 lloc.offset);
  }
  return 0;
}


void print_struct(FILE* out,const string* name, symbol* sym){
  // do not print out non-defined structs
  if (sym->fields!= nullptr){
    // struct name
    fprintf(out,"%s (%zd.%zd.%zd) {%zd} %s\n",
            name->c_str(),
            sym->lloc.filenr,
            sym->lloc.linenr,
            sym->lloc.offset,
            sym-> block_nr,
            dump_attributes(sym,0,1).c_str());
    // struct fields
      for (size_t i = 0; i < sym->fields->size(); i++){
        for (auto itor: *sym->fields){
          if (itor.second->sequence == i ){
            fprintf (out,"   ");
            fprintf (out,"%s (%zd.%zd.%zd) %s %zd\n",
                     itor.first->c_str(),
                     itor.second->lloc.filenr,
                     itor.second->lloc.linenr,
                     itor.second->lloc.offset,
                     dump_attributes(itor.second,0,1).c_str(),
                     i );
            continue;
          }
        }
      }
    fprintf (out,"\n");
  }
}

void p_struct (astree *s){
  symbol *sym = new symbol(s,0);
  sym->attributes.set(static_cast<int>(attr::STRUCT));
  const string* name =  s->children[0]->lexinfo; 
  sym->sname = name;

  // add to struct table first, then process fields.
  if (struct_t->find(name)!=struct_t->end()){
    if ((*struct_t)[name]->fields == nullptr){
      symbol* old = struct_t->find(name)->second;
      struct_t->erase(struct_t->find(name));
      delete old;
      struct_t->emplace(name,sym);  
    } 
    else{
      errprintf ("struct %s defined already: %zd.%zd.%zd\n",
                  name->c_str(),sym->lloc.filenr,
                  sym->lloc.linenr,sym->lloc.offset);
      delete sym;
      return;
    }  
  }
  else{
    struct_t->emplace(name,sym);  
  }
  sym->fields = new symbol_table();
  for (unsigned int i = 1; i < s->children.size(); i++){
    astree *c = s->children[i];
    symbol *f = new symbol(c,0); 
    int t_code;
    const string *id;
    const string *s_name;
    f->sequence = i-1;

    // if a pointer is found, 
    // adjust identifier and type code accordingly.
    if (c->children[0]->symbol == TOK_ARRAY){
      f->attributes.set(static_cast<int>(attr::ARRAY));
      if (c->children[0]->children[0]->symbol == TOK_PTR){
        t_code = c->children[0]->children[0]->children[0]->symbol;
        s_name = c->children[0]->children[0]->children[0]->lexinfo;
        c->sname = f->sname = s_name;
        id = c->children[1]->lexinfo;
        // if an incomplete structure is found, add it to hash
        if (!(struct_exists(s_name))){
          symbol *placeholder = new symbol(c,0);   	  
          placeholder->attributes.set(static_cast<int>(attr::STRUCT));
          placeholder->sname = s_name;
          struct_t->emplace(s_name,placeholder); 
        }
      }
      else{
        t_code = c->children[0]->children[0]->symbol;
        id = c->children[1]->lexinfo;
      }
    }
    else{
      if (c->children[0]->symbol == TOK_PTR){
        t_code = c->children[0]->children[0]->symbol;
        s_name = c->children[0]->children[0]->lexinfo;
        c->sname = f->sname = s_name;
        id = c->children[1]->lexinfo;
        // if an incomplete structure is found, add it to hash
        if (!(struct_exists(s_name))){
          symbol *placeholder = new symbol(c,0);   	  
          placeholder->attributes.set(static_cast<int>(attr::STRUCT));
          placeholder->sname = s_name;
          struct_t->emplace(s_name,placeholder); 
        }
      }
      else{
        t_code = c->children[0]->symbol;
        id = c->children[1]->lexinfo;
      }
    }

    if (t_code == TOK_VOID){
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
    else{
      sym->fields->emplace(id,f);
    }
  }
  struct_t->erase(struct_t->find(sym->sname));
  struct_t->emplace(sym->sname,sym);
  print_struct(lexer::sym_fp,sym->sname,sym);
}

int matching_attrib(symbol *p, symbol *f){
  // XOR
  if (!(p->parameters == nullptr) != !(f->parameters == nullptr))
    return 0;
  else if (!(p->sname == nullptr ) != !(f->sname == nullptr))
    return 0;
  else {
    if (p->sname != nullptr && f->sname != nullptr){
        if (strcmp(p->sname->c_str(), f->sname->c_str()) != 0)
          return 0;
    }
    attr_bitset pa = p->attributes; 
    attr_bitset fa = f->attributes;
    // check function return attribs
    for (int i = 0 ; i < static_cast<int>(attr::BITSET_SIZE); i++){
      if ( i == static_cast<int>(attr::PROTOTYPE))
        continue;
      if (pa[i] != fa[i])
        return 0; 
    }
    if (p->parameters != nullptr  && f->parameters != nullptr){
      if (p->parameters->size() != f->parameters->size())
         return 0;
      for (unsigned int i = 0 ; i< f->parameters->size(); i++){
        if (p->parameters->at(i)->sname != nullptr && 
	    f->parameters->at(i)->sname != nullptr ) {
            if (strcmp(p->parameters->at(i)->sname->c_str(), 
	               f->parameters->at(i)->sname->c_str()) != 0)
              return 0;
        }
        attr_bitset pra = p->parameters->at(i)->attributes;
        attr_bitset fra = f->parameters->at(i)->attributes;
        // check function param attribs
        for (int j =0 ; j < static_cast<int>(attr::BITSET_SIZE); j++){
          if (pra[j] != fra[j]){
            return 0; 
	  }
        }
      }
    }
    return 1;
  }
  return 0;

}

void p_function (astree *s){
  symbol *sym = new symbol(s,current_block);
  current_block = next_block; 
  next_block++;
  sym->attributes.set(static_cast<int>(attr::FUNCTION));
  int ret;
  const string *fname;
  const string *sname;
  
  astree *ref = s->children[0];
  // process function return type

  // if a pointer is found, adjust identifier 
  // and type code accordingly.
  if (ref->children[0]->symbol == TOK_ARRAY){
    sym->attributes.set(static_cast<int>(attr::ARRAY));
    if (ref->children[0]->children[0]->symbol == TOK_PTR){
      sname = ref->children[0]->children[0]->children[0]->lexinfo;
      s->sname = sym->sname = sname;
      struct_valid(sname,sym->lloc);
      ret = ref->children[0]->children[0]->children[0]->symbol;
      fname = ref->children[1]->lexinfo;
    }
    else{
      ret = ref->children[0]->children[0]->symbol;  
      fname = ref->children[1]->lexinfo;
    }
  }
  else{
    if (ref->children[0]->symbol == TOK_PTR){
      sname = ref->children[0]->children[0]->lexinfo;
      s->sname = sym->sname = sname;
      struct_valid(sname,sym->lloc);
      ret = ref->children[0]->children[0]->symbol;
      fname = ref->children[1]->lexinfo;
    }
    else{
      ret = ref->children[0]->symbol;  
      fname = ref->children[1]->lexinfo;
    }
  }
  if (ret == TOK_VOID)
    sym->attributes.set(static_cast<int>(attr::VOID));
  else 
    sym->attributes.set(type_enum(ret));

  symbol_table *block = new symbol_table;
  local = block;
  // process function args
  if (s->children[1]->children.size()>0){
    sym->parameters = new vector<symbol*>();
    for (unsigned int i = 0; i < s->children[1]->children.size(); i++){
      astree *c = s->children[1]->children[i];
      symbol *f = new symbol(c,current_block); 
      int t_code;
      const string *id;
      const string *spname;
      f->sequence = i-1;

      // if a pointer is found, adjust identifier 
      // and type code accordingly.
      if (c->children[0]->symbol == TOK_ARRAY){
        f->attributes.set(static_cast<int>(attr::ARRAY));
        if (c->children[0]->children[0]->symbol == TOK_PTR){
          spname = c->children[0]->children[0]->children[0]->lexinfo;
	  c->sname = f->sname = spname;
          struct_valid(spname,f->lloc);
          t_code = c->children[0]->children[0]->children[0]->symbol;
          id = c->children[1]->lexinfo;
        }
        else{
          t_code = c->children[0]->children[0]->symbol;  
          id = c->children[1]->lexinfo;
        }
      }
      else{
        if (c->children[0]->symbol == TOK_PTR){
	  spname = c->children[0]->children[0]->lexinfo;
	  c->sname = f->sname = spname;
	  struct_valid(spname,f->lloc);
	  t_code = c->children[0]->children[0]->symbol;
	  id = c->children[1]->lexinfo;
        }
	else{
          t_code = c->children[0]->symbol;  
	  id = c->children[1]->lexinfo;
	}
      }

      if (t_code == TOK_VOID){
         errprintf ("VOID may not be a function param:%zd.%zd.%zd\n",
                     f->lloc.filenr, f->lloc.linenr,
                     f->lloc.offset);
      }
      f->attributes.set(static_cast<int>(attr::LVAL));
      f->attributes.set(static_cast<int>(attr::VARIABLE));
      f->attributes.set(static_cast<int>(attr::PARAM));
      f->attributes.set(type_enum(t_code));
      if (block->find(spname)!=sym->fields->end()){
        errprintf("%s defined multiple times in func %s :%zd.%zd.%zd\n",
                   spname->c_str(), fname->c_str(),
                   sym->lloc.filenr, sym->lloc.linenr,
                   sym->lloc.offset);

      }
      else{
        block->emplace(id,f);
        sym->parameters->push_back(f);
      }
    }
  }
  if (s->children.size()>2){
    if (global->find(fname)!=sym->fields->end()){
      if (global->find(fname)->second->attributes[static_cast<int>(attr::PROTOTYPE)]){
        // match params then emplace
	symbol* old = global->find(fname)->second;
	if (matching_attrib(old,sym)){
	  global->erase(global->find(fname));
	  delete old;
          global->emplace(fname,sym);
          master.push_back(block);
	}
	else {
          errprintf("nonmatching params for function %s: %zd.%zd.%zd\n",
                     fname->c_str(),
                     sym->lloc.filenr, sym->lloc.linenr,
                     sym->lloc.offset);
	}
      }
      else{ 
        errprintf("function %s defined multiple times: %zd.%zd.%zd\n",
                   fname->c_str(),
                   sym->lloc.filenr, sym->lloc.linenr,
                   sym->lloc.offset);
      }
    }
    else{
      global->emplace(fname,sym);
      master.push_back(block);
    }
  }
  else{
    if (global->find(fname)!=sym->fields->end()){
        errprintf("prototype %s defined multiple times: %zd.%zd.%zd\n",
                   fname->c_str(),
                   sym->lloc.filenr, sym->lloc.linenr,
                   sym->lloc.offset);
    }
    else{
      sym->attributes.set(static_cast<int>(attr::PROTOTYPE));
      delete block;
      global->emplace(fname,sym);
    }
  }
}

// Main function,handles all members of language
void gen_table(astree *s){
  switch(s->symbol){
    case TOK_ROOT:
      master.push_back(global);      
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
  for (auto itor: master){
    for (auto itor2: *itor){
       delete itor2.second;
    }
    itor->clear();
    delete itor;
  }
  for (auto itor: *struct_t){
      delete itor.second;
  }
  struct_t->clear();
  delete struct_t;
}

void dump_all_tables(FILE* out){
  for (auto itor: *struct_t){
    print_struct(out,itor.first,itor.second);  
  }

}


