// $Id: oclib.h,v 1.7 2019-04-18 14:06:21-07 - - $

// Bilingual file useable as a header file for both oc and c++.

#ifndef __OCLIB_H__
#define __OCLIB_H__

#ifdef __cplusplus
   using string = char*;
   extern "C" {
   #define END_EXTERN_C }
#else
   #define END_EXTERN_C
#endif

#define SUCCESS 0
#define FAILURE 1
#define BOOL int
#define TRUE 1
#define FALSE 0
#define EOF (-1)

#define assert(expr) if (not (expr)) fail (#expr, __FILE__, __LINE__); 

void fail (string expr, string file, int line);

void putchr (int c);
void putint (int i);
void putstr (string s);

int getchr();
string getstr();
string getln();

END_EXTERN_C

#endif

