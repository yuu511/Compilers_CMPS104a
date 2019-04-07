// $Id: findmap.cpp,v 1.2 2018-11-07 11:46:09-08 - - $

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
   unordered_map<string,int> um;
   for (const string& s: vector<string> {"foo", "bar", "baz"}) {
      const auto& e = um.find (s);
      cout << s << ": ";
      if (e == um.end()) cout << "not found";
                    else cout << e->second;
      cout << endl;
   }
   int i{};
   for (const string& s: vector<string> {"foo", "bar", "baz"}) {
      um.insert ({s, ++i});
   }
   for (const auto& i: um) {
      cout << i.first << ": " << i.second << endl;
   }
   return 0;
}

//TEST// ./findmap >findmap.lis 2>&1
//TEST// mkpspdf findmap.ps findmap.cpp* findmap.lis

