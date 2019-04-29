// $Id: lyutils.cpp,v 1.4 2019-03-15 14:32:40-07 - - $

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxlib.h"
#include "lyutils.h"
#include "string_set.h"

bool lexer::interactive = true;
location lexer::lloc = {0, 1, 0};
size_t lexer::last_yyleng = 0;
vector<string> lexer::filenames;
size_t lexer::last_filenr = -1;
FILE* lexer::string_fp = nullptr;
FILE* lexer::token_fp = nullptr;


astree* parser::root = nullptr;

const string* lexer::filename (int filenr) {
   return &lexer::filenames.at(filenr);
}

void lexer::newfilename (const string& filename) {
   lexer::lloc.filenr = lexer::filenames.size();
   lexer::filenames.push_back (filename);
}

void lexer::advance() {
   if (not interactive) {
      if (lexer::lloc.offset == 0) {
         printf (";%2zd.%3zd: ",
                 lexer::lloc.filenr, lexer::lloc.linenr);
      }
      printf ("%s", yytext);
   }
   lexer::lloc.offset += last_yyleng;
   last_yyleng = yyleng;
}

void lexer::newline() {
   ++lexer::lloc.linenr;
   lexer::lloc.offset = 0;
}

void lexer::badchar (unsigned char bad) {
   char buffer[16];
   snprintf (buffer, sizeof buffer,
             isgraph (bad) ? "%c" : "\\%03o", bad);
   errllocprintf (lexer::lloc, "invalid source character (%s)\n",
                  buffer);
}


int lexer::badtoken (int symbol) {
   errllocprintf (lexer::lloc, "invalid token (%s)\n", yytext);
   return symbol;
}

void lexer::include() {
   size_t linenr;
   static char filename[0x1000];
   assert (sizeof filename > strlen (yytext));
   int scan_rc = sscanf (yytext, "# %zu \"%[^\"]\"", &linenr, filename);
   if (scan_rc != 2) {
      errprintf ("%s: invalid directive, ignored\n", yytext);
   }else {
      if (yy_flex_debug) {
         fprintf (stderr, "--included # %zd \"%s\"\n",
                  linenr, filename);
      }
      lexer::lloc.linenr = linenr - 1;
      lexer::newfilename (filename);
   }
}

void lexer::stringfp(FILE* strfp){
   string_fp = strfp;
}

void lexer::tokenfp(FILE* tokfp){
   token_fp = tokfp;
}

int lexer::token(int symbol){
   yylval = new astree (symbol, lexer::lloc, yytext);
   if ((string_fp == nullptr) | (token_fp == nullptr)){
     exec::exit_status = EXIT_FAILURE;
     fprintf (stderr,"stringset or tokenset fileptr null!");
   }
   /* if the filenumber is different than the last 
    * scanned file number, then print out the name
    * of the new file and update the coords. (2b) */
   if (yylval->lloc.filenr != last_filenr){
     fprintf (token_fp,"# %3zd \"%s\"\n",yylval->lloc.linenr,
              lexer::filenames.back().c_str());
     last_filenr = yylval->lloc.filenr;
   }
   fprintf(token_fp,"  %3zd %3zd.%.3zd %3d %-14s%s\n", 
           yylval->lloc.filenr,
           yylval->lloc.linenr, 
           yylval->lloc.offset, 
           yylval->symbol,
           parser::get_tname(yylval->symbol),
           yylval->lexinfo->c_str());   
           string_set::intern(yylval->lexinfo->c_str());
   return symbol;
}

void yyerror (const char* message) {
   assert (not lexer::filenames.empty());
   errllocprintf (lexer::lloc, "%s\n", message);
}

