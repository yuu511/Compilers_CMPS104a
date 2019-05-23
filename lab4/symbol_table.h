#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include <bitset>
#include <unordered_map>
#include <string>
#include "astree.h"
#include "auxlib.h"

using namespace std;
struct symbol;

using symbol_table = unordered_map<string*,symbol*>;
using symbol_entry = symbol_table::value_type;

enum class attr {
  VOID, INT, NULLPTR_T, STRING, STRUCT, ARRAY, FUNCTION, VARIABLE,
  FIELD, TYPEID, PARAM, LOCAL, LVAL, CONST, VREG, VADDR, BITSET_SIZE
};
using attr_bitset = bitset <static_cast<size_t>(attr::BITSET_SIZE)>;

struct symbol {
  attr_bitset attributes;
  size_t sequence;
  symbol_table* fields;
  location lloc;
  size_t block_nr;
  vector<symbol*>* parameters;
};

#endif
