#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include <bitset>
#include <unordered_map>
#include <string>
#include <vector>
#include "auxlib.h"
#include "astree.h"

using namespace std;

struct symbol {
  // Fields.
  attr_bitset attributes;
  size_t sequence;
  symbol_table* fields;
  location lloc;
  size_t block_nr;
  vector<symbol*>* parameters;
  const string* sname;

  // Functions.
  symbol (astree* ast, size_t block_nr);
  ~symbol();
  symbol* symbol_deepcopy(astree* s);
  void dump_symbol (FILE* outfile, symbol *sym);
};

struct all_tables{
  symbol_table *struct_t;
  symbol_table *global;
  unordered_map<const string*,symbol_table*> *master;
  all_tables(symbol_table *struct_t,
              symbol_table *global,
              unordered_map<const string*,symbol_table*> *master);
};

void gen_table(astree* node);

void free_symbol();

void dump_all_tables(FILE* outfile);

all_tables *get_tables();

#endif
