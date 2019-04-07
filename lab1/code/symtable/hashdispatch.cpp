// $Id: hashdispatch.cpp,v 1.8 2018-11-07 11:46:10-08 - - $

#include <iostream>
#include <unordered_map>
using namespace std;

string add() { return __PRETTY_FUNCTION__; }
string sub() { return __PRETTY_FUNCTION__; }
string mul() { return __PRETTY_FUNCTION__; }
string div() { return __PRETTY_FUNCTION__; }

using function = string(*)();
unordered_map<char,function> dispatch {
   {'+', add},
   {'-', sub},
   {'*', mul},
   {'/', div},
};

int main() {
   const char ops[] = "+-*/%";
   for (int i = 0; ops[i]; ++i) {
      auto itor = dispatch.find (ops[i]);
      if (itor == dispatch.end()) {
         cout << ops[i] << ": not found" << endl;
      }else {
         auto f = itor->second;
         cout << reinterpret_cast<void*> (f) << " " << f() << endl;
      }
   }
}

//TEST// ./hashdispatch >hashdispatch.lis 2>&1
//TEST// mkpspdf hashdispatch.ps hashdispatch.cpp* hashdispatch.lis

