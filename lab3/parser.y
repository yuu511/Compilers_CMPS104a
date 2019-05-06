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
%token TOK_TYPE_ID TOK_VARDECL

%right  '='
%left   TOK_EQ TOK_NE '<' TOK_LE '>' TOK_GE
%left   '+' '-'
%left   '*' '/' '%'
%right  U_PLUS U_MINUS TOK_NOT
%left   '[' TOK_ARROW TOK_CALL TOK_ALLOC
%nonassoc '('

%start  start


%%

start     : program            { $$ = $1 = nullptr; }
          ;

program   : program structdef  { $$ = $1->adopt($2); }
          | program statement  { $$ = $1->adopt($2); }
          | program error '}'  { $$ = $1; 
	                         destroy ($3);}
          | program error ';'  { $$ = $1; 
	                         destroy ($3);}
	  |                    { $$ = parser::root; }
	  ;
	
structdef : sargs '}' ';'                    { $$ = $1;
                                               destroy ($2);
			                       destroy ($3); }
	  | TOK_STRUCT TOK_IDENT '{' '}' ';' { $$ = $1 ->adopt($2);    
	                                       destroy($3);      
	                                       destroy($4);
					       destroy($5); }
          ;

sargs     : sargs type TOK_IDENT ';'                    { astree* tid = new astree(TOK_TYPE_ID, $2->lloc,"");
                                                          tid ->adopt($2,$3);    
							  $$ = $1->adopt(tid);
                                                          destroy($4); }
          | TOK_STRUCT TOK_IDENT '{' type TOK_IDENT ';' { astree* tid = new astree(TOK_TYPE_ID, $4->lloc,"");
	                                                  tid->adopt($4,$5);
							  $$ = $1->adopt($2,tid);
	                                                  destroy ($3);
							  destroy ($6); } 
	  ;

type      : plaintype                   { $$ = $1; }
          | TOK_ARRAY '<' plaintype '>' { $$ = $1 -> adopt ($3); 
	                                  destroy($2);
					  destroy($4); }
	  ;

plaintype : TOK_INT                                    { $$ = $1; }
          | TOK_VOID                                   { $$ = $1; }
          | TOK_STRING                                 { $$ = $1; }
          | TOK_PTR '<' TOK_STRUCT TOK_IDENT '>'       { $$ = $1 -> adopt($4); 
	                                                 destroy ($3);
	                                                 destroy ($2); 
							 destroy ($5); }
	  ;

statement : vardecl { $$ = $1; }
          ;

vardecl : type TOK_IDENT '=' expr ';' { astree* tid = new astree(TOK_TYPE_ID, $1->lloc,"");
                                         tid->adopt($1,$2);
			                 $3->adopt_sym(tid,TOK_VARDECL);
				         $$ = $3->adopt($4);
				         destroy($5); }
	| type TOK_IDENT ';'          { astree* tid = new astree(TOK_TYPE_ID, $1->lloc,"");
	                                $$ = tid->adopt ($1,$2);
				        destroy($3); }
	 ;

expr    : expr '=' expr              { $$ = $2->adopt ($1, $3); }
        | expr '+' expr              { $$ = $2->adopt ($1, $3); }
        | expr '-' expr              { $$ = $2->adopt ($1, $3); }
        | expr '*' expr              { $$ = $2->adopt ($1, $3); }
        | expr '/' expr              { $$ = $2->adopt ($1, $3); }
        | expr '%' expr              { $$ = $2->adopt ($1, $3); }
        | expr TOK_EQ expr           { $$ = $2->adopt ($1, $3); }
        | expr TOK_NE expr           { $$ = $2->adopt ($1, $3); }
        | expr TOK_LE expr           { $$ = $2->adopt ($1, $3); }
        | expr TOK_GE expr           { $$ = $2->adopt ($1, $3); }
        | expr '<' expr              { $$ = $2->adopt_sym ($1,TOK_LT); 
	                               $2->adopt($3); }
        | expr '>' expr              { $$ = $2->adopt_sym ($1,TOK_GT); 
	                               $2->adopt($3); }
	| constant                   { $$ = $1; }
	| variable                   { $$ = $1; }
        ;


constant : TOK_INTCON    { $$ = $1; }
         | TOK_CHARCON   { $$ = $1; }  
	 | TOK_STRINGCON { $$ = $1; }
	 | TOK_NULLPTR   { $$ = $1; }
	 ;

variable : TOK_IDENT           { $$ = $1; }
         | expr '[' expr ']'   { $$ = $2 ->adopt ($1,$3);
	                         delete ($4); }
	 | expr TOK_ARROW TOK_IDENT { $$ = $2 -> adopt ($1,$3); }
         ;
	                                
         

%% 

const char* parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

