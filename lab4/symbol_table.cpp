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

vector <symbol_table> master;
vector <symbol_table> stack;
symbol_table allstructs;
int current_block = 0;
int next_block = 1;

void gen_table(astree *s){
  switch(s->symbol){
    case TOK_ROOT:
      for (astree* child: s->children) astree::print(stdout,child);        
      break;
  }
}
