#include "3ac.h"
#include "symbol_table.h"
#include "astree.h"

void ac_struct(symbol_table *struct_table){
  
}

void emit_3ac(astree *s, symbol_table *struct_table, 
  unordered_map<const string*,symbol_table*> *master){
  ac_struct(struct_table);
}
