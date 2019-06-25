#include "symbol_table.h"
#include "astree.h"
#include <map>

void emit_3ac(astree *root, all_tables *table, FILE *out);

void free_3ac();

// instruction bitset for kind of instruction
enum class instruction{
  GOTO,RETURN,ASSIGNMENT,CALL,BITSET_SIZE
};
using instruction_bitset = bitset <static_cast<size_t>(instruction::BITSET_SIZE)>;

struct ac3 {
  symbol *sym;
  astree *expr;
  string *ret;
  string *op;
  string *t1;
  string *t2;
  string *label;
  instruction_bitset itype = 0;
  int last_reg = -1;
  ac3(symbol *sym, astree *expr=nullptr);
  ~ac3();
};

using ac3_table = vector<ac3*>;
