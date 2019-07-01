#include "symbol_table.h"
#include "astree.h"

void emit_3ac(astree *root, all_tables *table, FILE *out);

void free_3ac();

// instruction bitset for kind of instruction
enum class instruction{
  GOTO,ASSIGNMENT,LABEL_ONLY,CALL,BITSET_SIZE
};
using instruction_bitset = bitset <static_cast<size_t>(instruction::BITSET_SIZE)>;

struct reg {
  // exists if a register is a variable
  const string *ident;
  // exists if a register is an actual register
  int reg_number;
  string *stride;
  // all registers may have a unary operator
  string *unop;
  // constructors
  reg(const string *ident);
  reg(string *stride , int reg_number);
  string str();
  ~reg();
};

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
