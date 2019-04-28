/* $Id: lexer.l,v 1.8 2019-04-10 14:51:55-07 - - $ */

%{

#include "lyutils.h"

#define YY_USER_ACTION  { lexer::advance(); }

int yylval_token (int symbol) {
   yylval = new astree (symbol, lexer::lloc, yytext);
   return symbol;
}

%}

%option 8bit
%option debug
%option nobackup
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option warn
/*%option verbose*/

LETTER          [A-Za-z_]
DIGIT           [0-9]
VCHAR           ([^\\'\n]|\\[\\'"0nt])
VSTRING         ([^\\"\n]|\\[\\'"0nt])
NUMBER          ([1-9]+{DIGIT}*|0(([xX]({DIGIT}|[A-Fa-f])+)*|[1-7]*))
NOT_NUMBER      (0[8-9][0-9]*|0[xX])
IDENTIFIER      ({LETTER}({LETTER}|{DIGIT})*)
NOT_IDENTIFIER  ({DIGIT}({LETTER}|{DIGIT})+)
CHRCONST        ('{VCHAR}') 
NOT_CHRCONST    ('{VCHAR}*|'{VCHAR}{2,}') 
STRINGCONST     (\"{VSTRING}*\")
NOT_STRINGCONST (\"{VSTRING}*)

%%
"#".*           { lexer::include(); }
[ \t]+          { /* ignore this token */ }
\n              { lexer::newline(); }

"if"            { yylval_token (TOK_IF);        return lexer::token(); }
"else"          { yylval_token (TOK_ELSE);      return lexer::token(); }
"while"         { yylval_token (TOK_WHILE);     return lexer::token(); }
"return"        { yylval_token (TOK_RETURN);    return lexer::token(); }
"alloc"         { yylval_token (TOK_ALLOC);     return lexer::token(); }
"nullptr"       { yylval_token (TOK_NULLPTR);   return lexer::token(); }
"not"           { yylval_token (TOK_NOT);       return lexer::token(); }
"int"           { yylval_token (TOK_INT);       return lexer::token(); }
"string"        { yylval_token (TOK_STRING);    return lexer::token(); }
"struct"        { yylval_token (TOK_STRUCT);    return lexer::token(); }
"array"         { yylval_token (TOK_ARRAY);     return lexer::token(); }
"ptr"           { yylval_token (TOK_PTR);       return lexer::token(); }
"void"          { yylval_token (TOK_VOID);      return lexer::token(); }
                                                                  
{NUMBER}        { yylval_token (TOK_INTCON);    return lexer::token(); }
{IDENTIFIER}    { yylval_token (TOK_IDENT);     return lexer::token(); } 
{CHRCONST}      { yylval_token (TOK_CHARCON);   return lexer::token(); } 
{STRINGCONST}   { yylval_token (TOK_STRINGCON); return lexer::token(); } 
                                                                  
"=="            { yylval_token (TOK_EQ);        return lexer::token(); }
"!="            { yylval_token (TOK_NE);        return lexer::token(); }
"<="            { yylval_token (TOK_LE);        return lexer::token(); }
">="            { yylval_token (TOK_GE);        return lexer::token(); }
"->"            { yylval_token (TOK_ARROW);     return lexer::token(); }
"+"             { yylval_token ('+');           return lexer::token(); }
"-"             { yylval_token ('-');           return lexer::token(); }
"*"             { yylval_token ('*');           return lexer::token(); }
"/"             { yylval_token ('/');           return lexer::token(); }
"%"             { yylval_token ('%');           return lexer::token(); }
"="             { yylval_token ('=');           return lexer::token(); }
"<"             { yylval_token (TOK_LT);        return lexer::token(); }
">"             { yylval_token (TOK_GT);        return lexer::token(); }
","             { yylval_token (',');           return lexer::token(); }
";"             { yylval_token (';');           return lexer::token(); }
"("             { yylval_token ('(');           return lexer::token(); }
")"             { yylval_token (')');           return lexer::token(); }
"["             { yylval_token ('[');           return lexer::token(); }
"]"             { yylval_token (']');           return lexer::token(); }
"{"             { yylval_token ('{');           return lexer::token(); }
"}"             { yylval_token ('}');           return lexer::token(); }

{NOT_NUMBER}      { lexer::badtoken (yytext); }
{NOT_IDENTIFIER}  { lexer::badtoken (yytext); }
{NOT_CHRCONST}    { lexer::badtoken (yytext); }
{NOT_STRINGCONST} { lexer::badtoken (yytext); }
.                 { lexer::badchar (*yytext); }
%%

