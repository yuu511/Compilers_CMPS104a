#include "symbol_table.h"
#include "astree.h"

void emit_3ac(astree *root, symbol_table *struct_table, 
  unordered_map<const string*,symbol_table*> *master, FILE *out);

void free_3ac();
