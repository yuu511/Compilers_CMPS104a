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
start     : program            { $$ = $1 = nullptr; }
          ;

program   : program structdef  { $$ = $1->adopt ($2); }
	  |                    { $$ = parser::root; }
	  ;
	
structdef : sargs '}' ';'  { $$ = $1; }
          ;


sargs     : sargs type TOK_IDENT ';'  {$$ = $1 ->adopt($2);}
          | TOK_STRUCT TOK_IDENT '{' type TOK_IDENT ';' { $$ = $1 ->adopt($2,$4); } 
	  | TOK_STRUCT TOK_IDENT '{' { $$ = $1 ->adopt($2);}
	  ;

type      : plaintype                         { $$ = $1; }
          | TOK_ARRAY TOK_LT plaintype TOK_GT { $$ = $1 -> adopt ($3); }
	  ;

plaintype : TOK_VOID                                   { $$ = $1; }
          | TOK_INT                                    { $$ = $1; }
          | TOK_STRING                                 { $$ = $1; }
          | TOK_PTR TOK_LT TOK_STRUCT TOK_IDENT TOK_GT { $$ = $1 -> adopt ($4); }
	  ;

plaintype : 

%% 

const char* parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

