#ifndef __3AC_H_
#define __3AC_H_

#include "symbol_table.h"
#include "astree.h"

// instruction bitset for kind of instruction
enum class instruction{
  GOTO,ASSIGNMENT,LABEL_ONLY,RETURN,BITSET_SIZE
};
using instruction_bitset = bitset <static_cast<size_t>(instruction::BITSET_SIZE)>;

/* 
   reg may be:
   1. an identifier e.g. x
   2. a temporary register e.g. $t0
   3. a function call e.g. call foo(arg1,arg2) 
   4. a typesize e.g. sizeof ptr (sizeof is stored in unop as it is an operator)
   5. a pointer to a string literal (.s[n]) where [n] is the index in string table
   6. an index to an array e.g. x[5]
   7. a struct field selection e.g. x->field

   and be preceded by a unary operator (-,+,not)
   the unary operator may also be "sizeof" iff the register is a typesize
*/

struct reg {
  // 1. exists if a register is an identifier
  const string *ident;
  // 2. exists if a register is a temp register
  int reg_number;
  // 3. exists if a register is a function
  vector<reg*> *parameters;
  // 4. exists if a register is a typesize
  string *typesize;
  // 5. exists if register is pointer to string literal
  int string_index;
  // 6. array selection 
  reg *array_index;
  // 7. struct field selection
  const string *sname;
  const string *field;

  // if 2. stride of type, 3. function name 6. stride of type 
  string *name;
  // optional unary operator
  string *unop;

  // constructors
  reg(const string *ident);
  reg(string *stride, int reg_number);
  reg(string *fname, vector<reg*> *parameters = nullptr);
  reg(string *typesize, string *szof);
  reg(int string_index);
  // reg(const string *array_ident, int array_index, string *array_stride);
  reg(const string *ident,const string *sname, const string *field);

  // functions
  // deep copy register, return ptr to newly allocated object
  reg *deep_copy();
  // stringify a register
  string str();
  // refrence count
  ~reg();
};

/*
    the format of a 3-address code statement depends on 
    the type of instruction,represented by bitset attribute:

    let tn = reg n (defined above)

    ASSIGNMENT (primary expression):
    [LABEL] [t0]  = [t1] [OPERATOR] [t2] 
    
    GOTO:
    goto [LABEL] if not [t0]
    
    LABEL_ONLY:
    [LABEL]

    RETURN:
    [LABEL] return [t0]


*/

struct ac3{
  astree *expr;
  string *label;
  reg *t0;
  string *op;
  reg *t1;
  reg *t2;
  instruction_bitset itype = 0;
  ac3(astree *expr,reg *t0 = nullptr);
  ~ac3();
};

/*
   all functions have an equivalent ac3 table 
   (which is just a collection of 3 address code statements, defined above)
   all global declarations are also encapsulated within an ac3 table
*/

using ac3_table = vector<ac3*>;

/*
  all tables generated are stored in this object.
  store function ac3 tables with function name for easy lookup.
  all strings literals are stored in a vector.
*/

struct all_3ac{
  ac3_table *all_globals;  
  vector<pair<const string*,ac3_table*>> *all_functions;
  vector<const string*> *all_strings;
  all_3ac(ac3_table *all_globals, 
          vector<pair<const string*,ac3_table*>> *all_functions,
          vector<const string*> *all_strings);
};

// creates 3ac tables
int generate_3ac(astree *root, all_tables *table);

// free memory associated with 3ac tables
void free_3ac();

// return all 3ac tables generated by emit_3ac
all_3ac *return_3ac();

// emit all of the statements returned by all_3ac
void emit_all3ac(FILE *out);

#endif
