%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.7"
%defines
%define parser_class_name "GuavaParser"
%code requires {
# include <string>
class GuavaDriver;
}
#line 10227 "../../doc/bison.texi"
// The parsing context.
%parse-param { GuavaDriver& driver }
%lex-param   { GuavaDriver& driver }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
%debug
%error-verbose
// Symbols.
%union
{
    int          ival;
    std::string  *sval;
    bool         bval;
    char         cval;
};
%code {
# include "GuavaDriver.hh"
}
%token        END      0 "end of file"
%token        ASSIGN     ":="
%token <sval> IDENTIFIER "identifier"
%token <ival> NUMBER     "number"
%token <char> CHAR 
%type  <ival> exp
%printer    { yyoutput << *$$; } "identifier"
%destructor { delete $$; } "identifier"

%printer    { yyoutput << $$; } <ival>
#line 10320 "../../doc/bison.texi"
%%
%start unit;
unit: assignments exp  { driver.result = $2; };

assignments:
  /* Nothing.  */        {}
| assignments assignment {};

assignment:
     "identifier" ":=" exp
       { driver.variables[*$1] = $3; delete $1; };

%left '+' '-';
%left '*' '/';
exp: exp '+' exp   { $$ = $1 + $3; }
   | exp '-' exp   { $$ = $1 - $3; }
   | exp '*' exp   { $$ = $1 * $3; }
   | exp '/' exp   { $$ = $1 / $3; }
   | "identifier"  { $$ = driver.variables[*$1]; delete $1; }
   | "number"      { $$ = $1; };
%%
void
yy::calcxx_parser::error (const yy::calcxx_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
