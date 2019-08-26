#ifndef __3AC_EMITTER_H_
#define __3AC_EMITTER_H_

#include "symbol_table.h"
#include "astree.h"
#include "reg.h"

int generate_3ac();
void free_3ac();
void emit_all3ac(FILE *out);

// instruction bitset for kind of instruction
enum class instruction{
  GOTO,ASSIGNMENT,LABEL_ONLY,RETURN,BITSET_SIZE
};
using instruction_bitset = bitset <static_cast<size_t>(instruction::BITSET_SIZE)>;

/*
    the format of a 3-address code statement depends on 
    the type of instruction,represented by bitset attribute:

    let tn = reg n (defined in reg.h)

    ASSIGNMENT:
    [LABEL] [t0]  = [t1] [OPERATOR] [t2] 
    
    GOTO:
    [LABEL] goto [condition] if [t1] [OPERATOR] [t2]
    
    LABEL_ONLY:
    [LABEL]

    RETURN:
    [LABEL] return [t0]
*/

struct ac3{
  astree *expr;
  string *label;
  string *condition;
  reg *t0;
  string *op;
  reg *t1;
  reg *t2;
  instruction_bitset itype = 0;
  ac3(astree *expr,reg *t0 = nullptr);
  ~ac3();
};

/*
   all functions have an ac3 table assocciated with them
   (which is just a collection of 3 address code statements, defined above)
   all global declarations are also encapsulated within an ac3 table
*/

using ac3_table = vector<ac3*>;

/* 
   namespace for values to return:
   1. Table for all 3-address code global statements.
   2. For every function : table of 3-address code statements.
   2. Table mapping the 3-Address code tables its respective symbol table.
   3. Table containing all string literals used in the program.
*/

namespace three_address_code {
  extern ac3_table *all_globals; 
  extern vector<pair<const string*,ac3_table*>> *all_functions;
  extern unordered_map <symbol_table*, ac3_table*> *table_lookup;
  extern vector<const string*> *all_strings;
}

#endif
