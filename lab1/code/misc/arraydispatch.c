// $Id: arraydispatch.c,v 1.6 2019-04-03 17:26:09-07 - - $

#include <stdio.h>

void add (void) { printf ("%s\n", __func__); }
void sub (void) { printf ("%s\n", __func__); }
void mul (void) { printf ("%s\n", __func__); }
void div (void) { printf ("%s\n", __func__); }

typedef void (*fn) (void);
fn dispatch[256] = {
   ['+'] = add,
   ['-'] = sub,
   ['*'] = mul,
   ['/'] = div,
};

int main() {
   char ops[] = "+-*/";
   for (int i = 0; ops[i]; ++i) {
      fn f = dispatch[(int)ops[i]];
      printf ("%p ", (void*) f);
      f();
   }
}

