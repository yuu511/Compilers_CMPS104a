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

%destructor { destroy ($$); } <>
%printer { astree::dump (yyoutput, $$); } <>

%initial-action {
   parser::root = new astree (ROOT, {0, 0, 0}, "<<ROOT>>");
}

%token TOK_VOID TOK_INT TOK_STRING
%token TOK_IF TOK_ELSE TOK_WHILE TOK_RETURN TOK_STRUCT
%token TOK_NULLPTR TOK_ARRAY TOK_ARROW TOK_ALLOC TOK_PTR
%token TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE TOK_NOT
%token TOK_IDENT TOK_INTCON TOK_CHARCON TOK_STRINGCON
%token TOK_ROOT TOK_BLOCK TOK_CALL TOK_INITDECL

%right  '='
%left   '+' '-'
%left   '*' '/'
%right  '^'
%right  POS NEG

%start  program


%%
start    :program            { yyparse_astree = $1; };

program  :program structdef  { $$ = $1->adopt ($2); }
         |program function   { $$ = $1->adopt ($2); }
	 |program statement  { $$ = $1->adopt ($2); }
	 |program error '}'  { $$ = $1; }
	 |program error ';'  { $$ = $1; }
	 |                   { $$ = parser::root; }
	 ;
	
structdef : {}

function : {}

statement : {}

%% 

const char* parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

