// $Id: astree.h,v 1.10 2016-10-06 16:42:35-07 - - $

#ifndef __ASTREE_H__
#define __ASTREE_H__

#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
using namespace std;

#include "auxlib.h"

struct location {
   size_t filenr;
   size_t linenr;
   size_t offset;
};

struct symbol;

using symbol_table = unordered_map<const string*,symbol*>;
using symbol_entry = symbol_table::value_type;

enum class attr {
  VOID, INT, NULLPTR_T, STRING, STRUCT, ARRAY, FUNCTION, VARIABLE,
  FIELD, TYPEID, PARAM, LOCAL, LVAL, CONST, VREG, VADDR, PROTOTYPE,
  BITSET_SIZE
};
using attr_bitset = bitset <static_cast<size_t>(attr::BITSET_SIZE)>;

struct astree {

   // Fields.
   int symbol;               // token code
   location lloc;            // source location
   const string* lexinfo;    // pointer to lexical information
   vector<astree*> children; // children of this n-way node
   const string* sname;      // if structure, name, else nullptr

   // appended fields for asg4
   attr_bitset attributes;
   int block_number;
   symbol_table* struct_ptr;   

   // Functions.
   astree (int symbol, const location&, const char* lexinfo,
           attr_bitset=0, int block_number=0, 
           symbol_table* struct_ptr=nullptr,
           const string* sname = nullptr);
   ~astree();
   astree* adopt (astree* child1, astree* child2 = nullptr);
   astree* adopt_sym (astree* child, int symbol);
   void dump_node (FILE*);
   void dump_tree (FILE*, int depth = 0);
   static void dump (FILE* outfile, astree* tree);
   static void print (FILE* outfile, astree* tree, int depth = 0);
   static void draw (FILE* outfile, astree* tree, int depth = 0);

};


void destroy (astree* tree1, astree* tree2 = nullptr);

void errllocprintf (const location&, const char* format, const char*);

string dump_attributes(attr_bitset a);

#endif

