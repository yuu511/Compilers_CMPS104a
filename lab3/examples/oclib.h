// $Id: oclib.h,v 1.11 2019-04-25 13:03:37-07 - - $

// Bilingual file useable as a header file for both oc and c++.

#ifndef __OCLIB_H__
#define __OCLIB_H__

#ifdef __cplusplus
   extern "C" {
   using string = char*;
#endif

#define SUCCESS 0
#define FAILURE 1
#define BOOL int
#define TRUE 1
#define FALSE 0
#define EOF (-1)

#define assert(expr) {if (not (expr)) fail (#expr, __FILE__, __LINE__);}

void fail (string expr, string file, int line);

void putchr (int chr);
void putint (int num);
void putstr (string str);

int getchr();
string getstr();
string getln();

#ifdef __cplusplus
   }
#endif

#endif

