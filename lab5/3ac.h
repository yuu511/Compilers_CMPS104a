#ifndef __3AC_H_
#define __3AC_H_

#include "symbol_table.h"
#include "astree.h"

void emit_3ac(astree *root, all_tables *table, FILE *out);

void free_3ac();

// instruction bitset for kind of instruction
enum class instruction{
  GOTO,ASSIGNMENT,LABEL_ONLY,CALL,RETURN,BITSET_SIZE
};
using instruction_bitset = bitset <static_cast<size_t>(instruction::BITSET_SIZE)>;

/* 
   a register may be:
   1. an identifier e.g. x
   2. a temporary reigster e.g. $t0
   3. a function call e.g. call foo(arg1,arg2) 

   and be preceded by a unary operator (-,+,not)
*/

struct reg {
  // exists if a register is a variable
  const string *ident;
  // exists if a register is an actual register
  int reg_number;
  string *stride;
  // exists if a register is a function
  string *fname;
  vector<reg*> *parameters;
  // optional uanry operator
  string *unop;
  // constructors
  reg(const string *ident);
  reg(string *stride , int reg_number);
  reg(string *fname, vector<reg*> *parameters = nullptr);
  string str();
  ~reg();
};

/*
    the format of a 3-address code statement depends on 
    the type of instruction,represented by bitset attribute:

    let tn = register (defined above)

    ASSIGNMENT:
    [LABEL] t0 = t1 OP t2
    
    GOTO:
    goto LABEL [ if not t0 ]
    
    LABEL_ONLY:
    [LABEL]

    RETURN:
    [LABEL] return [t0]

    CALL:
    [LABEL] [t0 = ] call t1 ( [ paramters[0],parameters[1] ... paramters[n] ] ) 

*/
struct ac3{
  astree *expr;
  string *label;
  reg *t0;
  const string *op;
  reg *t1;
  reg *t2;
  instruction_bitset itype = 0;
  ac3(astree *expr,reg *t0 = nullptr);
  ~ac3();
};

using ac3_table = vector<ac3*>;

#endif
