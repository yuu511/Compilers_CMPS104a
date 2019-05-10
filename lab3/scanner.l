/* $Id: lexer.l,v 1.8 2019-04-10 14:51:55-07 - - $ */

%{

#include "lyutils.h"

#define YY_USER_ACTION  { lexer::advance(); }

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

LETTER       [A-Za-z_]
DIGIT        [0-9]
VCHAR        ([^\\'\n]|\\[\\'"0nt])
VSTRING      ([^\\"\n]|\\[\\'"0nt])
NUMBER       ([1-9]+{DIGIT}*|0(([xX]({DIGIT}|[A-Fa-f])+)*|[1-7]*))
NOT_NUMBER   (0[8-9][0-9]*|0[xX])
IDENT        ({LETTER}({LETTER}|{DIGIT})*)
NOT_IDENT    ({DIGIT}({LETTER}|{DIGIT})+)
CCONST       ('{VCHAR}') 
NOT_CCONST   ('{VCHAR}*|'{VCHAR}{2,}') 
SCONST       (\"{VSTRING}*\")
NOT_SCONST   ((\"{VSTRING}*)|(\"{VSTRING}*(\\[^\\'"0nt])+{VSTRING}*\"))

%%
"#".*           { lexer::include(); }
[ \t]+          { /* ignore this token */ }
\n              { lexer::newline(); }

"if"            {  return lexer::token(TOK_IF);      }
"else"          {  return lexer::token(TOK_ELSE);    }
"while"         {  return lexer::token(TOK_WHILE);   }
"return"        {  return lexer::token(TOK_RETURN);  }
"alloc"         {  return lexer::token(TOK_ALLOC);   }
"nullptr"       {  return lexer::token(TOK_NULLPTR); }
"not"           {  return lexer::token(TOK_NOT);     }
"int"           {  return lexer::token(TOK_INT);     }
"string"        {  return lexer::token(TOK_STRING);  }
"struct"        {  return lexer::token(TOK_STRUCT);  }
"array"         {  return lexer::token(TOK_ARRAY);   }
"ptr"           {  return lexer::token(TOK_PTR);     }
"void"          {  return lexer::token(TOK_VOID);    }

{NUMBER}        { return lexer::token(TOK_INTCON);    }
{IDENT}         { return lexer::token(TOK_IDENT);     } 
{CCONST}        { return lexer::token(TOK_CHARCON);   } 
{SCONST}        { return lexer::token(TOK_STRINGCON); } 
                                                                  
"=="            {  return lexer::token(TOK_EQ);    }
"!="            {  return lexer::token(TOK_NE);    }
"<="            {  return lexer::token(TOK_LE);    }
">="            {  return lexer::token(TOK_GE);    }
"->"            {  return lexer::token(TOK_ARROW); }
"+"             {  return lexer::token('+');       }
"-"             {  return lexer::token('-');       }
"*"             {  return lexer::token('*');       }
"/"             {  return lexer::token('/');       }
"%"             {  return lexer::token('%');       }
"="             {  return lexer::token('=');       }
"<"             {  return lexer::token('<');       }
">"             {  return lexer::token('>');       }
","             {  return lexer::token(',');       }
";"             {  return lexer::token(';');       }
"("             {  return lexer::token('(');       }
")"             {  return lexer::token(')');       }
"["             {  return lexer::token('[');       }
"]"             {  return lexer::token(']');       }
"{"             {  return lexer::token('{');       }
"}"             {  return lexer::token('}');       }

{NOT_NUMBER}      { lexer::badtoken (TOK_INTCON);    }
{NOT_IDENT}       { lexer::badtoken (TOK_IDENT);     }
{NOT_CCONST}      { lexer::badtoken (TOK_CHARCON);   }
{NOT_SCONST}      { lexer::badtoken (TOK_STRINGCON); }
.                 { lexer::badchar (*yytext);        }
%%

