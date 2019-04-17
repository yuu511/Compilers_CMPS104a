// Based off of cppstrtok.cpp in the class folder
// /Assignments/code/cppstrtok/cppstrtok.cpp
// $Id: cppstrtok.cpp,v 1.3 2019-04-05 14:28:09-07 - - $

// Use cpp to scan a file and print line numbers.
// Print out each input line read in, then strtok it for
// tokens.

#include <string>
using namespace std;

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>

#include "string_set.h"
#include "auxlib.h"
#include "lyutils.h"

const string CPP = "/usr/bin/cpp -nostdinc";
constexpr size_t LINESIZE = 1024;

// strip the file extension any string  
string strp (char* filename){
   string input_stripped = string(basename(filename));
   size_t lastindex = input_stripped.find_last_of(".");
   input_stripped = input_stripped.substr(0,lastindex);
   return input_stripped;
}

// Chomp the last character from a buffer if it is delim.
void chomp (char* string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char* nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}

int main (int argc, char** argv) {
   // const char* execname = basename (argv[0]);
   char* filename = argv[argc-1];
   int exit_status = EXIT_SUCCESS;
   string command = CPP;
   string input_stripped = strp(filename);

   // parse command line arguments
   // based off of the example in 
   // gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
   int opt;
   while ((opt = getopt(argc,argv,"@:D:ly")) != -1 ){  
     switch (opt){ 
       case '@':
         //filler, todo
         DEBUGF(*optarg,filename,116,filename,filename);
         break;
       case 'D':
         command = command + " -D" + std::string(optarg);
         break;
       case 'l': 
         yy_flex_debug = 1;
         break;
       case 'y':
         yydebug = 1;
         break;
       case '?':
         break;
     }
   }
   if (optind > argc){

   }
   // pass the file specified into the preprocessor
   command = command + " " + filename;
   // printf ("command=\"%s\"\n", command.c_str());
   yyin = popen (command.c_str(), "r");
   if (yyin == nullptr) {
     syserrprintf (command.c_str());
     exit (exec::exit_status);
   }else {
     if (yy_flex_debug){
       fprintf(stderr,"-- popen (%s),fileno(yyin) = %d\n",
               command.c_str(),fileno(yyin));
     }
     lexer::newfilename (command);
   }

   return exit_status;
}

