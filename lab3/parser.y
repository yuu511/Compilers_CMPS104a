// $Id: parser.y,v 1.14 2016-10-06 16:26:41-07 - - $

%{

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "lyutils.h"

%}

%debug
%defines
%error-verbose
%token-table
%verbose

%initial-action {
  location lloc  = {0, 0, 0 };
  parser::root = new astree (TOK_ROOT, lloc, "<<ROOT>>");
}

%destructor { destroy ($$); } <>
%printer { astree::dump (yyoutput, $$); } <>

%token TOK_VOID TOK_INT TOK_STRING
%token TOK_IF TOK_ELSE TOK_WHILE TOK_RETURN TOK_STRUCT
%token TOK_NULLPTR TOK_ARRAY TOK_ARROW TOK_ALLOC TOK_PTR
%token TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE TOK_NOT
%token TOK_IDENT TOK_INTCON TOK_CHARCON TOK_STRINGCON
%token TOK_ROOT TOK_BLOCK TOK_CALL TOK_INITDECL

%start  start


%%
start    : program            { $$ = $1 = nullptr; }
         ;

program  : program structdef  { $$ = $1->adopt ($2); }
	 |                    { $$ = parser::root; }
	 ;
	
structdef : TOK_STRUCT TOK_IDENT '{' sargs '}' ';'  { $$ = $1 ->adopt ($2,$4); }
          ;

sargs : TOK_IDENT ';' sargs { $$ = $1; } 
        |
	;

%% 

const char* parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

