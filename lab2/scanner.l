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
NUMBER          ([1-9]+{DIGIT}*|[0]([xX]({DIGIT}|[A-Fa-f])+)+)
IDENTIFIER      ({LETTER}({LETTER}|{DIGIT})*)
NOT_IDENTIFIER  ({DIGIT}({LETTER}|{DIGIT})+)
CHRCONST        (’([^\\’\n]|\\[\\’"0nt])’) 
NOT_CHRCONST    (’([^\\’\n]|\\[\\’"0nt])) 
STRINGCONST     (\"([^\\"\n]|\\[\\'"0nt])*\")
NOT_STRINGCONST (\"([^\\"\n]|\\[\\'"0nt])*)

%%
"#".*           { lexer::include(); }
[ \t]+          { }
\n              { lexer::newline(); }

"if"            { return yylval_token (TOK_IF); }
"else"          { return yylval_token (TOK_ELSE); }
"while"         { return yylval_token (TOK_WHILE); }
"return"        { return yylval_token (TOK_RETURN); }
"alloc"         { return yylval_token (TOK_ALLOC); }
"nullptr"       { return yylval_token (TOK_NULLPTR); }
"not"           { return yylval_token (TOK_NOT); }
"int"           { return yylval_token (TOK_INT); }
"string"        { return yylval_token (TOK_STRING);}
"struct"        { return yylval_token (TOK_STRUCT);}
"array"         { return yylval_token (TOK_ARRAY);}
"ptr"           { return yylval_token (TOK_PTR); }
"void"          { return yylval_token (TOK_VOID); }

"=="            { return yylval_token (TOK_EQ); }
"!="            { return yylval_token (TOK_NE); }
"<="            { return yylval_token (TOK_LE); }
">="            { return yylval_token (TOK_GE); }
"->"            { return yylval_token (TOK_ARROW); }

{NUMBER}        { return yylval_token (TOK_INT); }
{IDENTIFIER}    { return yylval_token (TOK_IDENT); } 
{CHRCONST}      { return yylval_token (TOK_CHARCON); } 
{STRINGCONST}   { return yylval_token (TOK_STRINGCON); } 
"+"             { return yylval_token ('+'); }
"-"             { return yylval_token ('-'); }
"*"             { return yylval_token ('*'); }
"/"             { return yylval_token ('/'); }
"%"             { return yylval_token ('%'); }
"="             { return yylval_token ('='); }
","             { return yylval_token (','); }
";"             { return yylval_token (';'); }
"("             { return yylval_token ('('); }
")"             { return yylval_token (')'); }
"["             { return yylval_token ('['); }
"]"             { return yylval_token (']'); }
"{"             { return yylval_token ('}'); }
"}"             { return yylval_token ('}'); }
{NOT_IDENTIFIER} { lexer::badtoken (yytext);
                   return yylval_token (TOK_IDENT);}
{NOT_CHRCONST} { lexer::badtoken (yytext);
                   return yylval_token (TOK_CHARCON);}
{NOT_STRINGCONST} { lexer::badtoken (yytext);
                   return yylval_token (TOK_STRINGCON);}
.               { lexer::badchar (*yytext); }
%%

