#ifndef __REG_H_
#define __REG_H_

#include <string>
#include <vector>

using namespace std;

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
  reg(const reg& r);
  virtual ~reg(); // destructor
  void set_unop(string *unop);// functions
  // virtual functions
  virtual reg *deep_copy(); //deep copy register
  virtual string str(); // stringify register
};

struct reg_ident : reg { //1
  const string *ident; // fields

  reg_ident (const string *ident); 
  reg_ident (const reg_ident &r);
  ~reg_ident();

  reg *deep_copy();
  string str();
};

struct reg_temp : reg { //2
  string *stride; 
  int reg_number;

  reg_temp(string *stride, int reg_number); 
  reg_temp(const reg_temp &r);
  ~reg_temp();

  reg *deep_copy();
  string str();
};

struct reg_function_call : reg { // 3
  string *fname;
  vector<reg*> *parameters;

  reg_function_call(string *fname, vector<reg*> *parameters); 
  reg_function_call(const reg_function_call &r);
  ~reg_function_call();

  reg *deep_copy();
  string str();
};

struct reg_typesize : reg { // 4
  string *typesize;

  reg_typesize(string *typesize); 
  reg_typesize(const reg_typesize &r);
  ~reg_typesize();

  reg *deep_copy();
  string str();
};

struct reg_string_pointer : reg { // 5 
  int index; 

  reg_string_pointer(int index); 
  reg_string_pointer(const reg_string_pointer &r);
  ~reg_string_pointer();

  reg *deep_copy();
  string str();
};

struct reg_array_index : reg { //6
  reg *array_ident;
  reg *selection_index;
  string *stride;

  reg_array_index(reg *array_ident, reg *selection_index, string *stride); 
  reg_array_index(const reg_array_index &r);
  ~reg_array_index();

  reg *deep_copy();
  string str();
};

struct reg_selection : reg { //7
  reg *ident; 
  const string *sname;
  const string *field;

  reg_selection(reg *ident, const string *sname, const string *field);
  reg_selection(const reg_selection &r);
  ~reg_selection();

  // using reg::str; 
  reg *deep_copy();
  string str();
  // using reg::deep_copy;
};

#endif
