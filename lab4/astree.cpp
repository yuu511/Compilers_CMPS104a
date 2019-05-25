// $Id: astree.cpp,v 1.17 2019-03-15 14:32:40-07 - - $

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "string_set.h"
#include "lyutils.h"
#include "symbol_table.h"

astree::astree (int symbol_, const location& lloc_, const char* info, 
                attr_bitset attributes_, int block_number_, 
                symbol_table* struct_ptr_) {
   symbol = symbol_;
   lloc = lloc_;
   lexinfo = string_set::intern (info);
   attributes = attributes_;
   block_number = block_number_;
   struct_ptr = struct_ptr_;
   // vector defaults to empty -- no children
}

astree::~astree() {
   while (not children.empty()) {
      astree* child = children.back();
      children.pop_back();
      delete child;
   }
   if (yydebug) {
      fprintf (stderr, "Deleting astree (");
      astree::dump (stderr, this);
      fprintf (stderr, ")\n");
   }
}

astree* astree::adopt (astree* child1, astree* child2) {
   if (child1 != nullptr) children.push_back (child1);
   if (child2 != nullptr) children.push_back (child2);
   return this;
}

astree* astree::adopt_sym (astree* child, int symbol_) {
   symbol = symbol_;
   return adopt (child);
}


void astree::dump_node (FILE* outfile) {
   fprintf (outfile, "%p->{%s %zd.%zd.%zd \"%s\":",
            static_cast<const void*> (this),
            parser::get_tname (symbol),
            lloc.filenr, lloc.linenr, lloc.offset,
            lexinfo->c_str());
   for (size_t child = 0; child < children.size(); ++child) {
      fprintf (outfile, " %p",
               static_cast<const void*> (children.at(child)));
   }
}

void astree::dump_tree (FILE* outfile, int depth) {
   fprintf (outfile, "%*s", depth * 3, "");
   dump_node (outfile);
   fprintf (outfile, "\n");
   for (astree* child: children) child->dump_tree (outfile, depth + 1);
   fflush (nullptr);
}

void astree::dump (FILE* outfile, astree* tree) {
   if (tree == nullptr) fprintf (outfile, "nullptr");
                   else tree->dump_node (outfile);
}

void astree::print (FILE* outfile, astree* tree, int depth) {
   fprintf (outfile, "; %*s", depth * 3, "");
   fprintf (outfile, "%s \"%s\" (%zd.%zd.%zd)\n",
            parser::get_tname (tree->symbol), tree->lexinfo->c_str(),
            tree->lloc.filenr, tree->lloc.linenr, tree->lloc.offset);
   for (astree* child: tree->children) {
      astree::print (outfile, child, depth + 1);
   }
}

void astree::draw (FILE* outfile, astree* tree, int depth) {
   for (int i =0; i<depth; i++){
     fprintf(outfile,"| ");
   }
   const char *tname = parser::get_tname (tree->symbol);
   if (strstr (tname,"TOK_") == tname) tname +=4;
   fprintf (outfile, "%s \"%s\" %zd.%zd.%zd\n",
            tname, tree->lexinfo->c_str(),
            tree->lloc.filenr, tree->lloc.linenr, tree->lloc.offset);
   for (astree* child: tree->children) {
      astree::draw (outfile, child, depth + 1);
   }
}

void destroy (astree* tree1, astree* tree2) {
   if (tree1 != nullptr) delete tree1;
   if (tree2 != nullptr) delete tree2;
}

void errllocprintf (const location& lloc, const char* format,
                    const char* arg) {
   static char buffer[0x1000];
   assert (sizeof buffer > strlen (format) + strlen (arg));
   snprintf (buffer, sizeof buffer, format, arg);
   errprintf ("%s:%zd.%zd: %s", 
              lexer::filename (lloc.filenr), lloc.linenr, lloc.offset,
              buffer);
}

symbol::symbol (astree* ast_, size_t block_nr_){
  attributes = ast_->attributes;  
  sequence = 0;
  fields = ast_->struct_ptr;
  lloc = ast_->lloc;
  block_nr = block_nr_;
  parameters = nullptr;
}

string dump_attributes(attr_bitset a){
  string st;
  for (size_t i = 0; i<a.size();i++){
    if (a[i]){
      switch(i) {
        case static_cast<int>(attr::VOID):
          st.append ("VOID ");
          break;
        case static_cast<int>(attr::INT):
          st.append ("INT ");
          break;
        case static_cast<int>(attr::NULLPTR_T):
          st.append ("NULLPTR_T ");
          break;
        case static_cast<int>(attr::STRING):
          st.append ("STRING ");
          break;
        case static_cast<int>(attr::STRUCT):
          st.append ("STRUCT ");
          break;
        case static_cast<int>(attr::ARRAY):
          st.append ("ARRAY ");
          break;
        case static_cast<int>(attr::FUNCTION):
          st.append ("FUNCTION ");
          break;
        case static_cast<int>(attr::VARIABLE):
          st.append ("VARIABLE ");
          break;
        case static_cast<int>(attr::FIELD):
          st.append ("FIELD ");
          break;
        case static_cast<int>(attr::TYPEID):
          st.append ("TYPEID ");
          break;
        case static_cast<int>(attr::PARAM):
          st.append ("PARAM ");
          break;
        case static_cast<int>(attr::LOCAL):
          st.append ("LOCAL ");
          break;
        case static_cast<int>(attr::LVAL):
          st.append ("LVAL ");
          break;
        case static_cast<int>(attr::CONST):
          st.append ("CONST ");
          break;
        case static_cast<int>(attr::VREG):
          st.append ("VREG ");
          break;
        case static_cast<int>(attr::VADDR):
          st.append ("VADDR ");
          break;
      }
    }
  }
  return st;
}

void symbol::dump_symbol (FILE* outfile) {
  fprintf (outfile, "->%s\n->%zd\n->\n->%zd.%zd.%zd\n->%zd\n->\n",
           dump_attributes(attributes).c_str(),
           sequence, 
           lloc.filenr, lloc.linenr, lloc.offset,
           block_nr);
}
