%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.6"
/*%require "2.6.90.8-d4fe"*/
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
    EntradaSalida *classEntradaSalida;

    /*ExpParentizada *classExpParentizada;
    Identificador *classIdentificador;
    Real *classReal;
    Integer *classInteger;
    Char *classChar;
    String *classString;
    Bool *classBool;
    Estructura *classEstructura;
    PlusMinus *classPlusMinus;*/
    Program *classProgram;
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
%type <classLParam> lparam lparam2
%type <classLElseIf> lelseif
%type <classFuncion> funcion funcionmain
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
%type <classProgram> program
%type <classEntradaSalida> entradasalida

%start program
%destructor { delete $$; } ID
%% /* Reglas */

/*LISTO*/
program: bloqueprincipal { *$$ = Program(*$1); };

/*LISTO*/
bloqueprincipal: bloquedeclare lfunciones { *$$ = BloquePrincipal(*$1, *$2); };

/*LISTO*/
bloquedeclare: /* Vacio */                { *$$ = BloqueDeclare(); }
             | DECLARE '{' lvariables '}' { *$$ = BloqueDeclare(*$3); };

/*LISTO*/
lvariables: tipo1 VAR lvar ';' lvariables          { *$$ = LVariables($1, $3, *$5); }
          | tipo1 VAR lvar ';'                     { *$$ = LVariables($1, $3, 0); }
          | tipo1 ARRAY lvararreglo ';'            { *$$ = LVariables($1, $3, 0); }
          | tipo1 ARRAY lvararreglo ';' lvariables { *$$ = LVariables($1, $3, *$5); }
          | ID   UNION lvar ';'                    {}
          | ID   UNION lvar ';' lvariables         {}
          | ID   RECORD lvar ';'                   {}
          | ID   RECORD lvar ';' lvariables        {}
          | union ';' lvariables                   { *$$ = LVariables($1, *$3); }
          | record ';' lvariables                  { *$$ = LVariables($1, *$3); }
          | union  ';'                             { *$$ = LVariables($1, 0); }
          | record ';'                             { *$$ = LVariables($1, 0); };

/*LISTO*/
union: UNION ID '{' lvariables '}' { *$$ = Union(Identificador(std::string($2)), $4); 
                                    };
/*LISTO*/
record: RECORD ID '{' lvariables '}' { *$$ = Record(Identificador(std::string($2)), $4); 
                                        };
/*LISTO*/
lvar: ID           { *$$ = LVar(Identificador(std::string($1)), 0); 
                    }
    | ID ',' lvar  { *$$ = LVar(Identificador(std::string($1)), $3); 
                    };
/*LISTO*/
lvararreglo: ID lcorchetes               { *$$ = LVarArreglo(Identificador(std::string($1)), $2, 0); 
                                         }
           | ID lcorchetes ',' lvararreglo { *$$ = LVarArreglo(Identificador(std::string($1)), $2, $4); 
                                            };
/*LISTO*/
lcorchetes: '[' exp ']'             { *$$ = LCorchetes($2,0); 
                                    }
          | '[' exp ']' lcorchetes  { *$$ = LCorchetes($2,$4); 
                                    };
/*LISTO*/
arreglo: '[' larreglo ']' { *$$ = Arreglo($2); };

/*LISTO*/
larreglo: exp ',' larreglo      { *$$ = LArreglo(*$1,$3); }
        | arreglo ',' larreglo  { *$$ = LArreglo($1,$3);  }
        | exp                   { *$$ = LArreglo(*$1,0);  }
        | arreglo               { *$$ = LArreglo($1,0);};

/*LISTO*/
lfunciones: funcionmain        { *$$ = LFunciones(*$1,0);  }
	        | funcion lfunciones { *$$ = LFunciones(*$1,$2); };

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' bloquedeclare listainstrucciones '}'     { Tipo v = Tipo(std::string("void"));
                                                                                            LParam lp = LParam();
                                                                                            *$$ = Funcion(v,Identificador(std::string("main")),lp,*$7,*$8,0); 
                                                                                          };

/*LISTO*/
funcion: FUNCTION tipo1 ID '(' lparam ')' '{' bloquedeclare listainstrucciones RETURN exp ';' '}' { *$$ = Funcion(*$2,Identificador(std::string($3))
                                                                                                                 ,*$5,*$8,*$9,*$11); 
                                                                                                  }
       | FUNCTION TYPE_VOID ID '(' lparam ')' '{' bloquedeclare listainstrucciones '}'            { Tipo v = Tipo(std::string("void"));
                                                                                                    *$$ = Funcion(v,Identificador(std::string($3)),*$5,*$8,*$9,0);
                                                                                                  };

/*LISTO*/
lparam: /* Vacio */          { *$$ = LParam(); } /* Nuevo alcance */
      | lparam2              { $$ = $1; } 

lparam2: tipo1 ID              { *$$ = LParam(*$1,Identificador(std::string($2)), 0);  } /* Nuevo alcance */
       | tipo1 ID ',' lparam2  { *$$ = LParam(*$1,Identificador(std::string($2)),*$4);};

/*LISTO*/
listainstrucciones: /* Vacio */                        { *$$ = ListaInstrucciones(); }
                  | instruccion ';' listainstrucciones { *$$ = ListaInstrucciones($1,$3); }
                  | instruccion1 listainstrucciones    { *$$ = ListaInstrucciones($1,$2); };

/*LISTO*/
instruccion: asignacion     { $$ = $1; }
           | llamadafuncion { $$ = $1; }
           | MINUSMINUS ID  { *$$ = PlusMinus(Identificador(std::string($2)), 0); }
           | ID MINUSMINUS  { *$$ = PlusMinus(Identificador(std::string($1)), 1); }
           | PLUSPLUS ID    { *$$ = PlusMinus(Identificador(std::string($2)), 2); }
           | ID PLUSPLUS    { *$$ = PlusMinus(Identificador(std::string($1)), 3); }
           | entradasalida  { $$ = $1; };
     
instruccion1: loopfor        { $$ = $1; }
            | loopwhile      { $$ = $1; }
            | selectorif     { $$ = $1; };

/*LISTO*/
asignacion: ID ASSIGN exp            { Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,$3);
                                     }
          | ID lcorchetes ASSIGN exp { Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,*$2,$4);
                                     }
          | ID '.' ID ASSIGN exp     { Identificador id1 = Identificador(std::string($1));
                                       Identificador id2 = Identificador(std::string($3));
                                       *$$ = Asignacion(id1,id2,$5);
                                     }
          | ID ASSIGN arreglo        { Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,*$3);
                                     };

/*LISTO*/
entradasalida: READ '(' lvarovalor ')' { *$$ = EntradaSalida(0, *$3); }
             | PRINT '(' lvarovalor ')'  { *$$ = EntradaSalida(1, *$3); };

/*LISTO*/
loopfor: FOR '(' ID ';' exp ';' asignacion ')' '{' bloquedeclare listainstrucciones '}' { Identificador id = Identificador(std::string($3));
                                                                                          *$$ = LoopFor(id,$5,*$7,*$10,*$11); 
                                                                                        }
       | FOR '(' ID ';' exp ';' exp ')' '{' bloquedeclare listainstrucciones '}'        { Identificador id = Identificador(std::string($3));
                                                                                          *$$ = LoopFor(id,$5,$7,*$10,*$11);
                                                                                        };

/*LISTO*/
loopwhile: WHILE '(' exp ')' DO '{' bloquedeclare listainstrucciones '}' { *$$ = LoopWhile($3,*$7,*$8); }
         | DO '{' bloquedeclare listainstrucciones '}' WHILE '(' exp ')' { *$$ = LoopWhile($8,*$3,*$4); };

/*LISTO*/
selectorif: IF '(' exp ')' THEN '{' bloquedeclare listainstrucciones '}' lelseif { *$$ = SelectorIf($3,$7,$8,$10); }
          | IF '(' exp ')' THEN instruccion                                      { *$$ = SelectorIf($3,$6,0); }
          | IF '(' exp ')' THEN instruccion ELSE instruccion                     { *$$ = SelectorIf($3,$6,$8); };

/*LISTO*/
lelseif: /* Vacio */                                                               { *$$ = LElseIf(); }
       | ELSE IF '(' exp ')' THEN '{' bloquedeclare listainstrucciones '}' lelseif { *$$ = LElseIf($4,*$8,*$9,$11); }
       | ELSE '{'bloquedeclare listainstrucciones '}'                              { *$$ = LElseIf(*$3,*$4); };

/*LISTO*/
llamadafuncion: ID '(' lvarovalor ')' { *$$ = LlamadaFuncion(Identificador(std::string($1)),*$3); };

/*LISTO*****REVISAR LOS CONSTRUCTORES*/                                      
lvarovalor: /* Vacio */   { *$$ = LVaroValor(); }
          | lvarovalor2   { $$ = $1; };      
          
lvarovalor2: exp ',' lvarovalor2     { Exp e = $1;
                                       *$$ = LVaroValor(&e,$3);
                                     }
           | exp                     { Exp e = $1;
                                       *$$ = LVaroValor(&e,0); 
                                     };	   

/*LISTO*/
exp: expbin       { *$$ = Exp($1); }
   | expun        { *$$ = Exp($1); } 
   | valor        { *$$ = Exp($1); }
   | ID           { *$$ = Identificador(std::string($1)); }
   | '(' exp ')'  { *$$ = ExpParentizada($2); };

/*LISTO*/
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
     | exp PLUSPLUS          { std::string str = std::string("++sufijo");
                               ExpUn tmp = ExpUn($1, &str);
                               $$ = &tmp; 
                             }
     | exp MINUSMINUS        { std::string str = std::string("--sufijo");
                               ExpUn tmp = ExpUn($1, &str);
                               $$ = &tmp; 
                             }
     | PLUSPLUS exp         { std::string str = std::string("++prefijo");
                              ExpUn tmp = ExpUn($2, &str);
                              $$ = &tmp; 
                            }
     | MINUSMINUS exp        { std::string str = std::string("--prefijo");
                               ExpUn tmp = ExpUn($2, &str);
                               $$ = &tmp; 
                             }
     | ID lcorchetes         { Exp id = Identificador(std:string($1));
                               ExpUn tmp = ExpUn(id, $2);
                               $$ = &tmp;
                             };
/*LISTO*/
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

/*LISTO*/
tipo: tipo1         { $$ = $1; } 
     | TYPE_VOID    {Tipo tmp = Tipo(std::string("void"));
                      $$ = &tmp;
                    };

/*LISTO*/
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
