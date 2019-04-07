// $Id: arraydispatch.cpp,v 1.1 2019-04-05 16:05:35-07 - - $

#include <iostream>
#include <unordered_map>
using namespace std;

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
      int s = ops[i];
      fn f = dispatch[ops[i]];
      printf ("%p ", reinterpret_cast<const void*> (f));
      f();
   }
}

