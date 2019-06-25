#include "symbol_table.h"
#include "astree.h"
#include <map>

void emit_3ac(astree *root, all_tables *table, FILE *out);

void free_3ac();

struct ac3 {
  symbol *sym;
  astree *expr;
  string *ret;
  string *op;
  string *t1;
  string *t2;
  string *label;
  ac3(symbol *sym, astree *expr,
       string *label, string *ret, 
       string *op, string *t1, 
       string *t2);
  ~ac3();
};

using ac3_table = vector<ac3*>;
