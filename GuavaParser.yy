%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.6.90.8-d4fe"
%defines
%define parser_class_name "GuavaParser"
%code requires {
# include <string>
# include "GuavaTree.hh"
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
    /* Clases  */
    Valor *classValor;
    Exp *classExp;
    ExpUn *classExpUn;
    ExpBin *classExpBin;
    LlamadaFuncion *classLlamadaFuncion;
    SelectorIf *classSelectorIf;
    LoopWhile *classLoopWhile;
    LoopFor *classLoopFor;
    Asignacion *classAsignacion;
    Instruccion *classInstruccion;
    ListaInstrucciones *classListaInstrucciones;
    LParam *classLParam;
    LElseIf *classLElseIf;
    Funcion *classFuncion;
    LFunciones *classLFunciones;
    LVariables *classLVariables;
    Union *classUnion;
    Record *classRecord;
    LVar *classLVar;
    LVaroValor *classLVaroValor;
    LVarArreglo *classLVarArreglo;
    Arreglo *classArreglo;
    LArreglo *classLArreglo;
    LCorchetes *classLCorchetes;
    Tipo *classTipo;
    BloqueDeclare *classBloqueDeclare;
    BloquePrincipal *classBloquePrincipal;

    /*ExpParentizada *classExpParentizada;
    Identificador *classIdentificador;
    Real *classReal;
    Integer *classInteger;
    Char *classChar;
    String *classString;
    Bool *classBool;
    Estructura *classEstructura;
    PlusMinus *classPlusMinus;
    Program *classProgram; */
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
%token FOR MAIN IF THEN ELSE WHILE DO RETURN BREAK CONTINUE RECORD UNION VAR FUNCTION DECLARE ARRAY
%token PRINT READ
%left <subtok> COMPARISON
%left UFO
%left AND
%left OR
%left NOT /* Revisar esta */
%left '+' '-' 
%left '*' '/' DIV MOD
%nonassoc PLUSPLUS MINUSMINUS
%right POW
%nonassoc UMINUS
/* Aqui debe ponerse las clases correspondientes. */
%type <classValor> valor
%type <classExp> exp
%type <classExpUn> expun
%type <classExpBin> expbin
%type <classLlamadaFuncion> llamadafuncion 
%type <classSelectorIf> selectorif 
%type <classLoopWhile> loopwhile 
%type <classLoopFor> loopfor 
%type <classAsignacion> asignacion
%type <classInstruccion> instruccion
%type <classListaInstrucciones> listainstrucciones
%type <classLParam> lparam
%type <classLElseIf> lelseif
%type <classFuncion> funcion 
%type <classLFunciones> lfunciones
%type <classLVariables> lvariables
%type <classUnion> union
%type <classRecord> record
%type <classLVar> lvar
%type <classLVaroValor> lvarovalor lvarovalor2
%type <classLVarArreglo> lvararreglo
%type <classArreglo> arreglo
%type <classLArreglo> larreglo
%type <classLCorchetes> lcorchetes
%type <classTipo> tipo
%type <classBloqueDeclare> bloquedeclare
%type <classBloquePrincipal> bloqueprincipal

%start program
%destructor { delete $$; } ID
%% /* Reglas */

program: bloqueprincipal { };

bloqueprincipal: bloquedeclare lfunciones {};

bloquedeclare: /* Vacio */                {}
             | DECLARE '{' lvariables '}' {};

lvariables: tipo VAR lvar ';' lvariables          {}
          | tipo VAR lvar ';'                     {}
          | tipo ARRAY lvararreglo ';'            {}
          | tipo ARRAY lvararreglo ';' lvariables {}
          | ID   UNION lvar ';'                   {}
          | ID   UNION lvar ';' lvariables        {}
          | ID   RECORD lvar ';'                  {}
          | ID   RECORD lvar ';' lvariables       {}
          | union ';' lvariables                  {}
          | record ';' lvariables                 {}
          | union  ';'                            {}
          | record ';'                            {};

union: UNION ID '{' lvariables '}' {};

record: RECORD ID '{' lvariables '}' {};

lvar: ID           {}
    | ID ',' lvar  {};

lvararreglo: ID lcorchetes               {}
           | ID lcorchetes ',' lvararreglo {};

lcorchetes: '[' exp ']'             {}
          | '[' exp ']' lcorchetes  {};

arreglo: '[' larreglo ']' {};

larreglo: exp ',' larreglo      {}
        | arreglo ',' larreglo  {}
        | exp                   {}
        | arreglo               {};

lfunciones: funcionmain        {}
	        | funcion lfunciones {};

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' bloquedeclare listainstrucciones '}'     {};

funcion: FUNCTION tipo ID '(' lparam ')' '{' bloquedeclare listainstrucciones RETURN exp ';' '}'         {}
       | FUNCTION TYPE_VOID ID '(' lparam ')' '{' bloquedeclare listainstrucciones '}' {};

lparam: /* Vacio */          {} 
      | lparam2              {} 

lparam2: tipo ID             {}
       | tipo ID ',' lparam2 {};

listainstrucciones: /* Vacio */                        {}
                  | instruccion ';' listainstrucciones {}
                  | instruccion1 listainstrucciones    {};

instruccion: asignacion     {}
           | llamadafuncion {}
           | ID PLUSPLUS    {}
           | ID MINUSMINUS  {};
     

instruccion1: loopfor        {}
            | loopwhile      {}
            | selectorif     {};
 
asignacion: ID ASSIGN exp            {}
          | ID lcorchetes ASSIGN exp {}
          | ID '.' ID ASSIGN exp     {}
          | ID ASSIGN arreglo        {};

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

lvarovalor: /* Vacio */   {}
          | lvarovalor2   {};      
          
lvarovalor2: exp ',' lvarovalor2     {}
           | exp                     {};	   


exp: expbin       {}
   | expun        {} 
   | valor        {}
   | ID           {}
   | '(' exp ')'  {};

expbin: exp AND exp          {}
      | exp OR exp           {}
      | exp COMPARISON exp   {}
      | exp UFO exp          {}
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
     | exp MINUSMINUS        {}
     | ID '.' ID             {}
     | ID lcorchetes         {};

valor: BOOL     {}
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
