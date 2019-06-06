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
unordered_map<const string*,symbol_table*> *master = 
new unordered_map<const string*,symbol_table*>;
int current = 0;
int next_block = 1;
symbol *p_expression(astree *s);

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

string dump_attributes(symbol *sym){
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
	      if (sym -> sname !=nullptr){
	        st.append (sym->sname->c_str());
	        st.append (" ");
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
          st.append ("struct ");
	      if (sym -> sname !=nullptr){
	        st.append (sym->sname->c_str());
	        st.append (" ");
	      }
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
  string p="";
  if (sym->fields != nullptr){
    f = dump_table_fields(sym->fields);
  }
  if (sym->parameters != nullptr){
     for (auto itor: *(sym->parameters)){
       p.append(dump_attributes(itor));
       p.append(" //  ");
     }
  }
  fprintf (outfile, "%p->{%zd.%zd.%zd}\nattrib: %s\n"
           "sequence: %zd\nfields: %s\nblock: %zd\nparams: %s\n",
           static_cast<const void*> (sym),
           sym->lloc.filenr,
	   sym->lloc.linenr,
	   sym->lloc.offset,
       dump_attributes(sym).c_str(),
	   sym->sequence,
	   f.c_str(),
	   sym->block_nr,
	   p.c_str() );
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
      return static_cast<int>(attr::TYPEID);
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

// things are going to be either a global vardecl or 
// encompassed within a function (which is global in oc)
// if statement, simply print.
// if function, look up block in hash, 
// print function name and block members.
void print_map(FILE* out, symbol_table *sym){
  for (auto itor: *sym){
    // if function
    if (itor.second->attributes[static_cast<int>(attr::FUNCTION)]){
    // print out name
      fprintf(out,"%s (%zd.%zd.%zd) {%zd} %s\n",
              itor.first->c_str(),
              itor.second->lloc.filenr,
              itor.second->lloc.linenr,
              itor.second->lloc.offset,
              itor.second-> block_nr,
              dump_attributes(itor.second).c_str());
      // print out the associated block ( if any )
      if ((master->find(itor.first))!=master->end()){
        symbol_table *block = master->find(itor.first)->second;
      for (size_t i = 0; i < block->size(); i++){
	    for (auto itor2: *block){
	       if (itor2.second->sequence == i){
                 fprintf(out,"   %s (%zd.%zd.%zd) {%zd} %s%zd\n",
                         itor2.first->c_str(), 
                         itor2.second->lloc.filenr,
                         itor2.second->lloc.linenr,
                         itor2.second->lloc.offset,
                         itor2.second-> block_nr,
                         dump_attributes(itor2.second).c_str(),
	             i);
	         continue;
	      }
	    }
	  }
      }
  }
    // otherwise, it's a statement
    else {
      fprintf(out,"%s (%zd.%zd.%zd) {%zd} %s\n",
              itor.first->c_str(),
              itor.second->lloc.filenr,
              itor.second->lloc.linenr,
              itor.second->lloc.offset,
              itor.second-> block_nr,
              dump_attributes(itor.second).c_str());
    }
    fprintf (out,"\n");
  }
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
            dump_attributes(sym).c_str());
    // struct fields
      for (size_t i = 0; i < sym->fields->size(); i++){
        for (auto itor: *sym->fields){
          if (itor.second->sequence == i ){
            fprintf (out,"   ");
            fprintf (out,"%s (%zd.%zd.%zd) %s%zd\n",
                     itor.first->c_str(),
                     itor.second->lloc.filenr,
                     itor.second->lloc.linenr,
                     itor.second->lloc.offset,
                     dump_attributes(itor.second).c_str(),
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
}

int matching_attrib(symbol *p, symbol *f){
  // XOR
  if (!(p->parameters == nullptr) != !(f->parameters == nullptr))
    return 0;
  else if (!(p->sname == nullptr) != !(f->sname == nullptr))
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
    // check parameter attribs
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
  current = next_block-1;
  symbol *sym = new symbol(s,current);
  current = next_block; 
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
  // parameters must be copied to both
  // the block, and param list, so allocate two symbols
  if (s->children[1]->children.size()>0){
    sym->parameters = new vector<symbol*>();
    for (unsigned int i = 0; i < s->children[1]->children.size(); i++){
      astree *c = s->children[1]->children[i];
      symbol *f = new symbol(c,current); 
      symbol *f_copy = new symbol(c,current);
      int t_code;
      const string *id;
      const string *spname;
      f->sequence = i;
      f_copy->sequence = i;

      // if a pointer is found, adjust identifier 
      // and type code accordingly.
      if (c->children[0]->symbol == TOK_ARRAY){
        f->attributes.set(static_cast<int>(attr::ARRAY));
        if (c->children[0]->children[0]->symbol == TOK_PTR){
          spname = c->children[0]->children[0]->children[0]->lexinfo;
	      c->sname = f->sname = f_copy->sname = spname;
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
	  c->sname = f->sname = f_copy->sname = spname;
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
      f_copy->attributes.set(static_cast<int>(attr::LVAL));
      f->attributes.set(static_cast<int>(attr::VARIABLE));
      f_copy->attributes.set(static_cast<int>(attr::VARIABLE));
      f->attributes.set(static_cast<int>(attr::PARAM));
      f_copy->attributes.set(static_cast<int>(attr::PARAM));
      f->attributes.set(type_enum(t_code));
      f_copy->attributes.set(type_enum(t_code));
      if (block->find(id)!=sym->fields->end()){
        errprintf("%s defined multiple times in func %s :%zd.%zd.%zd\n",
                   spname->c_str(), fname->c_str(),
                   sym->lloc.filenr, sym->lloc.linenr,
                   sym->lloc.offset);

      }
      else{
        f->attributes.set(static_cast<int>(attr::LOCAL));
        local->emplace(id,f);
        sym->parameters->push_back(f_copy);
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
          master->emplace(fname,block);
	  gen_table(s->children[2]);
	  current = 0;
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
      master->emplace(fname,block);
      gen_table(s->children[2]);
      current = 0;
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

int is_a_reference(symbol *sym){
  if (sym->attributes[static_cast<int>(attr::NULLPTR_T)] || 
      sym->attributes[static_cast<int>(attr::STRING)] ||
      sym->attributes[static_cast<int>(attr::TYPEID)] ||
      sym->attributes[static_cast<int>(attr::ARRAY)] ) {
      return 1;
  }
  return 0;
}

int compatible(symbol *l,symbol *r){
  int a_void      = static_cast<int>(attr::VOID);
  int a_int       = static_cast<int>(attr::INT);
  int a_string    = static_cast<int>(attr::STRING);
  int a_ptr       = static_cast<int>(attr::TYPEID);
  int a_array     = static_cast<int>(attr::ARRAY);
  int a_nullptr_t = static_cast<int>(attr::NULLPTR_T);
  if (is_a_reference(l) && !(l->attributes[a_nullptr_t]) ){
    if (r->attributes[a_nullptr_t]){
      return 1;
    }
  }
  if (l->sname != nullptr && r->sname != nullptr){
    if (strcmp(l->sname->c_str(),r->sname->c_str()) != 0){
      errprintf ("struct %s assigned as %s %zd.%zd.%zd\n",
                  l->sname->c_str(), r->sname->c_str(),
                  l->lloc.filenr, l->lloc.linenr, l->lloc.offset);
      return 0;
    }
  }
  attr_bitset left = l->attributes;
  attr_bitset right = r->attributes;

  if (left[a_void]   == right[a_void]   &&
      left[a_int]    == right[a_int]    &&
      left[a_string] == right[a_string] &&
      left[a_ptr]    == right[a_ptr]    &&
      left[a_array]  == right[a_array] ){
        return 1;
  }
 return 0; 
}

symbol *p_assignment (astree *parent, symbol *left, symbol *right){
  int a_lval = static_cast<int>(attr::LVAL);
  int a_vreg = static_cast<int>(attr::VREG);
  symbol *ret = new symbol(parent,current);
  ret->attributes = left->attributes;
  if (left->attributes[a_lval]){
    if (right->attributes[a_vreg]){
      ret->attributes.reset(a_lval);
      ret->attributes.set(a_vreg); 
    }
  }
  if (!compatible(left,right)){
    errprintf ("not compatible assignment: %zd.%zd.%zd\n",
                left->lloc.filenr, left->lloc.linenr
                , left->lloc.offset);
  }
  if (left->sname != nullptr)
    ret->sname = left->sname;
  delete left;  
  delete right;
  return ret;
}

symbol *p_INTCON(astree *s){
  symbol *sym = new symbol(s,current);
  sym->attributes.set(static_cast<int>(attr::INT));
  sym->attributes.set(static_cast<int>(attr::CONST));
  return sym;
}

symbol *p_STRINGCON(astree *s){
  symbol *sym = new symbol(s,current);
  sym->attributes.set(static_cast<int>(attr::STRING));
  sym->attributes.set(static_cast<int>(attr::CONST));
  return sym;
}

symbol *p_NULLPTR(astree *s){
  symbol *sym = new symbol(s,current);
  sym->attributes.set(static_cast<int>(attr::NULLPTR_T));
  sym->attributes.set(static_cast<int>(attr::CONST));
  return sym;
}

symbol *p_math(astree *s){
  int a_int = static_cast<int>(attr::INT); 
  int a_vreg = static_cast<int>(attr::VREG); 
  if (s->children.size() < 2)
    errprintf ("p_math called incorrectly: %zd.%zd.%zd",
                s->lloc.filenr, s->lloc.linenr, s->lloc.offset);
  symbol *left = p_expression(s->children[0]);
  symbol *right = p_expression(s->children[1]);
  if (!(left->attributes[a_int] && right->attributes[a_int]))
    errprintf ("type mismatch: math expr %zd.%zd.%zd",
                s->lloc.filenr, s->lloc.linenr, s->lloc.offset);
  delete left;
  delete right;
  symbol *ret = new symbol (s,current);
  ret->attributes.set(a_int);
  ret->attributes.set(a_vreg);
  return ret;
}

symbol *p_unary(astree *s){
  int a_int = static_cast<int>(attr::INT); 
  int a_vreg = static_cast<int>(attr::VREG); 
  symbol *unary = p_expression(s->children[0]);
  if (!(unary->attributes[a_int]))
    errprintf ("type mismatch: unary expr %zd.%zd.%zd",
                s->lloc.filenr, s->lloc.linenr, s->lloc.offset);
  unary->attributes.set(a_int);
  unary->attributes.set(a_vreg);
  return unary;
}

symbol *p_overload (astree *s){
  if (s->children.size() > 1)
    return p_math(s);
  return p_unary(s);
}

symbol *p_eq(astree *s){
  if (s->children.size() > 1){
    symbol *left = p_expression(s->children[0]);
    symbol *right = p_expression(s->children[1]);
    return p_assignment(s,left,right);
  }
  errprintf ("inapproriate call: p_eq %zd.%zd.%zd\n"); 
  return nullptr;
}

symbol *p_alloc(astree *s){
  int a_typeid = static_cast<int>(attr::TYPEID); 
  int a_vreg = static_cast<int>(attr::VREG); 
  int a_string = static_cast<int>(attr::STRING); 
  int a_array = static_cast<int>(attr::ARRAY); 
  int a_int = static_cast<int>(attr::INT); 

  symbol *sym = new symbol (s,current);
  if (s->children.size() == 1){
    if(struct_valid(s->children[0]->lexinfo,s->lloc)){
      sym->sname = s->children[0]->lexinfo;
      sym->attributes.set(a_typeid);
      sym->attributes.set(a_vreg);
    }
    else {
      errprintf("nonexistent struct referenced: %s: (%zd.%zd.%zd)\n",
                 s->children[0]->lexinfo,
                 s->lloc.filenr,
                 s->lloc.linenr,
                 s->lloc.offset);

    }
  }
  else {
    if (s->children[0]->symbol == TOK_ARRAY){
      symbol *eval = p_expression(s->children[1]);
      if (!(eval->attributes[a_int])){
        errprintf("expr not an int: (%zd.%zd.%zd)\n",
                   s->lloc.filenr,
                   s->lloc.linenr,
                   s->lloc.offset);
      }
      int base = s->children[0]->children[0]->symbol;
      if (base == TOK_VOID){
       errprintf ("VOID may not be a type:%zd.%zd.%zd\n",
                   s->lloc.filenr, s->lloc.linenr,
                   s->lloc.offset);
      }
      if (base == TOK_PTR){
        base =
        s->children[0]->children[0]->children[0]->symbol;
        if (struct_valid(s->
            children[0]->children[0]->children[0]->lexinfo,
            s->lloc)){
           sym->attributes.set(a_typeid); 
           sym->sname = 
           s->children[0]->children[0]->children[0]->lexinfo;
        }
        else {
          errprintf("nonexistent struct referenced: %s: (%zd.%zd.%zd)\n",
                     s->children[0]->children[0]->children[0]->lexinfo,
                     s->lloc.filenr,
                     s->lloc.linenr,
                     s->lloc.offset);
        }
      }
      sym->attributes.set(a_array);
      sym->attributes.set(type_enum(base));
    }
    else {
      symbol *eval = p_expression(s->children[1]);
      if (!(eval->attributes[a_int])){
        errprintf("expr not an int: (%zd.%zd.%zd)\n",
                   s->lloc.filenr,
                   s->lloc.linenr,
                   s->lloc.offset);
      }
      sym->attributes.set(a_string);
      sym->attributes.set(a_vreg);
      delete eval;
    }
  }
  return sym;
}

symbol *p_expression(astree *s){
  switch(s->symbol){
    case TOK_CHARCON:
    case TOK_INTCON:
      return p_INTCON(s); 
      break;
    case TOK_STRINGCON:
      return p_STRINGCON(s); 
      break;
    case TOK_NULLPTR:
      return p_NULLPTR(s);
      break;
    case TOK_LT:
    case TOK_LE:
    case TOK_GT:
    case TOK_GE:
    case '*':
    case '/':
    case '%':
      return p_math(s);
      break;
    case TOK_NOT:
      return p_unary(s);
      break;
    case '+':
    case '-':
      return p_overload(s);
    case '=':
      return p_eq(s);
    case TOK_ALLOC:
      return p_alloc(s);
  }
  return nullptr;
}

void p_typeid(astree *s){
  symbol *sym = new symbol(s,current);
  int ret;
  const string* vname;
  const string* sname;

  sym->attributes.set(static_cast<int>(attr::VARIABLE));
  sym->attributes.set(static_cast<int>(attr::LVAL));

  if (s->children[0]->symbol == TOK_ARRAY){
    sym->attributes.set(static_cast<int>(attr::ARRAY));
    if (s->children[0]->children[0]->symbol == TOK_PTR){
      sname = s->children[0]->children[0]->children[0]->lexinfo;
      s->sname = sym->sname = sname;
      struct_valid(sname,sym->lloc);
      ret = s->children[0]->children[0]->children[0]->symbol;
      vname = s->children[1]->lexinfo;
    }
    else{
      ret = s->children[0]->children[0]->symbol;  
      vname = s->children[1]->lexinfo;
    }
  }
  else{
    if (s->children[0]->symbol == TOK_PTR){
      sname = s->children[0]->children[0]->lexinfo;
      s->sname = sym->sname = sname;
      struct_valid(sname,sym->lloc);
      ret = s->children[0]->children[0]->symbol;
      vname = s->children[1]->lexinfo;
    }
    else{
      ret = s->children[0]->symbol;  
      vname = s->children[1]->lexinfo;
    }
  }
  if (ret == TOK_VOID){
     errprintf ("VOID may not be a variable decl:%zd.%zd.%zd\n",
                 s->lloc.filenr, s->lloc.linenr,
                 s->lloc.offset);
  }
  sym->attributes.set(type_enum(ret));

  // check for existence in local or global tables
  // depending on current scope.
  if (current != 0 && local != nullptr){
    if (local->find(vname)!=struct_t->end()){
      errprintf ("name %s already defined within block %d: "
                 "%zd.%zd.%zd\n",
      	         vname->c_str(), current,
                 sym->lloc.filenr, sym->lloc.linenr,
                 sym->lloc.offset);
      delete (sym);
      return;
    }
  }
  else  {
    string type ="";
    if (global->find(vname)->second
        ->attributes[static_cast<int>(attr::FUNCTION)])
      type.append ("function");
    else if (global->find(vname)->second
             ->attributes[static_cast<int>(attr::LVAL)])
      type.append ("variable");

    errprintf ("name %s already defined globally"
               " as a %s: %zd.%zd.%zd\n",
               vname->c_str(),
               type.c_str(),
               sym->lloc.filenr, sym->lloc.linenr,
               sym->lloc.offset);
    delete (sym);
    return;
  }

  // does not have an assignment e.g. int x;
  if ( s->children.size() < 3){
    // is part of a block
    if (current != 0 && local != nullptr){
      sym->sequence = local->size();
      sym->attributes.set(static_cast<int>(attr::LOCAL));
      local->emplace(vname,sym);  
    }
    // is a global decl
    else {
      global->emplace(vname,sym);  
    }
    return;
  }
  // has an assignment
  astree *parse = s->children[2];
  symbol *left = sym;
  symbol *right = p_expression(parse); 
  symbol *parsed;
  parsed = p_assignment(s,left,right);
  if (current !=0 && local != nullptr){
    parsed->sequence = local->size(); 
    parsed->attributes.set(static_cast<int>(attr::LOCAL));
    local->emplace(vname,parsed);
  }
  else {
    global->emplace(vname,parsed);
  }
}


// Main function,handles all members of language
void gen_table(astree *s){
  switch(s->symbol){
    case TOK_ROOT:
      master->emplace(s->lexinfo,global);      
      for (astree* child: s->children) gen_table(child);        
      break;
    case TOK_BLOCK:
      for (astree* child: s->children) gen_table(child);        
      break;
    case TOK_STRUCT:
      return p_struct(s);
      break;
    case TOK_FUNCTION:
      return p_function(s);
      break;
    case TOK_TYPE_ID:
      return p_typeid(s);
      break;
  }
}

void free_symbol(){
  for (auto itor: *master){
    for (auto itor2: *itor.second){
      delete itor2.second; 
    }
    delete itor.second;
  }
  master->clear();
  delete master;
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
  print_map(out,global);
}


