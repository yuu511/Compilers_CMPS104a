#ifndef __3AC_EMITTER_H_
#define __3AC_EMITTER_H_

#include "symbol_table.h"
#include "astree.h"
#include "statement_table.h"

int generate_3ac();
void free_3ac();
void emit_all3ac(FILE *out);

/* 
   namespace for values to return:
   1. Table for all 3-address code global statements.
   2. For every function : table of 3-address code statements.
   2. Table mapping the 3-Address code tables its respective symbol table.
   3. Table containing all string literals used in the program.
*/

namespace three_address_code {
  extern statement_table *all_globals; 
  extern vector<pair<const string*,statement_table*>> *all_functions;
  extern unordered_map <symbol_table*, statement_table*> *table_lookup;
  extern vector<const string*> *all_strings;
}

#endif
