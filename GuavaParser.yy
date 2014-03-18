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
%type <classInstruccion> instruccion instruccion1
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
%type <classTipo> tipo1
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
 
asignacion: ID ASSIGN exp            { Identificador id = Identificador(std::string($1));
                                       Exp e = $3;
                                       *$$ = Asignacion(id,e);
                                     }
          | ID lcorchetes ASSIGN exp { Identificador id = Identificador(std::string($1));
                                       LCorchetes *lc = $2;
                                       Exp e = $4;
                                       *$$ = Asignacion(id,*lc,e);
                                     }
          | ID '.' ID ASSIGN exp     {  }
          | ID ASSIGN arreglo        {  };

loopfor: FOR '(' ID ';' exp ';' asignacion ')' '{' bloquedeclare listainstrucciones '}' { Identificador id = Identificador(std::string($3));
                                                                                          Exp e1 = $5;
                                                                                          Asignacion *a = $7;
                                                                                          /* Nuevo alcance */
                                                                                          BloqueDeclare *bd = $10;
                                                                                          ListaInstrucciones *li = $11;
                                                                                          *$$ = LoopFor(id,e1,*a,*bd,*li); 
                                                                                        }
       | FOR '(' ID ';' exp ';' exp ')' '{' bloquedeclare listainstrucciones '}'        { Identificador id = Identificador(std::string($3));
                                                                                          Exp e1 = $5;
                                                                                          Exp e2 = $7;
                                                                                          /* Nuevo alcance */
                                                                                          BloqueDeclare *bd = $10;
                                                                                          ListaInstrucciones *li = $11;
                                                                                          *$$ = LoopFor(id,e1,e2,*bd,*li);
                                                                                        };

loopwhile: WHILE '(' exp ')' DO '{' bloquedeclare listainstrucciones '}' { /* Nuevo alcance */
                                                                           BloqueDeclare *bd = $7;
                                                                           ListaInstrucciones *li = $8;
                                                                           Exp e = $3;
                                                                           *$$ = LoopWhile(e,*bd,*li);
                                                                         }
         | DO '{' bloquedeclare listainstrucciones '}' WHILE '(' exp ')' { /* Nuevo alcance */
                                                                           BloqueDeclare *bd = $3;
                                                                           ListaInstrucciones *li = $4;
                                                                           Exp e = $8;
                                                                           *$$ = LoopWhile(e,*bd,*li); 
                                                                         };

selectorif: IF '(' exp ')' THEN '{' bloquedeclare listainstrucciones '}' lelseif { Exp e = $3;
                                                                                   /* Nuevo alcance */
                                                                                   BloqueDeclare *bd = $7;
                                                                                   ListaInstrucciones *li = $8;
                                                                                   LElseIf *le = $10;
                                                                                   *$$ = SelectorIf(e,bd,li,le); 
                                                                                 }
          | IF '(' exp ')' THEN instruccion                                      { Exp e = $3;
                                                                                   Instruccion *i = $6; 
                                                                                   *$$ = SelectorIf(e,i,0);
                                                                                 }
          | IF '(' exp ')' THEN instruccion ELSE instruccion                     { Exp e = $3;
                                                                                   Instruccion *i = $6;
                                                                                   Instruccion *i2 = $8;
                                                                                   *$$ = SelectorIf(e,i,i2);
                                                                                 };

lelseif: /* Vacio */                                                               { *$$ = LElseIf(); }
       | ELSE IF '(' exp ')' THEN '{' bloquedeclare listainstrucciones '}' lelseif { Exp e = $4;
                                                                                     /* Nuevo alcance */
                                                                                     BloqueDeclare *bd = $8;
                                                                                     ListaInstrucciones *li = $9;
                                                                                     LElseIf *lelse = $11;
                                                                                     *$$ = LElseIf(e,*bd,*li,lelse);
                                                                                   }
       | ELSE '{'bloquedeclare listainstrucciones '}'                              { 
                                                                                     /* Nuevo alcance */
                                                                                     BloqueDeclare *bd = $3;
                                                                                     ListaInstrucciones *li = $4;
                                                                                     *$$ = LElseIf(*bd,*li);
                                                                                   };

llamadafuncion: ID '(' lvarovalor ')' { /* Nuevo alcance? */
                                        LVaroValor lv = *$3;
                                        *$$ = LlamadaFuncion(std::string($1),lv); 
                                      }
	      | PRINT '(' lvarovalor ')' {  /* Nuevo alcance? */
                                            LVaroValor lv = *$3; /* Tal vez todo esto sea necesario cambiarlo */
                                            *$$ = LlamadaFuncion(std::string("print"),lv);  
                                         }
              | READ  '(' lvarovalor  ')' { /* Nuevo alcance? */
                                            LVaroValor lv = *$3;
                                            *$$ = LlamadaFuncion(std::string("read"),lv); 
                                          };

lvarovalor: /* Vacio */   { *$$ = LVaroValor(); }
          | lvarovalor2   { $$ = $1; };      
          
lvarovalor2: exp ',' lvarovalor2     {  Exp e = $1;
                                        *$$ = LVaroValor(&e,$3);
                                     }
           | exp                     { Exp e = $1;
                                        *$$ = LVaroValor(&e,0); 
                                     };	   


exp: expbin       { *$$ = Exp($1); }
   | expun        { *$$ = Exp($1); } 
   | valor        { *$$ = Exp($1); }
   | ID           { Identificador id = Identificador($1);
                    *$$ = id; 
                  }
   | '(' exp ')'  { *$$ = ExpParentizada($2); };

expbin: exp AND exp          { *$$ = ExpBin($1,$3,std::string("and")); }
      | exp OR exp           { *$$ = ExpBin($1,$3,std::string("or"));  }
      | exp COMPARISON exp   { int cmpv = $2;
                               switch(cmpv){
                                    case 1:
                                        *$$ = ExpBin($1,$3,std::string(">"));
                                        break;
                                    case 2:
                                        *$$ = ExpBin($1,$3,std::string("<"));
                                        break;
                                    case 3:
                                        *$$ = ExpBin($1,$3,std::string("<="));
                                        break;
                                    case 4:
                                        *$$ = ExpBin($1,$3,std::string(">="));
                                        break;
                                    case 5:
                                        *$$ = ExpBin($1,$3,std::string("="));
                                        break;
                                    case 6:
                                        *$$ = ExpBin($1,$3,std::string("!="));
                                        break;
                               }
                             }
      | exp UFO exp          { *$$ = ExpBin($1,$3,std::string("<=>")); }
      | exp '+' exp          { *$$ = ExpBin($1,$3,std::string("+")); }
      | exp '-' exp          { *$$ = ExpBin($1,$3,std::string("-")); }
      | exp '*' exp          { *$$ = ExpBin($1,$3,std::string("*")); }
      | exp '/' exp          { *$$ = ExpBin($1,$3,std::string("/")); }
      | exp DIV exp          { *$$ = ExpBin($1,$3,std::string("div")); }
      | exp MOD exp          { *$$ = ExpBin($1,$3,std::string("mod")); }
      | exp POW exp          { *$$ = ExpBin($1,$3,std::string("**")); }
      | ID '.' ID            {	Exp id1 = Identificador(std::string($1));
				Exp id2 = Identificador(std::string($3));
                             	*$$ = ExpBin(id1,id2,std::string("."));
                             };

expun: NOT exp               { std::string str = std::string("not");
                               ExpUn tmp = ExpUn($2, &str);
                               $$ = &tmp; 
                             }
     | '-' exp %prec UMINUS  { std::string str = std::string("-");
                               ExpUn tmp = ExpUn($2, &str);
                               $$ = &tmp; 
                             }
     | exp PLUSPLUS          { std::string str = std::string("++");
                               ExpUn tmp = ExpUn($1, &str);
                               $$ = &tmp; 
                             }
     | exp MINUSMINUS        { std::string str = std::string("--");
                               ExpUn tmp = ExpUn($1, &str);
                               $$ = &tmp; 
                             }
     | ID lcorchetes         { LCorchetes* lc;
                               lc = $2;
                               std::string str = std::string($1);
                               Exp id = Identificador(str);
                               ExpUn tmp = ExpUn(id, lc);
                               $$ = &tmp;
                             };

valor: BOOL     { Valor tmp = Bool($1);
                  $$ = &tmp;
                }
     | STRING   { Valor tmp = String($1);
                  $$ = &tmp;
                }
     | CHAR     { Valor tmp = Char($1);
                  $$ = &tmp;
                }
     | INTEGER  { Valor tmp = Integer($1);
                  $$ = &tmp;
                }
     | REAL     { Valor tmp = Real($1);
                  $$ = &tmp;
                };

tipo: tipo1         { $$ = $1; } 
     | TYPE_VOID    {Tipo tmp = Tipo(std::string("void"));
                      $$ = &tmp;
                    };

tipo1: TYPE_REAL    { Tipo tmp = Tipo(std::string("real"));
                      $$ = &tmp;
                    }
     | TYPE_INTEGER { Tipo tmp = Tipo(std::string("integer"));
                      $$ = &tmp;
                    }
     | TYPE_BOOLEAN { Tipo tmp = Tipo(std::string("boolean"));
                      $$ = &tmp;
                    }
     | TYPE_CHAR    { Tipo tmp = Tipo(std::string("character"));
                      $$ = &tmp;
                    }
     | TYPE_STRING  { Tipo tmp = Tipo(std::string("string"));
                      $$ = &tmp;
                    };


%%

void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  driver.error (l, m);
}
