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
MANTISSA        ({DIGIT}+\.?{DIGIT}*|\.{DIGIT}+)
EXPONENT        ([Ee][+-]?{DIGIT}+)
TOK_INT         ({MANTISSA}{EXPONENT}?)
NOTNUMBER       ({MANTISSA}[Ee][+-]?)

%%

"#".*           { lexer::include(); }
[ \t]+          { }
\n              { lexer::newline(); }

{TOK_INT}       { return yylval_token (TOK_INT); }
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

{NOTNUMBER}     { lexer::badtoken (yytext);
                  return yylval_token (TOK_INT); }
.               { lexer::badchar (*yytext); }

%%

