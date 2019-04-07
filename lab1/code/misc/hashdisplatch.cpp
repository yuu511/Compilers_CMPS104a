// $Id: hashdisplatch.cpp,v 1.6 2019-04-05 16:17:22-07 - - $

#include <iostream>
#include <unordered_map>
using namespace std;

void add (void) { cout << __PRETTY_FUNCTION__ << endl; }
void sub (void) { cout << __PRETTY_FUNCTION__ << endl; }
void mul (void) { cout << __PRETTY_FUNCTION__ << endl; }
void div (void) { cout << __PRETTY_FUNCTION__ << endl; }

using fn = void (*)();
unordered_map<char,fn> dispatch {
   {'+', add},
   {'-', sub},
   {'*', mul},
   {'/', div},
};

int main() {
   char ops[] = "+-*/";
   for (int i = 0; ops[i]; ++i) {
      fn f = dispatch[ops[i]];
      cout << ops[i] << ": " << reinterpret_cast<const void*> (f)
           << "->";
      f();
   }
}

