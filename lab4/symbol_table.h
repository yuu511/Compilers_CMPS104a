#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include <bitset>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
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

void gen_table(astree* node);

void free_symbol();

void dump_all_tables(FILE* outfile);

#endif
