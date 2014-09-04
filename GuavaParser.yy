%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.6"
/*%require "2.6.90.8-d4fe"*/
%defines
%define parser_class_name "GuavaParser"
%code requires {
# include <string>
# include <iostream>
# include <sstream>
# include <list>
# include <utility>
# include <string>
# include <typeinfo>
# include <algorithm>
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
    LCorchetesExp *classLCorchetesExp;
    TypeS *classTipo;
    BloqueDeclare *classBloqueDeclare;
    BloquePrincipal *classBloquePrincipal;
    EntradaSalida *classEntradaSalida;
    Identificador *classIdentificador;
    LAccesoAtributos *classLAccesoAtributos;
    PlusMinus *classPlusMinus;
    Program *classProgram;
    ErrorLoopFor* classErrorLoopFor; 
    ErrorBoolExp* classErrorBoolExp;
    Retorno* classRetorno;
};

%code {
# include "GuavaDriver.hh"

}

%token            END       0 "end of block" 
%right            ASSIGN     
%token <strval>   ID          "identifier"
%token <intval>   INTEGER     "integer value"
%token <strval>   STRING      "string"
%token <charval>  CHAR        "character"
%token <realval>  REAL        "real value"
%token <boolval>  BOOL        "boolean value"
%token TYPE_INTEGER TYPE_REAL TYPE_CHAR TYPE_VOID TYPE_BOOLEAN TYPE_STRING
%token FOR "for loop" MAIN "main function" IF "if" THEN "then" ELSE "else" WHILE "while loop" 
DO "do clause" RETURN "return statement" BREAK "break statement" CONTINUE "continue statement"
RECORD "record" UNION "union" REFERENCE "reference" FUNCTION "function" 
DECLARE "declare statement" ARRAY "array"
%token PRINT "print statement" READ "read statement"
%token <operator> UFO "<=> operator" AND "and operator" OR "or operator" NOT "not operator"
'+' "+ operator" '-' "- operator" '*' "* operator" '/' "/ operator"
DIV "div operator" MOD "mod operator" PLUSPLUS "++ operator" 
MINUSMINUS "-- operator" POW "** operator" UMINUS "unary - operator"
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
%left ','
/* Clases correspondientes. */
%type <classValor> valor
%type <classExp> exp expID /*ESTO ES NUEVO, VER QUE COMENTE ABAJO*/ expBool expAritmetica llamadafuncion
//%type <int> expBool         /* Tipo */
//%type <int> expAritmetica /* Falta el tipo para esto. */
//%type <classLlamadaFuncion> llamadafuncion 
%type <classLAccesoAtributos> lAccesoAtributos
%type <classSelectorIf> selectorif 
%type <classLoopWhile> loopwhile 
%type <classLoopFor> loopfor 
%type <classAsignacion> asignacion
%type <classInstruccion> instruccion
%type <classInstruccion> instruccion1
%type <classListaInstrucciones> listainstrucciones 
%type <classLParam> lparam lparam2
%type <classLElseIf> lelseif lelseif1
%type <classFuncion> funcion funcionmain
%type <classLFunciones> lfunciones lfunciones1
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
%type <classLCorchetesExp> lcorchetesExp
%type <classTipo> tipo
%type <classErrorLoopFor> errorloopfor
%type <classBloqueDeclare> bloquedeclare
%type <classBloquePrincipal> bloqueprincipal
%type <classProgram> program
%type <classEntradaSalida> entradasalida
%type <classErrorBoolExp> errorloopwhile errorif
%type <classRetorno> retorno

%start program
/*%destructor { delete $$; } ID*/
%% /* Reglas */

program: bloqueprincipal { //$$ = Program(*$1); 
                         };

bloqueprincipal: { 
                     tabla_actual.push_front(&driver.tablaSimbolos);
                     driver.tablaSimbolos.enterScope(); 
                     offset_actual.push_front(0);
                 } 

                bloquedeclare lfunciones  { $$ = new BloquePrincipal($2, $3);
                                            if (!error_state) {
                                                //std::cout << "Funciones: " << '\n';
                                                //driver.tablaSimbolos.show(0,identacion+ "  ");
                                                std::cout << "Variables globales: \n";
                                                driver.tablaSimbolos.show(1,identacion+ "  ");
                                            }
                                         };

bloquedeclare: /* Vacio */  { $$ = new BloqueDeclare(-1); 
                            }
             | { declare_scope = driver.tablaSimbolos.currentScope(); 
               }
               DECLARE '{' lvariables '}' { $$ = new BloqueDeclare(declare_scope); 
                                          };

lvariables: lvariables tipo lvar ';'                    { LVariables *tmp = new LVariables($2,$3);
                                                          $1->listaVar = tmp;
                                                          $$ = $1;
                                                          insertar_simboloSimple($3,$2,std::string("var"),&driver,yylloc); 
                                                        }
          | tipo lvar ';'                               { 
                                                          $$ = new LVariables($1,$2);
                                                          insertar_simboloSimple($2,$1,std::string("var"),&driver,yylloc); 
                                                        } 
          | tipo ARRAY lvararreglo ';'                  { 
                                                          insertar_simboloArreglo($3,$1,&driver,yylloc); 
                                                          $$ = new LVariables($1,$3);
                                                        }
          | lvariables tipo ARRAY lvararreglo ';'       { 
                                                          insertar_simboloArreglo($4,$2,&driver,yylloc); 
                                                          LVariables *tmp = new LVariables($2, $4);
                                                          $1->listaVar = tmp;
                                                          $$ = $1;
                                                        }
          | identificador ARRAY lvararreglo ';'         {
                                                          TypeS* tmp = insertar_simboloArregloEstructura($3,$1->identificador,&driver,yylloc);
                                                          LVariables *tmpLV = new LVariables(tmp,$3);
                                                          $$ = tmpLV;
                                                        } 
          | lvariables identificador  ARRAY lvararreglo ';' { 
                                                              TypeS* tmp = insertar_simboloArregloEstructura($4,$2->identificador,&driver,yylloc);
                                                              LVariables *tmpLV = new LVariables(tmp,$4);
                                                              $1->listaVar = tmpLV;
                                                              $$ = $1;
                                                            }
          | identificador UNION lvar ';'                { 
                                                          TypeS* tmp = insertar_simboloEstructura($3,$1->identificador,std::string("unionType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,$3); 
                                                          $$ = tmpLV;
                                                        }
          | lvariables identificador UNION lvar ';'     { 
                                                          TypeS* tmp = insertar_simboloEstructura($4,$2->identificador,std::string("unionType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,$4); 
                                                          $1->listaVar = tmpLV;
                                                          $$ = $1;
                                                        }
          | identificador RECORD lvar                   {
                                                          TypeS* tmp = insertar_simboloEstructura($3,$1->identificador,std::string("recordType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,$3); 
                                                          $$ = tmpLV;
                                                        }
          | lvariables identificador RECORD lvar ';'    { 
                                                          TypeS* tmp = insertar_simboloEstructura($4,$2->identificador,
                                                          std::string("recordType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,$4); 
                                                          $1->listaVar = tmpLV;
                                                          $$ = $1;
                                                        }
          | lvariables  union ';'                       {
                                                          LVariables * tmp = new LVariables($2);
                                                          $1->listaVar = tmp;
                                                          $$ = $1;
                                                        }
          | lvariables  record  ';'                     {
                                                          LVariables * tmp = new LVariables($2);
                                                          $1->listaVar = tmp;
                                                          $$ = $1;
                                                        }
          | union  ';'                                  {
                                                          $$ = new LVariables($1);
                                                        }
          | record ';'                                  {
                                                          $$ = new LVariables($1);
                                                        }
          /*Errores*/
          | tipo lvar error ';'                         {
                                                          /*Error en la declaracion del tipo y modo de la variable*/
                                                          $$ = new LVariables();
                                                        };

union: UNION identificador '{' { 
                                verificar_existencia_tipo($2, &driver,yylloc,true);
                               }
                               lvariables '}' { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                std::string identificador = $2->identificador;
                                                if (!error_state) {
                                                    identacion.erase(0,2);
                                                    std::cout << identacion << "Union " << identificador << " {\n";
                                                    tabla->show(tabla->currentScope(),identacion+ "  "); 
                                                    std::cout << identacion <<"}\n";
                                                }
                                                offset_actual.pop_front();
                                                tabla_actual.pop_front();
                                             }

record: RECORD identificador '{'{
                                    verificar_existencia_tipo($2,&driver,yylloc, false);
                                } 
                               lvariables '}' { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                if (!error_state) {
                                                std::cout << identacion << "Union " << $2->identificador << " {\n";
                                                tabla->show(tabla->currentScope(),identacion+ "  "); 
                                                std::cout << identacion <<"}\n";
                                                identacion.erase(0,2);
                                               }
                                                offset_actual.pop_front();
                                                tabla_actual.pop_front();
                                             }

lvar: identificador           { 
                                LVar *tmp = new LVar();
                                tmp->append(*$1);
                                $$ = tmp;
                              }
    | lvar ',' identificador  { 
                                $3->line = yylloc.begin.line;
                                $3->column = yylloc.begin.column;
                                $1->append(*$3);
                                $$ = $1;
                              }
    /*Errores*/
    | error                   { LVar *tmp = new LVar ();
                                $$ = tmp;
                              }
    | lvar ',' error          { $$ = $1; };

lvararreglo: identificador lcorchetes                  { LVarArreglo* tmp = new LVarArreglo(*$1,*$2);
                                                         $$ = tmp;
                                                       }
            | lvararreglo ',' identificador lcorchetes { $1->append(*$3,*$4);
                                                         $$ = $1;
                                                       }
            /*Errores*/
            | error lcorchetes                         { LVarArreglo* tmp = new LVarArreglo();
                                                        $$ = tmp;
                                                       }
            | lvararreglo ',' error lcorchetes         {
                                                        LVarArreglo* tmp = new LVarArreglo();
                                                        $$ = tmp;
                                                       };



lcorchetes: '[' INTEGER ']'            { 
                                        LCorchetes *tmp =  new LCorchetes(false);
                                        tmp->append($2);
                                        $$ = tmp;
                                       }
          | lcorchetes '[' INTEGER ']' { 
                                         $1->append($3);
                                         $$ = $1; 
                                       }
          /*Errores*/
          | '[' error ']'           {/*Definicion erronea del tamano del arreglo*/
                                      $$ = new LCorchetes(true);
                                    }
          | lcorchetes '[' error ']' {
                                      $$ = new LCorchetes(true);
                                     };

lcorchetesExp: '[' exp ']'               { LCorchetesExp* tmp = new LCorchetesExp();
                                           if($2->get_tipo() == TypeInt::Instance()) {
                                                tmp->tipo = $2->get_tipo();
                                           }
                                            else {
                                                std::string msg = mensaje_error_tipos("integer",$2->get_tipo()->get_name());
                                                driver.error(yylloc,msg);
                                                tmp->tipo = TypeError::Instance();
                                           }
                                           tmp->append($2);
                                           $$ = tmp;
                                         }
             | lcorchetesExp '[' exp ']' { 
                                           if ($3->get_tipo() != TypeInt::Instance()){
                                               std::string msg = mensaje_error_tipos("integer",$3->get_tipo()->get_name());
                                               driver.error(yylloc,msg);
                                               $1->tipo = TypeError::Instance();
                                           }
                                           $1->append($3);
                                           $$ = $1;
                                         }
             | '[' error ']'             {
                                            LCorchetesExp* tmp = new LCorchetesExp();
                                            tmp->tipo = TypeError::Instance();
                                         }
             |  lcorchetesExp '[' error ']' {
                                                LCorchetesExp* tmp = new LCorchetesExp();
                                                tmp->tipo = TypeError::Instance();
                                            };


lfunciones: funcionmain                    { $$ = new LFunciones($1,0);
                                           }
          | lfunciones1 funcionmain        { 
                                             LFunciones* main_ = new LFunciones($2,0);
                                             $1->lista = main_;
                                             $$ = $1;
                                           };

lfunciones1: funcion                       { $$ = new LFunciones($1,0);
                                           }
           | lfunciones1 funcion           { 
                                             LFunciones* func = new LFunciones($2,0);
                                             $1->lista = func;
                                             $$ = $1;
                                           };

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   int line = yylloc.begin.line;
                                                   int column = yylloc.begin.column;
                                                   driver.tablaSimbolos.insert(std::string("main"),std::string("function"),
                                                                                0,tipo,line,column, current_scope);
                                                   identacion += "  ";
                                                   offset_actual.push_front(0);
                                                 } 
           bloquedeclare listainstrucciones  '}' { LParam* lp = new LParam();
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   $$ = new  Funcion(tipo, new Identificador(std::string("main")),lp,$8,$9); 
                                                   if (!error_state) {
                                                       std::cout <<  "main {\n"; 
                                                       std::cout << "Parametros y variables:\n";
                                                       driver.tablaSimbolos.show(current_scope,identacion);
                                                       driver.tablaSimbolos.exitScope(); 
                                                       std::cout << "}\n";
                                                       identacion.erase(0,2);
                                                   }
                                                   $9->show("");
                                                 }
           /*Errores*/
           /*Mala especificacion del encabezado de la funcion*/
           | FUNCTION TYPE_VOID MAIN '(' error ')' '{' { current_scope = driver.tablaSimbolos.enterScope();
                                                         identacion += "  ";
                                                       } 
                 bloquedeclare listainstrucciones  '}' { TypeS* t = TypeError::Instance();
                                                         LParam* lp = new LParam();
                                                         $$ = new Funcion(t, new Identificador(std::string("main")),lp,$9,$10);
                                                       };


funcion: FUNCTION tipo identificador '('  { current_scope = driver.tablaSimbolos.enterScope();
                                            offset_actual.push_front(0);
                                          }
                                        lparam { 
                                                 insertar_funcion($2,$3,$6,&driver,current_scope,yylloc); 
                                                 identacion += "  ";
                                               } ')' '{' 
                                        bloquedeclare listainstrucciones '}' { TypeS* tipo = new TypeFunction($2->get_tipo(),$6->get_tipos());
                                                                               std::list<Instruccion*> lretorno = $11->obtener_return();
                                                                               if (lretorno.size() == 0) {
                                                                                    funcion_sin_return($3,&driver,yylloc); 
                                                                               } else{
                                                                                    if ( verificar_return($3,$2,lretorno,&driver) ){
                                                                                        $$ = new Funcion(tipo,$3,$6,$10,$11);
                                                                                    } else {
                                                                                        $$ = new Funcion();
                                                                                    }
                                                                               }
                                                                               if (!error_state) {
                                                                                    std::cout << $3->identificador << "{\n";
                                                                                    std::cout << "Parametros y variables:\n";
                                                                                    driver.tablaSimbolos.show(current_scope,identacion);
                                                                                    std::cout << "}\n";
                                                                                    driver.tablaSimbolos.exitScope();
                                                                                                identacion.erase(0,2);
                                                                               }
                                                                               $10->show("");
                                                                            }

       | FUNCTION TYPE_VOID identificador '(' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                offset_actual.push_front(0);
                                              } 
                                            lparam  {  
                                                      TypeS* v = TypeVoid::Instance();
                                                      insertar_funcion(v,$3,$6,&driver,current_scope,yylloc); 
                                                      identacion += "  ";
                                                    } ')' '{' 
                                            bloquedeclare listainstrucciones '}'{  TypeS* tipo = new TypeFunction(TypeVoid::Instance(),$6->get_tipos());
                                                                                   $$ = new Funcion(tipo,$3,$6,$10,$11);
                                                                                   if (!error_state) {
                                                                                        std::cout << $3->identificador << "{\n";
                                                                                        std::cout << "Parametros y variables:\n";
                                                                                        driver.tablaSimbolos.show(current_scope,identacion);
                                                                                        std::cout << "}\n";
                                                                                        driver.tablaSimbolos.exitScope();
                                                                                        identacion.erase(0,2);
                                                                                    }
                                                                                    $10->show("");
                                                                                }

       /*Errores*/
       /*Mala especificacion del encabezado de la funcion*/
       | FUNCTION tipo identificador '(' error ')' '{' { current_scope =  driver.tablaSimbolos.enterScope(); 
                                                         identacion += "  ";
                                                       }
                                            bloquedeclare listainstrucciones '}' { $$ = new Funcion(); 
                                                                                                }

       /*Mala especificacion del encabezado de la funcion*/
       | FUNCTION TYPE_VOID identificador '(' error ')' '{' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                              identacion += "  ";
                                                            }
                                            bloquedeclare listainstrucciones '}'           {  $$ = new Funcion();
                                                                                           };
/*LISTO*/
lparam: /* Vacio */          { $$ = new LParam(); 
                             } 
      | lparam2              { $$ = $1; 
                             } 

lparam2: tipo identificador               { LParam* tmp = new LParam(); 
                                            tmp->append($1,$2);
                                            tmp->appendTipo($1);
                                            $$ = tmp;
                                            insertar_simboloSimple($2,$1,std::string("param"),&driver,yylloc);
                                          }       
       | tipo REFERENCE identificador     { LParam* tmp = new LParam(); 
                                            tmp->append($1,$3);
                                            tmp->appendTipo($1);
                                            $$ = tmp;
                                            insertar_simboloSimple($3,$1,std::string("param"),&driver,yylloc); // llamada a otra funcion
                                          } 
       | lparam2 ',' tipo identificador   { 
                                            $1->append($3,$4);
                                            $1->appendTipo($3);
                                            $$ = $1;
                                            insertar_simboloSimple($4,$3,std::string("param"),&driver,yylloc);
                                          }
       | lparam2 ',' tipo REFERENCE identificador       { 
                                                          $1->append($3,$5);
                                                          $1->appendTipo($3);
                                                          $$ = $1;
                                                          insertar_simboloSimple($5,$3,std::string("param"),&driver,yylloc);
                                                        }
       | tipo error                        { $$ = new LParam();    }
       | tipo REFERENCE error              { $$ = new LParam();    }
       | lparam2 ',' tipo error            { $$ = new LParam();    }
       | lparam2 ',' tipo REFERENCE error  { $$ = new LParam();    };


listainstrucciones: /* Vacio */                         { 
                                                            $$ = new ListaInstrucciones(); 
                                                        }
                  | listainstrucciones instruccion ';'  { 
                                                          ListaInstrucciones * result;
                                                          if ( $1->get_tipo() == TypeError::Instance()
                                                               || $2->get_tipo() == TypeError::Instance()) {
                                                             result = new ListaInstrucciones($2,$1); 
                                                             result->tipo = TypeError::Instance();
                                                          }
                                                          else {
                                                             result = new ListaInstrucciones($2,$1); 
                                                          }
                                                          $$ = result;
                                                        }
                  | listainstrucciones instruccion1     {
                                                          ListaInstrucciones * result;
                                                          if ( $1->get_tipo() == TypeError::Instance()
                                                               || $2->get_tipo() == TypeError::Instance()) {
                                                            result = new ListaInstrucciones($2,$1); 
                                                            result->tipo = TypeError::Instance();
                                                          }
                                                          else {
                                                            result = new ListaInstrucciones($2,$1); 
                                                          }
                                                          $$ = result;
                                                        };

instruccion: asignacion     { 
                            }
           | llamadafuncion { 
                            }
           | MINUSMINUS identificador  {
                                         Symbol *id;
                                         PlusMinus *result;
                                         if ( (id = variable_no_declarada($2->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus($2,0);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | identificador MINUSMINUS  { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         if ( (id = variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus($1,1);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | PLUSPLUS identificador    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         if ( (id = variable_no_declarada($2->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus($2,2);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | identificador PLUSPLUS    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         if ( (id = variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus($1,3);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | entradasalida  { 
                            }
           | CONTINUE       {
                              $$ = new ContinueBreak(0);
                            }
           | BREAK          {
                              $$ = new ContinueBreak(1);
                            }

           /*Errores*/
           | error identificador       {/*Error en la especificacion del incremento o decremento*/
                                         $$ = new Error();
                                       }
           | identificador error       {/*Error en la especificacion del incremento o decremento*/
                                         $$ = new Error();
                                       }
           | retorno                   {
                                       }



instruccion1: loopfor        { 
                             }
            | loopwhile      { 
                             }
            | selectorif     { 
                             };

asignacion: expID ASSIGN exp   { /*Caso en el que alguno de los dos tipos sea de tipo error.*/
                                 if ($1->get_tipo() == TypeError::Instance() ||
                                     $3->get_tipo() == TypeError::Instance()){
                                     if ($1->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos($3->get_tipo()->get_name(),"null");
                                        driver.error(yylloc, msg);
                                     } else if ($3->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos($1->get_tipo()->get_name(),"null");
                                        driver.error(yylloc, msg);
                                     } else {
                                        std::string msg = mensaje_error_tipos($1->get_tipo()->get_name(), $3->get_tipo()->get_name());
                                        driver.error(yylloc, msg);
                                     }
                                    $$ = new Asignacion();
                                 } else {
                                    $$ = new Asignacion($1,$3);
                                 }
                               } 
          /*Errores*/
          | error ASSIGN exp   {
                                 $$ = new Asignacion();
                               }
          | expID ASSIGN error {
                                 $$ = new Asignacion();
                               };

/* Estas verificaciones se hacen a tiempo de ejecucion. */
entradasalida: READ '(' exp ')'   {
                                    EntradaSalida* tmp = new EntradaSalida(0,$3);  
                                    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos("type","error");
                                        driver.error(yylloc,msg);
                                    }
                                    $$ = tmp;
                                  }
             | PRINT '(' exp ')'  { 
                                    EntradaSalida* tmp = new EntradaSalida(1,$3);  
                                    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos("type","error");
                                        driver.error(yylloc,msg);
                                    }
                                    $$ = tmp;
                                  };

retorno: RETURN       { 
			    $$ = new Retorno(0); 
                          }
       | RETURN exp   {
			    Retorno* tmp =  new Retorno($2); 
			    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                std::string msg = mensaje_error_tipos("type","error");
                                driver.error(yylloc,msg);
			    }
                            $$ = tmp;
                          }

loopfor: FOR '(' identificador ';' expBool ';' errorloopfor ')' '{' { 
                                                                      variable_no_declarada($3->identificador,&driver,yylloc, tabla_actual.front()); 
                                                                      driver.tablaSimbolos.enterScope();   
                                                                      identacion += "  "; 
                                                                    }
                                
                                bloquedeclare listainstrucciones '}' {  ErrorLoopFor* asign_exp = $7;
                                                                            LoopFor* tmp;
                                                                            if (asign_exp->is_error()
                                                                                    || $3->get_tipo() == TypeError::Instance()
                                                                                    || $5->get_tipo() == TypeError::Instance()
                                                                               ){
                                                                                tmp = new LoopFor();
                                                                                std::string msg = mensaje_error_tipos("error","void");
                                                                                driver.error(yylloc,msg);
                                                                            } else{
                                                                                if (asign_exp->exp != 0){
                                                                                    tmp = new 
                                                                                        LoopFor($3, $5,asign_exp->exp,$11,$12);
                                                                                    tmp->tipo = TypeVoid::Instance();
                                                                                } else {
                                                                                    tmp = new 
                                                                                        LoopFor($3, $5,asign_exp->asign,$11,$12);
                                                                                    tmp->tipo = TypeVoid::Instance();
                                                                                }
                                                                            }
                                                                            $$ = tmp;
                                                                            if (!error_state) {
                                                                                std::cout << identacion << "for {\n";
                                                                                int cscope = driver.tablaSimbolos.currentScope();
                                                                                driver.tablaSimbolos.show(cscope,identacion+ "  ");
                                                                                std::cout << identacion << "}\n";
                                                                                driver.tablaSimbolos.exitScope();
                                                                                identacion.erase(0,2);
                                                                            }
                                                                         }
       /*Errores*/
       | FOR '(' error ';' expBool ';' errorloopfor ')' '{' { 
                                                            }
                        bloquedeclare listainstrucciones '}' { 
                                                                   $$ = new LoopFor();
                                                                 }
       | FOR '(' identificador ';' error  ';' errorloopfor ')' '{' { 
                                                                     variable_no_declarada($3->identificador,&driver,yylloc, tabla_actual.front());
                                                                   }
                                bloquedeclare listainstrucciones '}' { 
                                                                           $$ = new LoopFor();
                                                                         };

/**
 * Regla utilizada en el manejo de errores del encabezado de una iteracion
 * acotada
 */
errorloopfor : asignacion {
                            $$ = new ErrorLoopFor($1);
                          }
             | exp        {
                            $$ = new ErrorLoopFor($1);
                          }
             | error      {
                            $$ = new ErrorLoopFor();
                          };

loopwhile: WHILE '(' errorloopwhile ')' DO '{' { 
                                                 driver.tablaSimbolos.enterScope();   
                                                 identacion += "  ";
                                               }
                  bloquedeclare listainstrucciones '}' { 
                                                             LoopWhile* result;
                                                             ErrorBoolExp* exp_bool = $3;
                                                             if (exp_bool->get_error()
                                                                 || exp_bool->get_tipo() == TypeError::Instance()
                                                                 || $9->get_tipo() == TypeError::Instance()){
                                                                 result = new LoopWhile();
                                                                 std::string msg = mensaje_error_tipos("error","void");
                                                                 driver.error(yylloc,msg);
                                                             } 
                                                             else {
                                                                 result = new LoopWhile(exp_bool->exp,$8,$9);
                                                             }
                                                             $$ = result;
                                                             if (!error_state) {
                                                                 std::cout << identacion << "while {\n"; 
                                                                 driver.tablaSimbolos.show(driver.tablaSimbolos.currentScope(),identacion+"  ");
                                                                 std::cout << identacion << "}\n ";
                                                                 driver.tablaSimbolos.exitScope();
                                                                 identacion.erase(0,2);
                                                             }
                                                           }
         | DO '{' { 
                    driver.tablaSimbolos.enterScope();   
                    identacion += "  ";
                  } 
           bloquedeclare listainstrucciones '}' WHILE '(' errorloopwhile ')' { 
                                                                                   LoopWhile* result;
                                                                                   ErrorBoolExp* exp_bool = $9;
                                                                                   if (exp_bool->get_error()
                                                                                       || exp_bool->get_tipo() == TypeError::Instance()
                                                                                       || $5->get_tipo() == TypeError::Instance()){
                                                                                       result = new LoopWhile();
                                                                                       std::string msg = mensaje_error_tipos("error","void");
                                                                                       driver.error(yylloc,msg);
                                                                                   } 
                                                                                   else {
                                                                                       result = new LoopWhile(exp_bool->exp,$4,$5);
                                                                                   }
                                                                                   $$ = result;
                                                                                   if (!error_state) {
                                                                                       std::cout << identacion << "while {\n";
                                                                                       driver.tablaSimbolos.show(driver.tablaSimbolos.currentScope(),identacion+"  ");
                                                                                       std::cout << identacion << "}\n ";
                                                                                       driver.tablaSimbolos.exitScope();
                                                                                       identacion.erase(0,2);
                                                                                   }
                                                                                 };
/**
 * Regla utilizada para el manejo de errores en iteraciones indeterminadas.
 */
errorloopwhile: exp    {
                             if ( $1 == 0 || $1->get_tipo() != TypeBool::Instance()){
                                $$ = new ErrorBoolExp();
                             } else {
                                $$ = new ErrorBoolExp($1);
                             }
                            }
               | error      {
                              $$ = new ErrorBoolExp();
                            };

selectorif: IF '(' errorif ')' THEN '{' { 
                                          driver.tablaSimbolos.enterScope();   
                                          identacion += "  ";
                                        }
                bloquedeclare listainstrucciones '}' lelseif { 
                                                               ErrorBoolExp* err_exp = $3;
                                                               SelectorIf * result;
                                                               if (err_exp->get_error()
                                                                   || err_exp->get_tipo() == TypeError::Instance()
                                                                   || $9->get_tipo() == TypeError::Instance()){
                                                                   result = new SelectorIf(); 
                                                                   std::string msg = mensaje_error_tipos("error","void");
                                                                   driver.error(yylloc,msg);
                                                               } 
                                                               else {
                                                                   result = new SelectorIf(err_exp->exp,$8,$9,$11);
                                                               }
                                                               $$ = result;
                                                               driver.tablaSimbolos.exitScope();
                                                               identacion.erase(0,2);
                                                             }
          | IF '(' errorif ')' THEN instruccion ';'          { 
                                                               ErrorBoolExp* err_exp = $3;
                                                               SelectorIf * result;
                                                               if (err_exp->get_error()
                                                                   || err_exp->get_tipo() == TypeError::Instance()
                                                                   || $6->get_tipo() == TypeError::Instance()){
                                                                   result = new SelectorIf(); 
                                                                   std::string msg = mensaje_error_tipos("error","void");
                                                                   driver.error(yylloc,msg);
                                                               } 
                                                               else {
                                                                   result = new SelectorIf(err_exp->exp,$6,0);
                                                               }
                                                               $$ = result;
                                                             }
          | IF '(' errorif ')' THEN instruccion ELSE instruccion ';' { 
                                                                       ErrorBoolExp* err_exp = $3;
                                                                       SelectorIf * result;
                                                                       if (err_exp->get_error()
                                                                          || err_exp->get_tipo() == TypeError::Instance()
                                                                          ){
                                                                           result = new SelectorIf(); 
                                                                           std::string msg = mensaje_error_tipos("error","void");
                                                                           driver.error(yylloc,msg);
                                                                       } 
                                                                       else {
                                                                           result = new SelectorIf(err_exp->exp,$6,$8);
                                                                       }
                                                                       $$ = result;
                                                                     };


lelseif: /* Vacio */                                                { 
                                                                      $$ = new LElseIf(false);
                                                                    }
       | lelseif1 ELSE '{' { 
                             driver.tablaSimbolos.enterScope();   
                           }
                        bloquedeclare listainstrucciones '}'        { 
                                                                      LElseIf* result; 
                                                                      if ( $1->get_tipo() == TypeError::Instance()
                                                                           || $6->get_tipo() == TypeError::Instance() ){
                                                                          result = new LElseIf(true);
                                                                          std::string msg = mensaje_error_tipos("error","void");
                                                                          driver.error(yylloc,msg);
                                                                      } 
                                                                      else {
                                                                          result = new LElseIf($5,$6);
                                                                          result->lelseif = $1;
                                                                      }
                                                                      $$ = result;
                                                                      driver.tablaSimbolos.exitScope();
                                                                    }
        | ELSE '{' { driver.tablaSimbolos.enterScope();
                   }
                   bloquedeclare listainstrucciones '}'            {
                                                                      LElseIf* result; 
                                                                      if ( 
                                                                           $5->get_tipo() == TypeError::Instance() ){
                                                                          result = new LElseIf(true);
                                                                          std::string msg = mensaje_error_tipos("error","void");
                                                                          driver.error(yylloc,msg);
                                                                      } 
                                                                      else {
                                                                          result = new LElseIf($4,$5);
                                                                      }
                                                                      $$ = result;
                                                                    }
        | lelseif1                                                  { };
        


lelseif1: ELSE IF '(' errorif ')' THEN '{' { 
                                             driver.tablaSimbolos.enterScope();   
                                            }
                            bloquedeclare listainstrucciones '}' {
                                                                   LElseIf* result; 
                                                                   if ( 
                                                                         $4->get_error()
                                                                        || $4->get_tipo() == TypeError::Instance()
                                                                        || $10->get_tipo() == TypeError::Instance()) {
                                                                       result = new LElseIf(true);
                                                                       std::string msg = mensaje_error_tipos("error","void");
                                                                       driver.error(yylloc,msg);
                                                                   } 
                                                                   else {
                                                                       result = new LElseIf($4->exp,$9,$10);
                                                                   }
                                                                   $$ = result;
                                                                   driver.tablaSimbolos.exitScope();
                                                                 }
        | lelseif1 ELSE IF '(' errorif ')' THEN '{' { 
                                                      driver.tablaSimbolos.enterScope();   
                                                    }
                            bloquedeclare listainstrucciones '}' {
                                                                   LElseIf* result; 
                                                                   if ( $1->get_tipo() == TypeError::Instance()
                                                                        || $5->get_error()
                                                                        || $5->get_tipo() == TypeError::Instance()
                                                                        || $11->get_tipo() == TypeError::Instance()) {
                                                                       result = new LElseIf(true);
                                                                       std::string msg = mensaje_error_tipos("error","void");
                                                                       driver.error(yylloc,msg);
                                                                   } 
                                                                   else {
                                                                       result = new LElseIf($5->exp,$10,$11,$1);
                                                                   }
                                                                   $$ = result;
                                                                   driver.tablaSimbolos.exitScope();
                                                                 };
/**
 * Regla utilizada para el manejo de errores de los selectores de bloques e
 * instrucciones if-then-else.
 */
errorif : exp      {
                      if ($1 == 0  || $1->get_tipo() != TypeBool::Instance()){
                        $$ = new ErrorBoolExp();
                      } else {
                        $$ = new ErrorBoolExp($1);
                      }
                    }
        | error     {
                      $$ = new ErrorBoolExp();
                    };

llamadafuncion: identificador '(' lvarovalor ')' { Symbol *id; 
                                                   LlamadaFuncion* result;
                                                   if ( (id = driver.tablaSimbolos.lookup($1->identificador,0)) == 0){
                                                        std::string msg ("Undefined function '");
                                                        msg += $1->identificador;
                                                        msg += "'";
                                                        driver.error(yylloc,msg);
                                                        error_state = 1;
                                                        $$ = new LlamadaFuncion();
                                                    }else {
                                                        TypeS* tipo = obtener_tipo_simbolo(id);
                                                        if (tipo != 0 && tipo->is_func()){
                                                            TypeFunction * func = (TypeFunction*) tipo;
                                                            result = new LlamadaFuncion($1,$3);
                                                            TypeS* rango = tipo->get_tipo(); 
                                                            std::list<TypeS*>::iterator parametros = func->parametros.begin();
                                                            int expected = func->parametros.size();
                                                            int given = $3->lvarovalor.size();
                                                            std::list<Exp*>::iterator lvarovalor = $3->lvarovalor.begin();
                                                            Exp* tmp;
                                                            while (parametros != func->parametros.end()
                                                                   && lvarovalor != $3->lvarovalor.end()
                                                                  ){
                                                                  tmp = *lvarovalor;
                                                                  if (tmp->get_tipo() != *parametros) {
                                                                    std::string msg = mensaje_error_tipos(tmp->get_tipo()->get_name(),(*parametros)->get_name());
                                                                    driver.error(yylloc,msg);
                                                                    result->tipo = TypeError::Instance();
                                                                    break;
                                                                  }
                                                                  ++parametros;
                                                                  ++lvarovalor;
                                                            }
                                                            if (lvarovalor != $3->lvarovalor.end() && parametros != func->parametros.end()){
                                                                std::string msg ("Expected ");
                                                                msg += std::to_string(expected);
                                                                msg += " arguments, ";
                                                                msg += std::to_string(given);
                                                                msg += " provided.";
                                                                driver.error(yylloc,msg);
                                                                result->tipo = TypeError::Instance();
                                                            } else {
                                                                result->tipo = rango;
                                                            }
                                                            $$ = result;
                                                        }else{
                                                            std::string msg;
                                                            if (tipo == 0){
                                                                msg = mensaje_error_tipos("null","function");
                                                            } else {
                                                                msg = mensaje_error_tipos(tipo->get_name(),"function");
                                                            }
                                                            driver.error(yylloc,msg);
                                                            $$ = new LlamadaFuncion();
                                                        }
                                                    }

                                                 }
              | error '(' lvarovalor ')'         {/*Llamado a una funcion con identificador erroneo*/
                                                 };


lvarovalor: /* Vacio */   { 
                            $$ = new LVaroValor(false); 
                          }
           | lvarovalor2   { 
                           };      

lvarovalor2: lvarovalor2 ',' exp    { 
                                      $1->append($3);
                                      if ($3->get_tipo() == TypeError::Instance()){
                                        $1->tipo = $3->get_tipo();
                                      }
                                      $$ = $1;
                                    }
           | exp                    {
                                      LVaroValor *tmp = new LVaroValor(false);
                                      if ( $1->get_tipo() == TypeError::Instance()){
                                        tmp->tipo = $1->get_tipo();
                                      }
                                      tmp->append($1);
                                      $$ = tmp; 
                                    }
           | lvarovalor2 ',' error  { $$ = new LVaroValor(true);
                                    }
           | error                  {
                                      LVaroValor *tmp = new LVaroValor(true);
                                      $$ = tmp;
                                    };

exp: expAritmetica  { $$ = $1; }
   | expBool        { $$ = $1; } 
   | valor          { $$ = $1; }
   | expID          { $$ = $1; } 
   | '(' exp ')'    { $$ = $2; }
   | llamadafuncion {  /*Supondremos que una llamada a una funcion es una expresion*/}
   | '(' error ')'  {};
/**
 * Falta el caso recursivo de expID
 */
expID: identificador   { TypeS* tipo;
                         ExpID* result;
                         Symbol* id;
                         if ((id = variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()))  != 0) {
                            if((tipo = obtener_tipo_simbolo(id)) != 0) {;
                                result = new ExpID($1);
                                result->tipo = tipo;
                                $$ = result;
                            }
                            else {
                               std::string msg ("Type has not been declared or doesn't exists in current context");
                               driver.error(yylloc,msg);
                               result = new ExpID();
                               $$ = result;
                            }
                          } else {
                          $$ = new ExpID();
                          }
                       }
     | identificador lcorchetesExp    { TypeS* tipo;
                                        ExpID* result;
                                        Symbol* id;
                                        if ((id = variable_no_declarada($1->identificador,&driver, yylloc, tabla_actual.front())) != 0) {
                                            tipo = obtener_tipo_simbolo(id);
                                            if (tipo != 0){
                                                result = new ExpID($1, $2);

                                                if ($2->get_tipo() == TypeInt::Instance() &&
                                                    tipo->is_array()) {
                                                    result->tipo = tipo->get_tipo();
                                                }

                                                //Caso en el que el identificador NO es un arreglo
                                            
                                                else if (!tipo->is_array()){
                                                    std::string msg = mensaje_error_tipos("array",tipo->get_name());
                                                    driver.error(yylloc, msg);
                                                    result->tipo = TypeError::Instance();
                                                }

                                            //Caso en el que la estructura del arreglo no es de tipo integer

                                                else {
                                                    result->tipo = TypeError::Instance();
                                                }
                                                $$ = result;
                                            }
                                        } else{
                                            $$ = new ExpID();
                                        }
                                      }
     | identificador lAccesoAtributos { 
                                        Symbol * id;
                                        Identificador *prueba = $1;
                                        if ((id = variable_no_declarada(prueba->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                        //Caso en el que la variable es un record o union.
                                            if (!es_estructura_error(id->sym_catg, $1->identificador,&driver,yylloc)){
                                                std::list<Identificador*> tmp = $2->get_list();
                                                TypeS* tipo = verificar_acceso_atributos(id, tmp, &driver,yylloc);
                                                ExpID* result = new ExpID($1,$2);
                                                result->tipo = tipo;
                                                $$ = result;
                                            }
                                            else {
                                                $$ = new ExpID();
                                            }
                                        } else {
                                            $$ = new ExpID();
                                        }
                                      };

/*Faltan pruebas*/
expBool: exp AND exp         { ExpBin* tmp = new ExpBin($1,$3,std::string("AND"));
                               if ($1->get_tipo() == TypeBool::Instance() &&
                                   $3->get_tipo() == TypeBool::Instance())
                               { tmp->tipo = $1->get_tipo();
                               } 
                               else if ($1->get_tipo() != TypeBool::Instance()) {
                                 std::string msg = mensaje_error_tipos("boolean",$1->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               else {
                                 std::string msg = mensaje_error_tipos("boolean",$3->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               $$ = tmp;
                             }
       | exp OR exp          { ExpBin* tmp = new ExpBin($1,$3,std::string("OR"));
                               if ($1->get_tipo() == TypeBool::Instance() &&
                                   $3->get_tipo() == TypeBool::Instance())
                               { tmp->tipo = $1->get_tipo();
                               } 
                               else if ($1->get_tipo() != TypeBool::Instance()) {
                                 std::string msg = mensaje_error_tipos("boolean",$1->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               else {
                                 std::string msg = mensaje_error_tipos("boolean",$3->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               $$ = tmp;
                             }
       | exp COMPARISON exp  { ExpBin* tmp;
                               if ($1->get_tipo() == $3->get_tipo() &&
                                   ($1->get_tipo() == TypeInt::Instance() ||
                                    $1->get_tipo() == TypeReal::Instance())) {
                                 int cmpv = $2;
                                 switch(cmpv){
                                      case 1:
                                          tmp = new ExpBin($1,$3,std::string(">"));
                                          break;
                                      case 2:
                                          tmp = new ExpBin($1,$3,std::string("<"));
                                          break;
                                      case 3:
                                          tmp = new ExpBin($1,$3,std::string("<="));
                                          break;
                                      case 4:
                                          tmp = new ExpBin($1,$3,std::string(">="));
                                          break;
                                      case 5:
                                          tmp = new ExpBin($1,$3,std::string("="));
                                          break;
                                      case 6:
                                          tmp = new ExpBin($1,$3,std::string("!="));
                                          break;
                                 }
                                 tmp->tipo = TypeBool::Instance();
                               } 
                               else if ($1->get_tipo() != $3->get_tipo() &&
                                        ($1->get_tipo() == TypeInt::Instance() &&
                                         $3->get_tipo() == TypeReal::Instance()) ||
                                        ($1->get_tipo() == TypeReal::Instance() &&
                                         $3->get_tipo() == TypeInt::Instance())) {
                                 std::string expected = $1->get_tipo()->get_name()+"' or '"+$3->get_tipo()->get_name();
                                 std::string msg = mensaje_diff_operandos(std::string("<=>"),$1->get_tipo()->get_name(),$3->get_tipo()->get_name(),expected);
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               else if ( $1->get_tipo() == $3->get_tipo() && 
                                         $1->get_tipo() == TypeBool::Instance() &&
                                         $2 == 5
                                       ){
                                        tmp = new ExpBin($1,$3,std::string("="));
                                        tmp->tipo = TypeBool::Instance();
                               }else {
                                tmp = new ExpBin();
                                 if ($1->get_tipo() != TypeInt::Instance() &&
                                     $1->get_tipo() != TypeReal::Instance()) {
                                     std::cout << "";
                                     std::string msg = mensaje_error_tipos("integer' or 'real",$1->get_tipo()->get_name());
                                     driver.error(yylloc,msg);
                                 }
                                 else {
                                   std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                   driver.error(yylloc,msg);
                                 }
                                 tmp->tipo = TypeError::Instance();
                               }
                               $$ = tmp;

                             }
       | NOT exp             { std::string * op = new std::string("NOT");
                               ExpUn* tmp = new ExpUn($2,op);
                               if ($2->get_tipo() == TypeBool::Instance())
                               { tmp->tipo = $2->get_tipo();
                               }
                               else {
                                 std::string msg = mensaje_error_tipos("boolean",$2->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               $$ = tmp;
                             };

expAritmetica: '-' exp %prec UMINUS  { std::string * op = new std::string("-");
                                       ExpUn* tmp = new ExpUn($2,op);
                                       if ($2->get_tipo() == TypeInt::Instance() ||
                                           $2->get_tipo() == TypeReal::Instance())
                                       { tmp->tipo = $2->get_tipo();
                                       }
                                       else {
                                         std::string msg = mensaje_error_tipos("integer' or 'real",$2->get_tipo()->get_name());
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp PLUSPLUS          { 
                                       std::string * op = new std::string("++");
                                       ExpUn* tmp = new ExpUn($1,op);
                                       if ($1->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = $1->get_tipo();
                                       }
                                       else {
                                         std::string msg = mensaje_error_tipos("integer",$1->get_tipo()->get_name());
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp MINUSMINUS        { std::string * op = new std::string("--");
                                       ExpUn* tmp = new ExpUn($1,op);
                                       if ($1->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = $1->get_tipo();
                                       }
                                       else {
                                         std::string msg = mensaje_error_tipos("integer",$1->get_tipo()->get_name());
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp UFO exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("<=>"));
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           ($1->get_tipo() == TypeInt::Instance() ||
                                            $1->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = TypeInt::Instance();
                                        // El tipo de esta expresion es integer, recordar que UFO devuelve -1,0,1.
                                       } 
                                       else if ($1->get_tipo() != $3->get_tipo() &&
                                                ($1->get_tipo() == TypeInt::Instance() &&
                                                 $3->get_tipo() == TypeReal::Instance()) ||
                                                ($1->get_tipo() == TypeReal::Instance() &&
                                                 $3->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = $1->get_tipo()->get_name()+"' or '"+$3->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("<=>"),$1->get_tipo()->get_name(),
                                                                                    $3->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance() &&
                                             $1->get_tipo() != TypeReal::Instance()) {
                                           std::string msg = mensaje_error_tipos("integer' or 'real",$1->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                         }
                                         else {
                                           std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp '+' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("+"));
                                       if ($1->get_tipo() == $3->get_tipo() && 
                                           ($1->get_tipo() == TypeInt::Instance() ||
                                            $1->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = $1->get_tipo();
                                       } 
                                       else if ($1->get_tipo() != $3->get_tipo() &&
                                                ($1->get_tipo() == TypeInt::Instance() &&
                                                 $3->get_tipo() == TypeReal::Instance()) ||
                                                ($1->get_tipo() == TypeReal::Instance() &&
                                                 $3->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = $1->get_tipo()->get_name()+"' or '"+$3->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("+"),$1->get_tipo()->get_name(),
                                                                                    $3->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance() &&
                                             $1->get_tipo() != TypeReal::Instance()) {
                                             Exp* hola = $1;
                                             std::cout << "";
                                             std::string msg = mensaje_error_tipos("integer' or 'real",$1->get_tipo()->get_name());
                                             driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp '-' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("-"));
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           ($1->get_tipo() == TypeInt::Instance() ||
                                            $1->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = $1->get_tipo();
                                       } 
                                       else if ($1->get_tipo() != $3->get_tipo() &&
                                                ($1->get_tipo() == TypeInt::Instance() &&
                                                 $3->get_tipo() == TypeReal::Instance()) ||
                                                ($1->get_tipo() == TypeReal::Instance() &&
                                                 $3->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = $1->get_tipo()->get_name()+"' or '"+$3->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("-"),$1->get_tipo()->get_name(),
                                                                                $3->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance() &&
                                             $1->get_tipo() != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp '*' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("*"));
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           ($1->get_tipo() == TypeInt::Instance() ||
                                            $1->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = $1->get_tipo();
                                       } 
                                       else if ($1->get_tipo() != $3->get_tipo() &&
                                                ($1->get_tipo() == TypeInt::Instance() &&
                                                 $3->get_tipo() == TypeReal::Instance()) ||
                                                ($1->get_tipo() == TypeReal::Instance() &&
                                                 $3->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = $1->get_tipo()->get_name()+"' or '"+$3->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("*"),$1->get_tipo()->get_name(),
                                                                                    $3->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance() &&
                                             $1->get_tipo() != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp '/' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("/"));
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           ($1->get_tipo() == TypeInt::Instance() ||
                                            $1->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = $1->get_tipo();
                                       } 
                                       else if ($1->get_tipo() != $3->get_tipo() &&
                                                ($1->get_tipo() == TypeInt::Instance() &&
                                                 $3->get_tipo() == TypeReal::Instance()) ||
                                                ($1->get_tipo() == TypeReal::Instance() &&
                                                 $3->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = $1->get_tipo()->get_name()+"' or '"+$3->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("/"),
                                                                    $1->get_tipo()->get_name(),$3->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance() &&
                                             $1->get_tipo() != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp DIV exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("DIV"));
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           $1->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = $1->get_tipo();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer",$1->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer",$3->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp MOD exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("MOD"));
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           $1->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = $1->get_tipo();
                                       }
                                       else {
                                         if ($1->get_tipo() != TypeInt::Instance()) {
                                             std::string msg = mensaje_error_tipos("integer",$1->get_tipo()->get_name());
                                             driver.error(yylloc,msg);
                                         }
                                         else {
                                             std::string msg = mensaje_error_tipos("integer",$3->get_tipo()->get_name());
                                             driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     }
             | exp POW exp           { //El exponente sera integer, la base integer o real.
                                       ExpBin* tmp = new ExpBin($1,$3,std::string("**"));
                                       if ($3->get_tipo() == TypeInt::Instance()) {
                                           if($1->get_tipo() == TypeInt::Instance() ||
                                              $1->get_tipo() == TypeReal::Instance()) {
                                              tmp->tipo = $1->get_tipo();
                                           }
                                           else {
                                               std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                               driver.error(yylloc,msg);
                                               tmp->tipo = TypeError::Instance();
                                           }
                                       }
                                       else {
                                           std::string msg = mensaje_error_tipos("integer",$3->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                           tmp->tipo = TypeError::Instance();
                                       }
                                       $$ = tmp;
                                     };

valor: BOOL     { 
                  Valor* v = new Bool($1,TypeBool::Instance());
                  $$ = v;
                }
     | STRING   { 
                  Valor* v = new String($1,TypeString::Instance());
                  $$ = v;
                }
     | CHAR     { 
                  Valor* v = new Char($1,TypeChar::Instance());
                  $$ = v;
                }
     | INTEGER  { 
                  Valor* v  = new Integer($1,TypeInt::Instance());
                  $$ = v;
                }
     | REAL     { 
                  Valor* v = new Real($1,TypeReal::Instance());
                  $$ = v;
                }
     | arreglo  {
                  $$ = $1;
                }

/*Funciona*/

/* PRUEBA CON LA NUEVA FORMA DE USAR TIPOS*/
tipo: TYPE_REAL     { 
                      $$ = TypeReal::Instance();
                    }
     | TYPE_INTEGER { 
                      $$ = TypeInt::Instance();
                    }
     | TYPE_BOOLEAN { 
                      $$ = TypeBool::Instance();
                    }
     | TYPE_CHAR    { 
                      $$ = TypeChar::Instance();
                    }
     | TYPE_STRING  { 
                      $$ = TypeString::Instance();
                    };


/*NO Funciona*/
arreglo: '[' larreglo ']' {
                            Arreglo* tmp;
                            LArreglo *lr = $2;
                            tmp = new Arreglo(lr);
                            TypeS* tipo = $2->get_tipo();
                            tmp->tipo = tipo;
                            $$ = tmp;
                          };

/*Funciona. Faltan ejemplos mas interesantes.*/

larreglo: larreglo ',' exp      { 
                                  if ($1->get_tipo() != $3->get_tipo()
                                     || $1->get_tipo() == TypeError::Instance()
                                     || $3->get_tipo() == TypeError::Instance()){
                                        std::string msg;
                                        Exp* e = $3;
                                        LArreglo* a = $1;
                                        if ($1->get_tipo() != 0 && $3->get_tipo() != 0)
                                            msg = mensaje_error_tipos($1->get_tipo()->get_name(),$3->get_tipo()->get_name());
                                        else
                                            msg = mensaje_error_tipos("null","null");
                                        driver.error(yylloc,msg);
                                        $1->tipo = TypeError::Instance();
                                  }else{
                                    $1->append($3);
                                  }
                                  $$ = $1;
                                }
        | exp                   { 
                                  LArreglo *tmp = new LArreglo();
                                  tmp->append($1);
                                  tmp->tipo = $1->get_tipo();
                                  $$ = tmp;
                                }
        /*Errores*/
        | larreglo ',' error    { 
                                 $1->tipo = TypeError::Instance();
                                 $$ = $1; 
                                }
        | error                 { LArreglo *tmp = new LArreglo(); 
                                  tmp->tipo = TypeError::Instance();
                                };


lAccesoAtributos: '.' identificador { 
                                      $$ = new LAccesoAtributos($2);
                                    }
                | lAccesoAtributos '.' identificador {
                                                        $1->append($3);
                                                        $$ = $1;
                                                     }
                | lAccesoAtributos '.' identificador lcorchetesExp {
                                                                    $1->append($3);
                                                                    $$ = $1;
                                                                   }
                | '.' identificador lcorchetesExp                  {
                                                                     $$ = new LAccesoAtributos($2);
                                                                   }

identificador: ID { std::string str =  std::string($1);
                    Identificador* id = new Identificador(str);
                    id->line = yylloc.begin.line;
                    id->column = yylloc.begin.column;
                    $$ = id;
                  };


%%

void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  if(!error_state)
    error_state = 1;

  driver.error (l, m);
}
