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

const string CPP = "/usr/bin/cpp -nostdinc";
constexpr size_t LINESIZE = 1024;

// Chomp the last character from a buffer if it is delim.
void chomp (char* string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char* nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}

// Print the meaning of a signal.
static void eprint_signal (const char* kind, int signal) {
   fprintf (stderr, ", %s %d", kind, signal);
   const char* sigstr = strsignal (signal);
   if (sigstr != nullptr) fprintf (stderr, " %s", sigstr);
}

// Print the status returned from a subprocess.
void eprint_status (const char* command, int status) {
   if (status == 0) return; 
   fprintf (stderr, "%s: status 0x%04X", command, status);
   if (WIFEXITED (status)) {
      fprintf (stderr, ", exit %d", WEXITSTATUS (status));
   }
   if (WIFSIGNALED (status)) {
      eprint_signal ("Terminated", WTERMSIG (status));
      #ifdef WCOREDUMP
      if (WCOREDUMP (status)) fprintf (stderr, ", core dumped");
      #endif
   }
   if (WIFSTOPPED (status)) {
      eprint_signal ("Stopped", WSTOPSIG (status));
   }
   if (WIFCONTINUED (status)) {
      fprintf (stderr, ", Continued");
   }
   fprintf (stderr, "\n");
}


// Run cpp against the lines of the file.
void cpplines (FILE* pipe) {
   int linenr = 1;
   for (;;) {
      char buffer[LINESIZE];
      const char* fgets_rc = fgets (buffer, LINESIZE, pipe);
      if (fgets_rc == nullptr) break;
      chomp (buffer, '\n');
      // printf ("%s:line %d: [%s]\n", filename, linenr, buffer);
      // http://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html
      char inputname[LINESIZE];
      int sscanf_rc = sscanf (buffer, "# %d \"%[^\"]\"",
                              &linenr, inputname);
      if (sscanf_rc == 2) {
         // printf ("DIRECTIVE: line %d file \"%s\"\n", linenr, inputname);
         continue;
      }
      char* savepos = nullptr;
      char* bufptr = buffer;
      for (int tokenct = 1;; ++tokenct) {
         char* token = strtok_r (bufptr, " \t\n", &savepos);
         bufptr = nullptr;
         if (token == nullptr) break;
       //  printf ("token %d.%d: [%s]\n",
       //          linenr, tokenct, token); 
       string_set::intern(token);
      }
      ++linenr;
   }
}

int main (int argc, char** argv) {
   const char* execname = basename (argv[0]);
   char* filename = argv[argc-1];
   int exit_status = EXIT_SUCCESS;
   string command = CPP;
   string input_stripped = string(basename(filename));
   size_t lastindex = input_stripped.find_last_of(".");
   input_stripped = input_stripped.substr(0,lastindex);
   // parse command line arguments
   // based off of the example in https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
   int opt;
   while ((opt = getopt(argc,argv,"@:D:ly")) != -1 ){  
     switch (opt){ 
       case 'D':
         command = command + " -D" + std::string(optarg);
         break;
       case 'l': 
         // yy_flex_debug = 1;
         break;
       case 'y':
         // yyparse = 1;
         break;
       case '?':
         break;
     }
   }
   // pass the file specified into the preprocessor
   command = command + " " + filename;
   // printf ("command=\"%s\"\n", command.c_str());
   FILE* pipe = popen (command.c_str(), "r");
   if (pipe == nullptr) {
      exit_status = EXIT_FAILURE;
      fprintf (stderr, "%s: %s: %s\n",
               execname, command.c_str(), strerror (errno));
   }else {
      cpplines (pipe);
      int pclose_rc = pclose (pipe);
      eprint_status (command.c_str(), pclose_rc);
      if (pclose_rc != 0) exit_status = EXIT_FAILURE;
   }
   // fprintf (stdout,"131: input_stripped : %s",input_stripped.c_str());
   string append = ".str";
   // dump the string table into fn.str
   // string_set::dump(stdout); 
   FILE *strfp;
   string fn =(input_stripped+append);
   strfp = fopen (fn.c_str(),"w");
   if (strfp == NULL) {
      exit_status = EXIT_FAILURE;
      fprintf (stderr, "%s: %s: %s\n",
               execname, command.c_str(), strerror (errno));
   }
   string_set::dump(strfp); 
   if (pclose(strfp) < 0 ) {
      exit_status = EXIT_FAILURE;
      fprintf (stderr, "%s: %s: %s\n",
               execname, command.c_str(), strerror (errno));
   }
   return exit_status;
}

