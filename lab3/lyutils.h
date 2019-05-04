// $Id: lyutils.h,v 1.6 2017-10-05 16:39:39-07 - - $

#ifndef __UTILS_H__
#define __UTILS_H__

// Lex and Yacc interface utility.

#include <string>
#include <vector>
using namespace std;

#include <stdio.h>

#include "astree.h"
#include "auxlib.h"
#include "string_set.h"

#define YYEOF 0

extern FILE* yyin;
extern char* yytext; 
extern int yy_flex_debug;
extern int yydebug;
extern int yyleng; 

int yylex();
int yylex_destroy();
int yyparse();
void yyerror (const char* message);

struct lexer {
   static bool interactive;
   static location lloc;
   static int last_yyleng;
   static vector<string> filenames;
   static const string* filename (int filenr);
   static void newfilename (const string& filename);
   static void advance();
   static void newline();
   static void badchar (unsigned char bad);
   static int badtoken (int symbol);
   static void include();
   /* appended functions and variables */
   static int token(int symbol);
   static size_t last_filenr;
   static FILE* string_fp; 
   static FILE* token_fp;
   static void stringfp(FILE* strfp);
   static void tokenfp(FILE* tokfp);
};

struct parser {
   static astree* root;
   static const char* get_tname (int symbol);
};

#define YYSTYPE_IS_DECLARED
typedef astree* YYSTYPE;
#include "yyparse.h"

#endif

