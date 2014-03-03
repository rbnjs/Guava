%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.6.90.8-d4fe"
%defines
%define parser_class_name "GuavaParser"
%code requires {
# include <string>
class GuavaDriver;
}

%parse-param { GuavaDriver& driver }
%lex-param   { GuavaDriver& driver }

%locations
%initial-action
{
  @$.begin.filename = @$.end.filename = &driver.file;
};
%debug
%error-verbose
//Simbolos
%union
{
    int          intval;
    char         *strval;
    bool         boolval;
    char         charval;
    int          subtok;
    float        realval;
};
%code {
# include "GuavaDriver.hh"
}

%token            END       0 
%right            ASSIGN     
%token <strval>   ID         
%token <intval>   INTEGER    
%token <strval>   STRING
%token <charval>  CHAR       
%token <realval>  REAL       
%token <boolval>  BOOL       
%token TYPE_INTEGER TYPE_REAL TYPE_CHAR TYPE_VOID TYPE_BOOLEAN TYPE_STRING
%token FOR MAIN IF THEN ELSE WHILE DO RETURN BREAK CONTINUE RECORD UNION VAR FUNCTION DECLARE
%token PRINT READ
%left <subtok> COMPARISON
%left AND
%left OR
%left NOT /* Revisar esta */
%left '+' '-' 
%left '*' '/' DIV MOD
%nonassoc PLUSPLUS MINUSMINUS
%right POW
%nonassoc UMINUS
%type <intval> valor
%type <intval> expun expbin
%type <intval> llamadafuncion selectorif loopwhile loopfor asignacion
%type <intval> instruccion
%type <intval> listainstrucciones
%type <intval> lparam
%type <intval> lelseif
%type <intval> funcion 
%type <intval> lfunciones
%type <intval> lvariables
%type <intval> lvar
%type <intval> tipo
%type <intval> bloquedeclare
%type <intval> bloqueprincipal

%start program
%destructor { delete $$; } ID
%% /* Reglas */

program: bloqueprincipal {};

bloqueprincipal: bloquedeclare lfunciones;

bloquedeclare: /* Vacio */  {}
             | DECLARE '{' lvariables '}' {};

lvariables: tipo lvar ';' lvariables      {}
          | tipo lvar ';'                 {};

lvar: ID           {}
    | ID ',' lvar  {};

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' bloquedeclare listainstrucciones '}';

lfunciones: funcionmain        {}
	  | funcion lfunciones {}

funcion: FUNCTION tipo ID '(' lparam ')' '{' bloquedeclare listainstrucciones RETURN ID ';' '}'         {}
       | FUNCTION tipo ID '(' lparam ')' '{' bloquedeclare listainstrucciones RETURN valor ';' '}'      {}
       | FUNCTION TYPE_VOID ID '(' lparam ')' '{' bloquedeclare listainstrucciones RETURN valor ';' '}' {};

lparam: /* Vacio */          {} 
      | tipo ID ',' lparam2  {} 
      | tipo ID              {}

lparam2: tipo ID             {}
       | tipo ID ',' lparam2 {};

listainstrucciones: /* Vacio */                        {}
                  | instruccion ';' listainstrucciones {};

instruccion: asignacion     {}
           | loopfor        {}
           | loopwhile      {}
           | llamadafuncion {}
           | selectorif     {};

asignacion: ID ASSIGN exp {};

loopfor: FOR '(' ID ';' exp ';' asignacion ')' '{' bloquedeclare listainstrucciones '}' {}
       | FOR '(' ID ';' exp ';' exp ')' '{' bloquedeclare listainstrucciones '}'        {};

loopwhile: WHILE '(' exp ')' DO '{' bloquedeclare listainstrucciones '}' {/* aqui pongo codigo */}
         | DO '{' bloquedeclare listainstrucciones '}' WHILE '(' exp ')' {};

selectorif: IF '(' exp ')' THEN '{' bloquedeclare listainstrucciones '}' lelseif {}
          | IF '(' exp ')' THEN instruccion                                      {}
          | IF '(' exp ')' THEN instruccion ELSE instruccion                     {};

lelseif: /* Vacio */                                                               {}
       | ELSE IF '(' exp ')' THEN '{' bloquedeclare listainstrucciones '}' lelseif {}
       | ELSE '{'bloquedeclare listainstrucciones '}'                              {};

llamadafuncion: ID '(' lvarovalor ')' {}
	      | PRINT '(' exp ')'     {}
              | READ  '(' ID  ')'     {};

lvarovalor: /* Vacio */         {}
          | ID , lvarovalor     {}
          | valor , lvarovalor  {}
          | ID                  {}
          | valor               {};

exp: expbin       {}
   | expun        {} 
   | valor        {}
   | ID           {}
   | '(' exp ')'  {};

expbin: exp AND exp          {}
      | exp OR exp           {}
      | exp COMPARISON exp   {}
      | exp '+' exp          {}
      | exp '-' exp          {}
      | exp '*' exp          {}
      | exp '/' exp          {}
      | exp DIV exp          {}
      | exp MOD exp          {}
      | exp POW exp          {};

expun: NOT exp               {}
     | '-' exp %prec UMINUS  {}
     | exp PLUSPLUS          {}
     | exp MINUSMINUS        {};

valor: BOOL  {}
     | STRING   {}
     | CHAR     {}
     | INTEGER  {}
     | REAL     {};

tipo: TYPE_REAL    {}
    | TYPE_INTEGER {}
    | TYPE_BOOLEAN {}
    | TYPE_CHAR    {}
    | TYPE_STRING  {}
    | TYPE_VOID    {};

%%

void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  driver.error (l, m);
}
