#ifndef __STATEMENT_TABLE_H_
#define __STATEMENT_TABLE_H_

#include <bitset>
#include "astree.h"
#include "reg.h"

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

struct statement {
  astree *expr;
  string *label;
  string *condition;
  reg *t0;
  string *op;
  reg *t1;
  reg *t2;
  instruction_bitset itype = 0;
  statement(astree *expr,reg *t0 = nullptr);
  ~statement();
};

/*
   all functions have an statement table assocciated with them
   (which is just a collection of 3 address code statements, defined above)
   all global declarations are also encapsulated within a statement table
*/

using statement_table = vector<statement*>;

#endif
