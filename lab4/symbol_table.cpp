#include <bitset>
#include <unordered_set>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;
#include "auxlib.h"
#include "symbol_table.h"
#include "astree.h"
#include "lyutils.h"

vector <symbol_table*> master;
vector <symbol_table*> stack;
symbol_table* struct_t = new symbol_table();
int current_block = 0;
int next_block = 1;


void p_typeid(astree *s){ 
  symbol *sym = new symbol(s,current_block);
  // sym->dump_symbol(stderr);
  // s->dump_node(stderr);
  if (s->children[3]!=nullptr)
    fprintf(stderr,"varaiable declaration!\n");
  else fprintf(stderr,"no var decl!\n");
}

void p_struct (astree *s){
  symbol *sym = new symbol(s,0);
  sym->attributes.set(static_cast<int>(attr::STRUCT));
  sym->dump_symbol(stderr);
}


// Main function,handles all members of language
void gen_table(astree *s){
  switch(s->symbol){
    case TOK_ROOT:
      stack.push_back(new symbol_table());
      master.push_back(stack.back());
      for (astree* child: s->children) gen_table(child);        
      break;
    case TOK_BLOCK:
      for (astree* child: s->children) gen_table(child);        
      break;
    case TOK_TYPE_ID:
      return p_typeid(s);
    case TOK_STRUCT:
      return p_struct(s);
  }
}
