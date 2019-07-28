#ifndef __3AC_H_
#define __3AC_H_

#include "symbol_table.h"
#include "astree.h"

// generates 3-address code files
int generate_3ac(astree *root, all_tables *table);

// free memory associated with 3ac tables
void free_3ac();

// return object with all generated 3-address code tables
struct all_3ac;
all_3ac *return_3ac();

// emit all of 3-address code statements in file [FILENAME].oil
void emit_all3ac(FILE *out);

/* 
   reg may be:
   1. an identifier e.g. x , 5
   2. a temporary register e.g. $t0 , $t1
   3. a function call e.g. call foo(arg1,arg2) 
   4. a typesize e.g. sizeof ptr (sizeof is stored in unop as it is an operator)
   5. a pointer to a string literal (.s[n]) where [n] is the index in string table
   6. an index to an array e.g. x[5]
   7. a struct field selection e.g. x->field

   and be preceded by a unary operator (-,+,not)
   the unary operator may also be "sizeof" iff the register is a typesize
*/

struct reg { // parent struct
  string *unop;
  reg(); // constructor
  void set_unop(string *unop);// functions
  // virtual functions
  virtual string str(); // stringify register
  virtual reg *deep_copy(); //deep copy register
  virtual ~reg(); // destructor
};

struct reg_ident : reg { //1
  const string *ident; // fields
  reg_ident(const string *ident); // functions
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_ident();
};

struct reg_temp : reg { //2
  string *stride; // fields 
  int reg_number;
  reg_temp(string *stride, int reg_number); // functions
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_temp();
};

struct reg_function_call : reg { // 3
  string *fname; // fields
  vector<reg*> *parameters;
  reg_function_call(string *fname, vector<reg*> *parameters); // functions
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_function_call();
};

struct reg_typesize : reg { // 4
  string *typesize; // fields
  reg_typesize(string *typesize); // functions
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_typesize();
};

struct reg_string_pointer : reg { // 5 
  int index; // fields 
  reg_string_pointer(int index); // functions
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_string_pointer();
};

struct reg_array_index : reg { //6
  reg *array_ident; // fields
  reg *selection_index;
  string *stride;
  reg_array_index(reg *array_ident, reg *selection_index, string *stride); // functions
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_array_index();
};

struct reg_selection : reg { //7
  reg *ident;
  const string *sname;
  const string *field;
  reg_selection(reg *ident, const string *sname, const string *field);
  using reg::str;
  string str();
  using reg::deep_copy;
  reg *deep_copy();
  ~reg_selection();
};

/*
    the format of a 3-address code statement depends on 
    the type of instruction,represented by bitset attribute:

    let tn = reg n (defined above)

    ASSIGNMENT:
    [LABEL] [t0]  = [t1] [OPERATOR] [t2] 
    
    GOTO:
    [LABEL] goto [condition] if [t1] [OPERATOR] [t2]
    
    LABEL_ONLY:
    [LABEL]

    RETURN:
    [LABEL] return [t0]
*/

// instruction bitset for kind of instruction
enum class instruction{
  GOTO,ASSIGNMENT,LABEL_ONLY,RETURN,BITSET_SIZE
};
using instruction_bitset = bitset <static_cast<size_t>(instruction::BITSET_SIZE)>;

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
#endif
