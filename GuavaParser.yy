%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.6"
/*%require "2.6.90.8-d4fe"*/
%defines
%define parser_class_name "GuavaParser"
%code requires {
# include <string>
# include <iostream>
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
    Identificador *classIdentificador;

    /*ExpParentizada *classExpParentizada;
    Real *classReal;
    Integer *classInteger;
    Char *classChar;
    String *classString;
    Bool *classBool;
    Estructura *classEstructura;*/
    PlusMinus *classPlusMinus;
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
%type <classInstruccion> instruccion
%type <classInstruccion> instruccion1
%type <classListaInstrucciones> listainstrucciones
%type <classLParam> lparam lparam2
%type <classLElseIf> lelseif
%type <classFuncion> funcion funcionmain
%type <classLFunciones> lfunciones
%type <classLVariables> lvariables
%type <classUnion> union
%type <classIdentificador> identificador
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
%type <classProgram> program
%type <classEntradaSalida> entradasalida

%start program
/*%destructor { delete $$; } ID*/
%% /* Reglas */

/*LISTO*/
program: bloqueprincipal { //*$$ = Program(*$1); 
                         };

/*LISTO*/
bloqueprincipal: { 
                   driver.tablaSimbolos.enterScope(); 
                 } 
                 bloquedeclare lfunciones { //*$$ = BloquePrincipal(*$2, *$3); 
                                            };

/*LISTO*/
bloquedeclare: /* Vacio */                { //*$$ = BloqueDeclare(); 
                                            }
             | DECLARE '{' lvariables '}' { //*$$ = BloqueDeclare(*$3); 
                                            };

/*LISTO*/
lvariables: tipo VAR lvar ';' lvariables          { Tipo *tipo = $1; 
                                                    LVar lvar = *$3; 
                                                    std::list<Identificador> lista = lvar.get_list();
                                                    std::cout << lista.size() << '\n';
                                                  }
          | tipo VAR lvar ';'                     { //*$$ = LVariables(*$1, *$3, 0); 
                                                    }
          | tipo lvar ';' lvariables              {}
          | tipo lvar ';'                         {}
          | tipo ARRAY lvararreglo ';'            { //*$$ = LVariables(*$1, *$3, 0); 
                                                    }
          | tipo ARRAY lvararreglo ';' lvariables { //*$$ = LVariables(*$1, *$3, $5); 
                                                    }
          | identificador   UNION lvar ';'                    {}
          | identificador   UNION lvar ';' lvariables         {}
          | identificador   RECORD lvar ';'                   {}
          | identificador   RECORD lvar ';' lvariables        {}
          | union ';' lvariables                   { //*$$ = LVariables(*$1, $3); 
                                                   }
          | record ';' lvariables                  { //*$$ = LVariables(*$1, $3); 
                                                   }
          | union  ';'                             { //*$$ = LVariables(*$1, 0); 
                                                   }
          | record ';'                             { //*$$ = LVariables(*$1, 0); 
                                                   };

/*LISTO*/
union: UNION identificador '{' lvariables '}' { //*$$ = Union(Identificador(std::string($2)), $4); 
                                   };

record: RECORD identificador '{' lvariables '}' { //*$$ = Record(Identificador(std::string($2)), $4); 
                                     };

lvar: identificador           { 
                     LVar tmp = LVar(*$1, 0); 
                     $$ = &tmp; 
                   }
    | identificador ',' lvar  { std::cout << $1 << '\n';
                     LVar tmp = LVar(*$1, $3); 
                     $$ = &tmp;
                   };

/*LISTO*/
lvararreglo: identificador lcorchetes                 { //*$$ = LVarArreglo(Identificador(std::string($1)), $2, 0); 
                                           }
           | identificador lcorchetes ',' lvararreglo { //*$$ = LVarArreglo(Identificador(std::string($1)), $2, $4); 
                                           };

lcorchetes: '[' exp ']'             { LCorchetes tmp =  LCorchetes(*$2,0); 
                                      $$ = &tmp;
                                    }
          | '[' exp ']' lcorchetes  { LCorchetes tmp = LCorchetes(*$2,$4);
                                      $$ = &tmp;
                                    };
/*LISTO*/
lfunciones: funcionmain        { //*$$ = LFunciones(*$1,0);  
                               }
	  | funcion lfunciones { //*$$ = LFunciones(*$1,$2); 
                               };

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' { driver.tablaSimbolos.enterScope();   
                                                 } 
                                                 bloquedeclare listainstrucciones '}'     { /*Tipo v = Tipo(std::string("void"));
                                                                                            LParam lp = LParam();
                                                                                            *$$ = Funcion(v,Identificador(std::string("main")),lp,*$8,*$9,0); 
                                                                                            driver.tablaSimbolos.exitScope(); */
                                                                                          };

/*LISTO*/
funcion: FUNCTION tipo identificador '(' lparam ')' '{' { driver.tablaSimbolos.enterScope();   
                                             }
                                             bloquedeclare listainstrucciones RETURN exp ';' '}' { /**$$ = Funcion(*$2,Identificador(std::string($3))
                                                                                                                 ,*$5,*$9,*$10,*$12); 
                                                                                                   driver.tablaSimbolos.exitScope();*/
                                                                                                  }
       | FUNCTION TYPE_VOID identificador '(' lparam ')' '{' { 
                                                    driver.tablaSimbolos.enterScope();   
                                                  }
                                                 bloquedeclare listainstrucciones '}'            { /*Tipo v = Tipo(std::string("void"));
                                                                                                    *$$ = Funcion(v,Identificador(std::string($3)),*$5,*$9,*$10,0);
                                                                                                    driver.tablaSimbolos.exitScope();*/
                                                                                                  };

/*LISTO*/
lparam: /* Vacio */          { //*$$ = LParam(); 
                            } 
      | lparam2              { //$$ = $1; 
                                } 

lparam2: tipo identificador              { //*$$ = LParam(*$1,Identificador(std::string($2)), LParam());  
                                } 
       | tipo identificador ',' lparam2  { //*$$ = LParam(*$1,Identificador(std::string($2)),*$4);
                                };

/*LISTO*/
listainstrucciones: /* Vacio */                        { //*$$ = ListaInstrucciones(); 
                                                        }
                  | instruccion ';' listainstrucciones { //*$$ = ListaInstrucciones($1,$3); 
                                                        }
                  | instruccion1 listainstrucciones    { //*$$ = ListaInstrucciones($1,$2); 
                                                        };

/*LISTO*/
instruccion: asignacion     { 
                            }
           | llamadafuncion { 
                            }
           | MINUSMINUS identificador  { PlusMinus tmp = PlusMinus(*$2, 0); 
                              //$$ = &tmp; 
                            }
           | identificador MINUSMINUS  { PlusMinus tmp = PlusMinus(*$1, 1); 
                              //$$ = &tmp;
                            }
           | PLUSPLUS identificador    { PlusMinus tmp = PlusMinus(*$2, 2); 
                              $$ = &tmp;
                            }
           | identificador PLUSPLUS    { PlusMinus tmp = PlusMinus(*$1, 3); 
                              $$ = &tmp;
                            }
           | entradasalida  { 
                            };
     
instruccion1: loopfor        { 
                             }
            | loopwhile      { 
                             }
            | selectorif     { 
                             };

/*LISTO*/
asignacion: identificador ASSIGN exp            { /*Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,$3);*/
                                     }
          | identificador lcorchetes ASSIGN exp { /*Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,*$2,$4);*/
                                     }
          | identificador '.' identificador ASSIGN exp     { /*Identificador id1 = Identificador(std::string($1));
                                       Identificador id2 = Identificador(std::string($3));
                                       *$$ = Asignacion(id1,id2,$5);*/
                                     };

/*LISTO*/
entradasalida: READ '(' lvarovalor ')' { //*$$ = EntradaSalida(0, *$3); 
                                       }
             | PRINT '(' lvarovalor ')'  { //*$$ = EntradaSalida(1, *$3); 
                                         };

/*LISTO*/
loopfor: FOR '(' identificador ';' exp ';' asignacion ')' '{' { 
                                                     driver.tablaSimbolos.enterScope();   
                                                   }
                                                   bloquedeclare listainstrucciones '}' { /*Identificador id = Identificador(std::string($3));
                                                                                          *$$ = LoopFor(id,$5,*$7,*$11,*$12); 
                                                                                          driver.tablaSimbolos.exitScope();*/
                                                                                        }
       | FOR '(' identificador ';' exp ';' exp ')' '{' { 
                                              driver.tablaSimbolos.enterScope();   
                                            } 
                                            bloquedeclare listainstrucciones '}'        { /*Identificador id = Identificador(std::string($3));
                                                                                          *$$ = LoopFor(id,$5,$7,*$11,*$12);
                                                                                          driver.tablaSimbolos.exitScope();*/
                                                                                        };

/*LISTO*/
loopwhile: WHILE '(' exp ')' DO '{' { 
                                      driver.tablaSimbolos.enterScope();   
                                    } 
                                    bloquedeclare listainstrucciones '}' { /**$$ = LoopWhile($3,*$8,*$9); 
                                                                           driver.tablaSimbolos.exitScope();*/
                                                                         }
         | DO '{'{ 
                   driver.tablaSimbolos.enterScope();   
                 } 
                  bloquedeclare listainstrucciones '}' WHILE '(' exp ')' { /**$$ = LoopWhile($9,*$4,*$5); 
                                                                           driver.tablaSimbolos.exitScope();*/
                                                                         };

/*LISTO*/
selectorif: IF '(' exp ')' THEN '{' { 
                                      driver.tablaSimbolos.enterScope();   
                                    }
                                    bloquedeclare listainstrucciones '}' lelseif { /**$$ = SelectorIf($3,$8,$9,$11);
                                                                                   driver.tablaSimbolos.exitScope();*/
                                                                                 }
          | IF '(' exp ')' THEN instruccion                                      { //*$$ = SelectorIf($3,$6,0); 
                                                                                 }
          | IF '(' exp ')' THEN instruccion ELSE instruccion                     { //*$$ = SelectorIf($3,$6,$8); 
                                                                                 };

/*LISTO*/
lelseif: /* Vacio */                                                               { //*$$ = LElseIf(); 
                                                                                   }
       | ELSE IF '(' exp ')' THEN '{' { 
                                        driver.tablaSimbolos.enterScope();   
                                      }
                                      bloquedeclare listainstrucciones '}' lelseif { /**$$ = LElseIf($4,*$9,*$10,$12);
                                                                                     driver.tablaSimbolos.exitScope();*/
                                                                                   }
       | ELSE '{' { 
                    driver.tablaSimbolos.enterScope();   
                  }
                  bloquedeclare listainstrucciones '}'                              { /**$$ = LElseIf(*$4,*$5); 
                                                                                      driver.tablaSimbolos.exitScope();*/
                                                                                    };

llamadafuncion: identificador '(' /* enterScope */ 
                                 lvarovalor ')' { //*$$ = LlamadaFuncion(Identificador(std::string($1)),*$3); 
                                                };


lvarovalor: /* Vacio */   { LVaroValor tmp= LVaroValor();
                            $$ = &tmp;
                          }
          | lvarovalor2   { 
                          };      
          
lvarovalor2: exp ',' lvarovalor2     { Exp e = $1;
                                       LVaroValor tmp = LVaroValor(&e,$3);
                                       $$ = &tmp; 
                                     }
           | exp                     { Exp e = $1;
                                       LVaroValor tmp = LVaroValor(&e);
                                       $$ = &tmp; 
                                     };	   

/*Aqui no es necesario poner nada. Revisar esto.*/
exp: expbin       {  
                  }
   | expun        {  
                  } 
   | valor        {  
                  }
   | identificador    { 
                      }
   | '(' exp ')'  { 
                  };

/*Faltan pruebas*/
expbin: exp AND exp          { 
                               ExpBin eb = ExpBin(*$1,*$3,std::string("and"));
                               $$ = &eb;
                             }
      | exp OR exp           { 
                               ExpBin eb = ExpBin(*$1,*$3,std::string("or"));
                               $$ = &eb;
                             }
      | exp COMPARISON exp   { int cmpv = $2;
                               ExpBin eb;
                               switch(cmpv){
                                    case 1:
                                        eb = ExpBin(*$1,*$3,std::string(">"));
                                        $$ = &eb;
                                        break;
                                    case 2:
                                        eb = ExpBin(*$1,*$3,std::string("<"));
                                        $$ = &eb;
                                        break;
                                    case 3:
                                        eb = ExpBin(*$1,*$3,std::string("<="));
                                        $$ = &eb;
                                        break;
                                    case 4:
                                        eb = ExpBin(*$1,*$3,std::string(">="));
                                        $$ = &eb;
                                        break;
                                    case 5:
                                        eb = ExpBin(*$1,*$3,std::string("="));
                                        $$ = &eb;
                                        break;
                                    case 6:
                                        eb = ExpBin(*$1,*$3,std::string("!="));
                                        $$ = &eb;
                                        break;
                               }
                             }
      | exp UFO exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("<=>"));
                               $$ = &eb;
                             }
      | exp '+' exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("+"));
                               $$ = &eb;
                             }
      | exp '-' exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("-"));
                               $$ = &eb;
                             }
      | exp '*' exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("*"));
                               $$ = &eb;
                             }
      | exp '/' exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("/"));
                               $$ = &eb;
                             }
      | exp DIV exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("div"));
                               $$ = &eb; 
                             }
      | exp MOD exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("mod"));
                               $$ = &eb; 
                             }
      | exp POW exp          { ExpBin eb = ExpBin(*$1,*$3,std::string("**"));
                               $$ = &eb; 
                             }
      | identificador '.' identificador { Exp id1 = *$1; 
                                          Exp id2 = *$3;
                                          ExpBin eb = ExpBin(id1,id2,std::string("."));
                             	          $$ = &eb;
                                        };

/* Expresiones unarias probadas y funcionan. */
expun: NOT exp               { std::string str = std::string("not");
                               ExpUn tmp = ExpUn(*$2, &str);
                               $$ = &tmp; 
                             }
     | '-' exp %prec UMINUS  { std::string str = std::string("-");
                               ExpUn tmp = ExpUn(*$2, &str);
                               $$ = &tmp; 
                             }
     | exp PLUSPLUS          { std::string str = std::string("++sufijo");
                               ExpUn tmp = ExpUn(*$1, &str);
                               $$ = &tmp; 
                             }
     | exp MINUSMINUS        { std::string str = std::string("--sufijo");
                               ExpUn tmp = ExpUn(*$1, &str);
                               $$ = &tmp;
                             }
     | PLUSPLUS exp         { std::string str = std::string("++prefijo");
                              ExpUn tmp = ExpUn(*$2, &str);
                              $$ = &tmp; 
                            }
     | MINUSMINUS exp        { 
                               std::string str = std::string("--prefijo");
                               Exp e = *$2;
                               ExpUn tmp = ExpUn(e, &str);
                               $$ = &tmp; 
                             }
     | identificador lcorchetes { Exp id = *$1;
                                  ExpUn tmp = ExpUn(id, $2);
                                  $$ = &tmp;
                                };
/*Funciona*/
valor: BOOL     { Valor tmp = Bool($1);
                  $$ = &tmp;
                }
     | STRING   { Valor tmp = String($1);
                  $$ = &tmp;
                }
     | CHAR     { Valor tmp = Char($1);
                  $$ = &tmp;
                }
     | INTEGER  { Integer tmp;
                  tmp = Integer($1);
                  $$ = &tmp;
                }
     | REAL     { Valor tmp = Real($1);
                  $$ = &tmp;
                }
     | arreglo  {
                  $$ = $1;
                }

/*Funciona*/
tipo: TYPE_REAL     { Tipo tmp = Tipo(std::string("real"));
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


/*Funciona*/
arreglo: '[' larreglo ']' {
                            Arreglo tmp;
                            LArreglo *lr = $2;
                            tmp = Arreglo(lr);
                            $$ = &tmp; 
                          };

/*Funciona. Faltan ejemplos mas interesantes.*/

larreglo: exp ',' larreglo      { 
                                  Exp e = *$1;
                                  LArreglo *l = $3;
                                  LArreglo tmp = LArreglo(e,l); 
                                  $$ = &tmp;
                                }
        | exp                   { 
                                  LArreglo tmp = LArreglo(*$1,0);
                                  $$ = &tmp;
                                 
                                };

identificador: ID { Identificador id = Identificador(std::string($1));
                    $$ = &id;
                  };


%%

void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  driver.error (l, m);
}
