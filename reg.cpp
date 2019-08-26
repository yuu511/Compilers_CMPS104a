#include "reg.h"

/* 0. reg parent functions */
reg::reg() {
  unop = nullptr;
}

reg::reg(const reg& r) {
  unop = r.unop ? new string(*r.unop) : nullptr;
}

reg::~reg(){
  delete unop; 
}

void reg::set_unop(string *unop_) {
  unop = unop_; 
}

reg *reg::deep_copy() {
  return new reg(*this);
}

string reg::str(){
  string prefix="";
  if (unop != nullptr) {
    prefix.append(*unop);
    //add space (for readability)
    if (*unop == "sizeof" || *unop == "not") {
      prefix.append(" ");
    }
  }
  return prefix;
}

/* 1. identifier register */
reg_ident::reg_ident(const string *ident_) {
  ident = ident_;
}

reg_ident::reg_ident(const reg_ident &r) 
  : reg(r) {
  ident = r.ident;
}

reg_ident::~reg_ident() {
  ; //nothing to delete
}

reg *reg_ident::deep_copy() {
  return new reg_ident(*this);
}

string reg_ident::str() {
  string fmt_string = reg::str();  
  fmt_string.append(*ident);
  return fmt_string;
}

/* 2. temporary register */
reg_temp::reg_temp(string *stride_, int reg_number_) {
  stride = stride_;
  reg_number = reg_number_;
}

reg_temp::reg_temp(const reg_temp &r) 
  : reg(r) {
  stride = new string(*r.stride);
  reg_number = r.reg_number;
}

reg_temp::~reg_temp() {
  delete stride; 
}

reg *reg_temp::deep_copy() {
  return new reg_temp(*this);
}

string reg_temp::str() {
  string fmt_string = reg::str();
  fmt_string.append("$t");
  fmt_string.append(to_string(reg_number));
  fmt_string.append(*stride);
  return fmt_string;
}

/* 3. function */
reg_function_call::reg_function_call(string *fname_,vector<reg*> *parameters_) {
  fname = fname_;
  parameters = parameters_;
}

reg_function_call::reg_function_call(const reg_function_call &r)
  : reg(r) {
  if (r.parameters) {
    parameters = new vector<reg*>;  
    for (auto itor: *r.parameters) 
      parameters->push_back(itor->deep_copy());
  }
  else {
    parameters = nullptr;   
  }
}

reg_function_call::~reg_function_call() {
  if(parameters){
    for (auto itor : *parameters) delete itor;
  }
  delete parameters;
  delete fname;
}

reg *reg_function_call::deep_copy() {
  return new reg_function_call(*this); 
}

string reg_function_call::str(){
  string fmt_string = reg::str();
  fmt_string.append("call ");
  fmt_string.append(*fname);
  fmt_string.append("(");
  if (parameters->size() > 0){
    fmt_string.append(parameters->at(0)->str());
    for (size_t i = 1; i < parameters->size(); i++){
      fmt_string.append(",");
      fmt_string.append(parameters->at(i)->str());
    }
  }
  fmt_string.append(")");
  return fmt_string;
}

/* 4. typesize */
reg_typesize::reg_typesize(string *typesize_) {
  typesize = typesize_;
}

reg_typesize::~reg_typesize() {
  delete typesize;
}

reg_typesize::reg_typesize(const reg_typesize &r)
  : reg (r) { 
  typesize = new string(*r.typesize);
}

reg *reg_typesize::deep_copy() {
  return new reg_typesize(*this);
}

string reg_typesize::str() {
  string fmt_string = reg::str();
  fmt_string.append(*typesize);
  return fmt_string;
}

/* 5. pointer to string literal */
reg_string_pointer::reg_string_pointer(int index_) {
  index = index_;
}

reg_string_pointer::reg_string_pointer(const reg_string_pointer &r) 
  : reg(r) {
  index = r.index;
}

reg_string_pointer::~reg_string_pointer() {
  ; // nothing to delete
}

reg *reg_string_pointer::deep_copy() {
  return new reg_string_pointer(*this);
}

string reg_string_pointer::str() {
  string fmt_string = reg::str();
  fmt_string.append("(.s");
  fmt_string.append(to_string(index));
  fmt_string.append(")");
  return fmt_string;
}

/* 6. index to array */
reg_array_index::reg_array_index(reg *array_ident_, reg *selection_index_, string *stride_) {
  array_ident = array_ident_;
  selection_index = selection_index_;
  stride = stride_;
}

reg_array_index::reg_array_index(const reg_array_index &r) 
  : reg(r) {
  array_ident = r.array_ident->deep_copy();   
  selection_index = r.selection_index->deep_copy();
  stride = new string(*r.stride);
}

reg_array_index::~reg_array_index() {
  delete array_ident;
  delete selection_index;
  delete stride;
}

reg *reg_array_index::deep_copy() {
  return new reg_array_index(*this);
}
string reg_array_index::str() {
  string fmt_string= reg::str();
  fmt_string.append(array_ident->str());
  fmt_string.append("[");
  fmt_string.append(selection_index->str());
  fmt_string.append(" * ");
  fmt_string.append(*stride);
  fmt_string.append("]");
  return fmt_string;
}

/* 7. selection */
reg_selection::reg_selection(reg *ident_, const string *sname_, const string *field_){
  ident = ident_;
  sname = sname_;
  field = field_;
}

reg_selection::~reg_selection(){
  delete ident;
}

reg_selection::reg_selection(const reg_selection &r)
  : reg(r) {
  ident = r.ident->deep_copy();
  sname = r.sname;
  field = r.field;
}

reg *reg_selection::deep_copy() {
  return new reg_selection(*this);
}

string reg_selection::str(){
  string string_fmt = reg::str();
  string_fmt.append(ident->str());
  string_fmt.append("->");
  string_fmt.append(*sname);
  string_fmt.append(".");
  string_fmt.append(*field);
  return string_fmt;
}
