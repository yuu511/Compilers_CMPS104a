#include "statement_table.h"

statement::statement (astree *expr_,reg *t0_ ){
  expr = expr_;
  t0 = t0_;
  condition = nullptr;
  label = nullptr;
  op = nullptr;
  t1 = nullptr;
  t2 = nullptr;
}

statement::~statement(){
  delete label;
  delete condition;
  delete t0;
  delete op;
  delete t1;
  delete t2;
}
