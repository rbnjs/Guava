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
                                            if (!error_state && driver.print_table) {
                                                //std::cout << "Funciones: " << '\n';
                                                //driver.tablaSimbolos.show(0,identacion+ "  ");
                                                std::cout << "Variables globales: \n";
                                                driver.tablaSimbolos.show(1,identacion+ "  ");
                                            }


                                            if (!error_state){
                                                std::list<GuavaQuads*>* quads = $3->generar_quads();
                                                if (driver.print_quads){
                                                    imprimir_quads(quads); 
                                                }
                                                GrafoFlujo* g = new GrafoFlujo(quads,driver.guava_gen,&driver.tablaSimbolos);
                                                if (driver.print_graph){
                                                    g->imprimir();
                                                }
                                                //g->generar_mips();
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
          | lvariables identificador ARRAY lvararreglo ';' { 
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
          | identificador RECORD lvar ';'               {
                                                          TypeS* tmp = insertar_simboloEstructura($3,$1->identificador,std::string("recordType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,$3); 
                                                          $$ = tmpLV;
                                                        }
          | lvariables identificador RECORD lvar ';'    { 
                                                          TypeS* tmp = insertar_simboloEstructura($4,$2->identificador,std::string("recordType"),&driver,yylloc); 
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

union: UNION identificador '{' { //Se agrega la estructura a la tabla como un tipo nuevo 
                                 verificar_existencia_tipo($2, &driver,yylloc,true);
                               }
                               lvariables '}' { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                std::string identificador = $2->identificador;
                                                if (!error_state && driver.print_table) {
                                                    identacion.erase(0,2);
                                                    std::cout << identacion << "Union " << identificador << " {\n";
                                                    tabla->show(tabla->currentScope(),identacion+ "  "); 
                                                    std::cout << identacion <<"}\n";
                                                }
                                                offset_actual.pop_front();
                                                tabla_actual.pop_front();
                                             }

record: RECORD identificador '{'{ //Se agrega la estructura a la tabla como un tipo nuevo
                                  verificar_existencia_tipo($2,&driver,yylloc, false);
                                } 
                               lvariables '}' { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                if (!error_state && driver.print_table) {
                                                std::cout << identacion << "Record " << $2->identificador << " {\n";
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
                                tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                $$ = tmp;
                              }
    | lvar ',' error          { $$ = $1; };

lvararreglo: identificador lcorchetes                  { LVarArreglo* tmp = new LVarArreglo(*$1,*$2);
                                                         tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                         $$ = tmp;
                                                       }
            | lvararreglo ',' identificador lcorchetes { $1->append(*$3,*$4);
                                                         $$ = $1;
                                                       }
            /*Errores*/
            | error lcorchetes                         { LVarArreglo* tmp = new LVarArreglo();
                                                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                        $$ = tmp;
                                                       }
            | lvararreglo ',' error lcorchetes         {
                                                        LVarArreglo* tmp = new LVarArreglo();
                                                        $$ = tmp;
                                                       };



lcorchetes: '[' INTEGER ']'            { 
                                        LCorchetes *tmp =  new LCorchetes(false);
                                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                           //tmp->addr = newtemp(&driver,yylloc,TypeInt::Instance());
                                           tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                           if( $2 != 0 && $2->get_tipo() == TypeInt::Instance()) {
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
                                           if ($3 != 0 && $3->get_tipo() != TypeInt::Instance()){
                                               std::string msg = mensaje_error_tipos("integer",$3->get_tipo()->get_name());
                                               driver.error(yylloc,msg);
                                               $1->tipo = TypeError::Instance();
                                           }
                                           $1->append($3);
                                           $$ = $1;
                                         }
             | '[' error ']'             {
                                            LCorchetesExp* tmp = new LCorchetesExp();
                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                             main_->lista = $1;
                                             $$ =main_;
                                           };

lfunciones1: funcion                       { $$ = new LFunciones($1,0);
                                           }
           | lfunciones1 funcion           { 
                                             LFunciones* func = new LFunciones($2,0);
                                             func->lista = $1;
                                             $$ = func;
                                           };

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   int line = yylloc.begin.line;
                                                   int column = yylloc.begin.column;
                                                   driver.tablaSimbolos.insert(std::string("main"),std::string("function"),
                                                                                current_scope,tipo,line,column, 0);
                                                   identacion += "  ";
                                                   offset_actual.push_front(0);
                                                 } 
           bloquedeclare listainstrucciones  '}' { LParam* lp = new LParam();
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   Funcion* tmp = new  Funcion(tipo, new Identificador(std::string("main")),lp,$8,$9); 
                                                   tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                   std::list<Instruccion*> continue_break = $9->obtener_continue_break();
                                                   if (!continue_break.empty()){
                                                        continue_break_libres(continue_break,&driver); 
                                                        tmp = new Funcion();
                                                   }

                                                   $$ = tmp;
                                                   if (!error_state && driver.print_table) {
                                                       std::cout <<  "main {\n"; 
                                                       std::cout << "Parametros y variables:\n";
                                                       driver.tablaSimbolos.show(current_scope,identacion);
                                                       driver.tablaSimbolos.exitScope(); 
                                                       std::cout << "}\n";
                                                       identacion.erase(0,2);
                                                   }
                                                   if (driver.print_tree){
                                                        $9->show("");
                                                   }
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
                                                                               Funcion* tmp;
                                                                               if (lretorno.size() == 0) {
                                                                                    funcion_sin_return($3,&driver,yylloc); 
                                                                               } else{
                                                                                    if ( verificar_return($3,$2,lretorno,&driver) ){
                                                                                        tmp = new Funcion(tipo,$3,$6,$10,$11);
                                                                                    } else {
                                                                                        tmp = new Funcion();
                                                                                    }
                                                                               }
                                                                               std::list<Instruccion*> continue_break = $11->obtener_continue_break();
                                                                               if (!continue_break.empty()){
                                                                                    continue_break_libres(continue_break,&driver); 
                                                                                    tmp = new Funcion();
                                                                               }
                                                                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                               $$ = tmp;
                                                                               if (!error_state && driver.print_table) {
                                                                                    std::cout << $3->identificador << "{\n";
                                                                                    std::cout << "Parametros y variables:\n";
                                                                                    driver.tablaSimbolos.show(current_scope,identacion);
                                                                                    std::cout << "}\n";
                                                                                    driver.tablaSimbolos.exitScope();
                                                                                                identacion.erase(0,2);
                                                                               }
                                                                               if (driver.print_tree){
                                                                                    $10->show("");
                                                                               }
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
                                                                                   Funcion* tmp = new Funcion(tipo,$3,$6,$10,$11);
                                                                                   tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                                   std::list<Instruccion*> continue_break = $11->obtener_continue_break();
                                                                                   if (!continue_break.empty()){
                                                                                        continue_break_libres(continue_break,&driver); 
                                                                                        tmp = new Funcion();
                                                                                   }
                                                                                   $$ = tmp;
                                                                                   if (!error_state && driver.print_table) {
                                                                                        std::cout << $3->identificador << "{\n";
                                                                                        std::cout << "Parametros y variables:\n";
                                                                                        driver.tablaSimbolos.show(current_scope,identacion);
                                                                                        std::cout << "}\n";
                                                                                        driver.tablaSimbolos.exitScope();
                                                                                        identacion.erase(0,2);
                                                                                    }
                                                                                    if (driver.print_tree){
                                                                                        $10->show("");
                                                                                    }
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
lparam: /* Vacio */          { LParam* tmp = new LParam(); 
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               $$ = tmp;
                             } 
      | lparam2              { $$ = $1; 
                             } 

lparam2: tipo identificador               { LParam* tmp = new LParam(); 
                                            tmp->append($1,$2);
                                            tmp->appendTipo($1);
                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            $$ = tmp;
                                            insertar_simboloSimple($2,$1,std::string("param"),&driver,yylloc);
                                          }       
       | tipo REFERENCE identificador     { LParam* tmp = new LParam(); 
                                            tmp->append($1,$3);
                                            tmp->appendTipo($1);
                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                                          //$2->next = new GuavaLabel();
                                                          //$1->set_next($2);
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
                                                          //$2->next = new GuavaLabel();
                                                          //$1->set_next($2);
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
           | MINUSMINUS expID  {
                                         Symbol *id;
                                         PlusMinus *result;
                                         ExpID* exp_id = (ExpID*) $2;
                                         if ( (id = variable_no_declarada(exp_id->identificador->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance() ||
                                                 (tipo->is_array() && tipo->get_tipo() == TypeInt::Instance())){
                                                 result = new PlusMinus(exp_id,0);
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
                                             result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | expID MINUSMINUS  { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         ExpID* exp_id = (ExpID*) $1;
                                         if ( (id = variable_no_declarada(exp_id->identificador->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance() ||
                                                 (tipo->is_array() && tipo->get_tipo() == TypeInt::Instance())){
                                                 result = new PlusMinus(exp_id,1);
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
                                             result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | PLUSPLUS expID    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         ExpID* exp_id = (ExpID*) $2;
                                         if ( (id = variable_no_declarada(exp_id->identificador->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance() ||
                                                 (tipo->is_array() && tipo->get_tipo() == TypeInt::Instance())){
                                                 result = new PlusMinus(exp_id,2);
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
                                             result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | expID PLUSPLUS    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         ExpID* exp_id = (ExpID*) $1;
                                         if ( (id = variable_no_declarada(exp_id->identificador->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance() ||
                                                 (tipo->is_array() && tipo->get_tipo() == TypeInt::Instance())){
                                                 result = new PlusMinus(exp_id,3);
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
                                             result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                             $$ = result;
                                         } 
                                         else {
                                             $$ = new PlusMinus();
                                         }
                                       }
           | entradasalida  { 
                            }
           | CONTINUE       {
                              ContinueBreak* tmp = new ContinueBreak(0);
                              tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                              $$ = tmp;
                            }
           | BREAK          {
                              ContinueBreak* tmp = new ContinueBreak(1);
                              tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                              $$ = tmp;
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
                                 Asignacion* tmp;
                                 ExpID* a = (ExpID*) $1;
                                 Exp* b = $3;
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
                                    tmp = new Asignacion();
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
                                 } else if ($1->get_tipo() == $3->get_tipo()) {
                                    tmp = new Asignacion($1,$3);
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
                                 //Caso variables de tipo array.
                                 } else if ($1->get_tipo()->is_array() && $3->get_tipo()->is_array()) {
                                    TypeArray* arr1 = (TypeArray*) $1->get_tipo();
                                    TypeArray* arr2 = (TypeArray*) $3->get_tipo();
                                    if (arr1->compare(arr2)) {
                                        tmp = new Asignacion($1,$3);
                                    }
                                    else {
                                        std::string msg = mensaje_error_tipos(arr1->get_name(),arr2->get_name());
                                        driver.error(yylloc, msg);
                                        tmp = new Asignacion();
                                    }
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
                                 //Caso expresion arreglo de valores.
                                 } else if($1->get_tipo()->is_array() && $3->is_array()) {
                                    TypeArray* arr1 = (TypeArray*) $1->get_tipo();
                                    Arreglo* arr2 = (Arreglo*) $3;
                                    if (arr1->compare(arr2->get_tipoEstructura())){
                                        tmp = new Asignacion($1,$3);
                                    } else {
                                        std::string msg = mensaje_error_tipos(arr1->get_name(),arr2->get_tipoEstructura()->get_name());
                                        driver.error(yylloc, msg);
                                        tmp = new Asignacion();
                                    }
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
                                 } else {
                                    std::string msg = mensaje_error_tipos($1->get_tipo()->get_name(),$3->get_tipo()->get_name());
                                    driver.error(yylloc,msg);
                                    tmp = new Asignacion();
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
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
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
                                  }
             | PRINT '(' exp ')'  { 
                                    EntradaSalida* tmp = new EntradaSalida(1,$3);  
                                    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos("type","error");
                                        driver.error(yylloc,msg);
                                    }
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    $$ = tmp;
                                  };

retorno: RETURN       { 
                            NewTemp t (&secuencia_temporales, TypeVoid::Instance(), yylloc.begin.line,
                                              yylloc.begin.column,&driver.tablaSimbolos);
		            Retorno* tmp = new Retorno(0,yylloc.begin.line,yylloc.begin.column); 
                            tmp->tmp_return = t.newtemp();
                            $$ = tmp;
                      }
       | RETURN exp   {
			    Retorno* tmp =  new Retorno($2,yylloc.begin.line, yylloc.begin.column); 
                            NewTemp t (&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                              yylloc.begin.column,&driver.tablaSimbolos);
                            tmp->tmp_return = t.newtemp();
			    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                std::string msg = mensaje_error_tipos("type","error");
                                driver.error(yylloc,msg);
			    }
                            $$ = tmp;
                          }

loopfor: FOR '(' expID ';' expBool ';' errorloopfor ')' '{' { 
                                                                ExpID* exp_id = (ExpID*) $3;
                                                                Identificador* identificador = exp_id->identificador;
                                                                Symbol* id = variable_no_declarada(identificador->identificador
                                                                ,&driver,yylloc, tabla_actual.front()); 
                                                                exp_id->tipo = obtener_tipo_simbolo(id);
                                                                driver.tablaSimbolos.enterScope();   
                                                                identacion += "  "; 
                                                            }
                                
                                bloquedeclare listainstrucciones '}' {  ErrorLoopFor* asign_exp = $7;
                                                                        Exp* exp;
                                                                        LoopFor* tmp;
                                                                        ExpID* exp_id = (ExpID*) $3;
                                                                        Identificador* identificador = exp_id->identificador;
                                                                        if (asign_exp->is_error()
                                                                                    || exp_id->get_tipo() == TypeError::Instance()
                                                                                    || $5->get_tipo() == TypeError::Instance()
                                                                               ){
                                                                               //Caso error.
                                                                                tmp = new LoopFor();
                                                                                std::string msg = mensaje_error_tipos("error","void");
                                                                                driver.error(yylloc,msg);
                                                                            } else{
                                                                                if ( (exp = asign_exp->exp) != 0){
                                                                                    //Caso en el que es una expresion.
                                                                                    //Identificador debe ser del mismo tipo
                                                                                    //de la expresion
                                                                                    if (exp_id->get_tipo() == exp->get_tipo()){
                                                                                        tmp = new 
                                                                                            LoopForExp(exp_id, $5,asign_exp->exp,$11,$12);
                                                                                        tmp->tipo = TypeVoid::Instance();
                                                                                    }else{
                                                                                        tmp = new LoopFor();
                                                                                        std::string msg;
                                                                                        if (exp->get_tipo() != 0){
                                                                                            msg = 
                                                                                            mensaje_error_tipos(exp->get_tipo()->get_name(),"integer");
                                                                                        } else {
                                                                                            msg = 
                                                                                            mensaje_error_tipos("unknown","integer");
                                                                                        }
                                                                                        driver.error(yylloc,msg);
                                                                                    }
                                                                                } else {
                                                                                    //Caso en el que se usa una asignacion.
                                                                                    //En la asignacion debe usarse el mismo identificador.
                                                                                    //Este caso es chevere de revisar pero esta bastante complicado. PENDIENTE
                                                                                    ExpID* exp_id_tmp = (ExpID*) asign_exp->asign->id;
                                                                                    Identificador* identificador_tmp = exp_id_tmp->identificador;
                                                                                    if (identificador_tmp->identificador.compare(identificador->identificador) ){
                                                                                        tmp = new 
                                                                                            LoopForAsignacion(exp_id, $5,asign_exp->asign,$11,$12);
                                                                                        tmp->tipo = TypeVoid::Instance();
                                                                                    } else {
                                                                                        driver.error(yylloc,
                                                                                            "You are not using the same identifier in the assignment 'slot'");
                                                                                        tmp = new LoopFor();
                                                                                    }
                                                                                }
                                                                            }
                                                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                            $$ = tmp;
                                                                            if (!error_state &&  driver.print_table ) {
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
       | FOR '(' expID ';' error  ';' errorloopfor ')' '{' { 
                                                             ExpID* exp_id = (ExpID*) $3;
                                                             Identificador* id = exp_id->identificador;
                                                             variable_no_declarada(id->identificador,&driver,yylloc, tabla_actual.front());
                                                           }
                                bloquedeclare listainstrucciones '}' { 
                                                                           $$ = new LoopFor();
                                                                         };

/**
 * Regla utilizada en el manejo de errores del encabezado de una iteracion
 * acotada
 */
errorloopfor : asignacion {
                            if ($1->exp != 0 && $1->exp->exp_id()){
                                //La expresion debe ser 
                                //de tipo exp_id
                                $$ = new ErrorLoopFor($1);
                            } else {
                                $$ = new ErrorLoopFor();
                            }
                          }
             | expAritmetica        {
                                      //Solo se permite que se usen expAritmeticas de tipo integer.
                                      if ($1->get_tipo() == TypeInt::Instance()){
                                        $$ = new ErrorLoopFor($1);
                                      } else {
                                        $$ = new ErrorLoopFor();
                                        TypeS* tipo = $1->get_tipo();
                                        std::string msg;
                                        if (tipo != 0) {
                                            msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                        }else{
                                            msg = mensaje_error_tipos("unknown","integer");
                                        }
                                        driver.error(yylloc,msg);
                                      }
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
                                                                 result = new WhileDo(exp_bool->exp,$8,$9);
                                                             }
                                                             result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                             $$ = result;
                                                             if (!error_state && driver.print_table) {
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
                                                                                       result = new DoWhile(exp_bool->exp,$4,$5);
                                                                                   }
                                                                                   result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                                   $$ = result;
                                                                                   if (!error_state && driver.print_table) {
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
errorloopwhile: exp    {    Exp* tmp = $1;
                            ErrorBoolExp* tmp1;
                            if ( $1 == 0 || $1->get_tipo() != TypeBool::Instance()){
                                tmp1 = new ErrorBoolExp();
                                tmp1->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                $$ = tmp1;
                             } else {
                                tmp1 = new ErrorBoolExp($1);
                                tmp1->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                $$ = tmp1;
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
                                                               BoolLabel* labels;
                                                               SelectorIf * result;
                                                               if (err_exp->get_error()
                                                                   || err_exp->get_tipo() == TypeError::Instance()
                                                                   || $9->get_tipo() == TypeError::Instance()){
                                                                   result = new SelectorIf(); 
                                                                   std::string msg = mensaje_error_tipos("error","void");
                                                                   driver.error(yylloc,msg);
                                                               } 
                                                               else {
                                                                   result = new SelectorIfComplejo(err_exp->exp,$8,$9,$11);
                                                               }
                                                               result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                               $$ = result;
                                                               if (!error_state && driver.print_table) {
                                                                    std::cout << identacion << "if {\n"; 
                                                                    driver.tablaSimbolos.show(driver.tablaSimbolos.currentScope(),identacion+"  ");
                                                                    std::cout << identacion << "}\n ";
                                                                    driver.tablaSimbolos.exitScope();
                                                                    identacion.erase(0,2);
                                                               }
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
                                                                   result = new SelectorIfSimple(err_exp->exp,$6,0);
                                                               }
                                                               result->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                                                           result = new SelectorIfSimple(err_exp->exp,$6,$8);
                                                                       }
                                                                       result->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                                                          result = new Else($5,$6,$1);
                                                                      }
                                                                      result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                      $$ = result;

                                                                      if (!error_state && driver.print_table) {
                                                                            std::cout << identacion << "if {\n"; 
                                                                            driver.tablaSimbolos.show(driver.tablaSimbolos.currentScope(),identacion+"  ");
                                                                            std::cout << identacion << "}\n ";
                                                                            driver.tablaSimbolos.exitScope();
                                                                            identacion.erase(0,2);
                                                                      }
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
                                                                          result = new Else($4,$5);
                                                                      }
                                                                      result->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                                                       result = new ElseIf($4->exp,$9,$10);
                                                                   }
                                                                   result->set_line_column(yylloc.begin.line,yylloc.begin.column);
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
                                                                       result = new ElseIf($5->exp,$10,$11,$1);
                                                                   }
                                                                   result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                   $$ = result;
                                                                   driver.tablaSimbolos.exitScope();
                                                                 };
/**
 * Regla utilizada para el manejo de errores de los selectores de bloques e
 * instrucciones if-then-else.
 */
errorif : exp      {  ErrorBoolExp* tmp;
                      if ($1 == 0  || $1->get_tipo() != TypeBool::Instance()){
                        tmp = new ErrorBoolExp();
                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                        $$ = tmp;
                      } else {
                        tmp = new ErrorBoolExp($1);
                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                        $$ = tmp;
                      }
                   }
        | error    {
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
                                                   } else {
                                                        TypeS* tipo = obtener_tipo_simbolo(id);
                                                        if (tipo != 0 && tipo->is_func()){
                                                            TypeFunction * func = (TypeFunction*) tipo;
                                                            result = new LlamadaFuncion($1,$3);
                                                            TypeS* rango = tipo->get_tipo(); 
                                                            result->temp = new NewTemp(&secuencia_temporales, rango, yylloc.begin.line,
                                                                          yylloc.begin.column,&driver.tablaSimbolos);
                                                            std::list<TypeS*>::iterator parametros = func->parametros.begin();
                                                            int expected = func->parametros.size();
                                                            int given = $3->lvarovalor.size();
                                                            std::list<Exp*>::iterator lvarovalor = $3->lvarovalor.begin();
                                                            Exp* tmpArg;
                                                            TypeS* tmpPar;
                                                            if (expected != given) {
                                                                std::string msg("Expected ");
                                                                msg += std::to_string(expected);
                                                                msg += " arguments, ";
                                                                msg += std::to_string(given);
                                                                msg += " provided.";
                                                                driver.error(yylloc,msg);
                                                                result->tipo = TypeError::Instance();
                                                                $$ = result;
                                                            }
                                                            else {
                                                                result->tipo = rango;
                                                                while (parametros != func->parametros.end()
                                                                       && lvarovalor != $3->lvarovalor.end())
                                                                {
                                                                    tmpArg = *lvarovalor;
                                                                    tmpPar = *parametros;
                                                                    if (tmpArg->get_tipo() != tmpPar) {
                                                                        std::string msg = mensaje_error_tipos(tmpPar->get_name(),tmpArg->get_tipo()->get_name());
                                                                        driver.error(yylloc,msg);
                                                                        result->tipo = TypeError::Instance();
                                                                        break;
                                                                    }
                                                                    ++parametros;
                                                                    ++lvarovalor;
                                                                }
                                                                result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                
                                                                $$= result;
                                                            }
                                                        } else {
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
                                      if ( $1 != 0 && $1->get_tipo() == TypeError::Instance()){
                                        tmp->tipo = $1->get_tipo();
                                      }
                                      tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                      tmp->append($1);
                                      $$ = tmp; 
                                    }
           | lvarovalor2 ',' error  { $$ = new LVaroValor(true);
                                    }
           | error                  {
                                      LVaroValor *tmp = new LVaroValor(true);
                                      $$ = tmp;
                                    };

exp: expAritmetica  { /**
                       * Esto es de prueba. Para version final el generador de quads
                       * y de codigo intermedio debe ir en nodos padres, si no se
                       * generan listas de quads repetidos.
                       *
                       * SOLUCION ALTERNATIVA:
                       * Cada vez que se imprima codigo intermedio, borrar los quads. MOSCA.
                       *
                       **/
                      /*if (!error_state) {
                        $1->generar_quads();
                        std::cout << $1->gen();
                      }*/
                      $$ = $1; 
                    }
   | expBool        { //PARA PRUEBAS
                      //if (!error_state) {
                        //$1->generar_quads();
                        //std::cout << $1->gen();
                      //}
                      $$ = $1; }
   | valor          { $$ = $1; /*Aqui va:
                                * $$->addr = newtemp(&driver,yylloc,$1->get_tipo());
                                * y luego la generacion de la tripleta para cuando se asigna
                                * un valor constante.
                                *
                                * Funciona con constantes 'puras', es decir, esto:
                                *
                                * GuavaQuads(":=",$1->get_valor(),0,$$->addr);
                                *
                                * "Cuando $1 es un bool, un integer, un real, un string."
                                * Pero, como hacemos cuando $1 es un arreglo constante?
                                * funcionaria $1->get_valor()?
                                */}
   | expID          { $$ = $1; } 
   | '(' exp ')'    { $$ = $2; }
   | llamadafuncion { $$ = $1;
                       /** 
                        * Supondremos que una llamada a una funcion es una expresion.
                        * Para la generacion de codigo intermedio en el addr
                        * guardariamos la direccion de lo que retorne la funcion?
                        * Recordar en Orga aquello de tener un registro que contenga
                        * lo que devuelven las funciones.
                        **/}
   | '(' error ')'  {};

expID: identificador   { TypeS* tipo;
                         ExpID* result;
                         Symbol* id;
                         std::string msg;
                         if ((id = variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()))  != 0) {
                            if ((tipo = obtener_tipo_simbolo(id)) != 0) {
                                result = new ExpIdentificador($1);
                                result->offset = id->offset;
                                result->tipo = tipo;
                                result->temp = new NewTemp(&secuencia_temporales, result->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);                                    
                                result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                /* En caso de ser una estructura o union, se asigna la tabla de simbolos y address
                                 * correspondiente.
                                 */
                                if (tipo->is_structure() || tipo->is_union()) {
                                    TypeStructure* structure = (TypeStructure *) tipo;
                                    result->tabla = structure->get_tabla();
                                    revision_scope_id(id,result,&driver,yylloc,result->tabla);
                                }
                                else {
                                    revision_scope_id(id,result,&driver,yylloc);
                                }
                            }
                            else {
                                std::string msg("Type has not been declared or doesn't exists in current context.");
                                driver.error(yylloc,msg);
                            }
                            $$ = result;
                         } else {
                          result = new ExpID();
                          result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                          $$ = result;
                         }
                       }
     | identificador lcorchetesExp   { TypeS* tipo;
                                       ExpID* result;
                                       std::string msg;
                                       Symbol* id;
                                       if ((id = variable_no_declarada($1->identificador,&driver, yylloc, tabla_actual.front())) != 0) {
                                           if ((tipo = obtener_tipo_simbolo(id)) != 0) {
                                               result = new ExpIDLCorchetes($1,$2);
                                               result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                           }
                                           //Se verifica que la lista de expresiones sea de Integers y el simbolo un arreglo
                                           if ($2->get_tipo() == TypeInt::Instance() &&
                                               tipo->is_array()) {
                                               /**
                                                *
                                                *
                                                * MOSCA, FALTA VERIFICAR CUANDO NO SE INDICA BIEN EL INDICE.
                                                * Ejemplo: La variable es: integer array x[5][5] y se hace la asignacion asi: a := x[2]
                                                * estariamos asignando un arreglo de enteros. Pensando un poco ese tipo de asignaciones
                                                * es un poco pelua al momento de la verificacion de tipos: habria que cambiar en """gran""" medida
                                                * el arbol; mi opinion: No permitamos eso, :).
                                                *
                                                *
                                                **/
                                               result->tipo = tipo->get_tipo();
                                               /*En caso de ser una estructura o union, se asigna la tabla de simbolos
                                                * y address correspondiente.
                                                */
                                               if (result->tipo->is_structure() || result->tipo->is_union()) {
                                                   TypeStructure* structure = (TypeStructure *) tipo->get_tipo();
                                                   result->tabla = structure->get_tabla();
                                                   revision_scope_id(id,result,&driver,yylloc,result->tabla);
                                               }
                                               else {
                                                   revision_scope_id(id,result,&driver,yylloc);
                                               }

                                           }
                                           //Caso en el que el simbolo no es un arreglo
                                           else if (!tipo->is_array()) {
                                               std::string msg = mensaje_error_tipos("array",tipo->get_name());
                                               result->tipo = TypeError::Instance();
                                               driver.error(yylloc,msg);
                                           }
                                           //Caso en el que la lista de expresiones no se de tipo Integers
                                           else {
                                               std::string msg("Access to array index cannot be done.");
                                               result->tipo = TypeError::Instance();
                                               driver.error(yylloc,msg);
                                           }
                                           /* Se asigna el address a la expresion, necesario para los
                                            * calculos de acceso a elementos del arreglo.
                                            */
                                           result->temp = new NewTemp(&secuencia_temporales, result->get_tipo(), yylloc.begin.line,
                                                                          yylloc.begin.column,&driver.tablaSimbolos);
                                        } else {
                                           result = new ExpID();
                                           result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       }
                                       result->offset = id->offset;
                                       $$ = result;
                                     }
     | expID '.' identificador { 
                                Symbol * id;
                                ExpID* result;
                                TypeS* tipo;
                                ExpID* exp_id = (ExpID*) $1; //La expresion es de tipo ExpID
                                std::string msg ("");
                                //Caso en el que la expresion no sea una estructura
                                if (exp_id->get_tabla() == 0){
                                    if (exp_id->identificador != 0) msg = mensaje_estructura_error(exp_id->identificador->identificador);
                                    driver.error(yylloc,msg);
                                    result = new ExpID();
                                    result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                } else if ((id = variable_no_declarada($3->identificador,&driver,yylloc, exp_id->tabla)) != 0){
                                    if ((tipo = obtener_tipo_simbolo(id)) != 0) {
                                        result = new ExpIdentificador(exp_id,$3);
                                        result->offset = id->offset;
                                        result->tipo = tipo;
                                        result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                        /* En caso de ser una estructura o union, se asigna la tabla de simbolos
                                         * y address correspondiente.
                                         */
                                        if (tipo->is_structure() || tipo->is_union()) {
                                            TypeStructure* structure = (TypeStructure *) tipo;
                                            result->tabla = structure->get_tabla();
                                            revision_scope_id(id,result,&driver,yylloc,result->tabla);
                                        }
                                        else {
                                            revision_scope_id(id,result,&driver,yyloc);
                                        }
                                    }
                                    else {
                                        std::string msg("Type has not been declared or doesn't exists in current context.");
                                        driver.error(yylloc,msg);
                                    }
                                } else {
                                    //Error
                                    result = new ExpID();
                                    result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                }
                                result->temp = new NewTemp(&secuencia_temporales, result->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);                                    

                                $$ = result;
                              }
       | expID '.' identificador 
                   lcorchetesExp { 
                                   Symbol * id;
                                   ExpID* result;
                                   TypeS* tipo;
                                   ExpID* exp_id = (ExpID*) $1;
                                   std::string msg;
                                   //Caso en el que la expresion no sea una estructura
                                   if (exp_id->get_tabla() == 0){
                                        if (exp_id->identificador != 0) msg = mensaje_estructura_error(exp_id->identificador->identificador);
                                        driver.error(yylloc,msg);
                                        result = new ExpID();
                                        result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                   } else if ((id = variable_no_declarada($3->identificador,&driver,yylloc, exp_id->get_tabla()))  != 0) {  
                                       if ((tipo = obtener_tipo_simbolo(id)) != 0) {
                                            result = new ExpIDLCorchetes(exp_id,$3,$4);
                                            result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            //Se verifica que el simbolo sea un arreglo
                                            if (tipo->is_array()) {
                                                result->tipo = tipo->get_tipo();
                                                //En caso de ser una estructura o union, se asigna la tabla de simbolos correspondiente
                                                if (result->tipo->is_structure() || result->tipo->is_union()) {
                                                    TypeStructure* structure = (TypeStructure *) tipo->get_tipo();
                                                    result->tabla = structure->get_tabla();
                                                }
                                            }
                                            //Caso en el que el simbolo no es un arreglo
                                            else {
                                                std::string msg = mensaje_error_tipos("array",tipo->get_name());
                                                result->tipo = TypeError::Instance();
                                                driver.error(yylloc,msg);
                                            }
                                            //Se asigna el address a la expresion
                                            if (result->tipo->is_structure()){
                                                revision_scope_id(id,result,&driver,yylloc, result->tabla);
                                            }else{
                                                revision_scope_id(id,result,&driver,yylloc);
                                            }
                                        }
                                        else {
                                            std::string msg("Type has not been declared or doesn't exists in current context.");
                                        }
                                   } else {
                                        // Error     
                                        result = new ExpID();
                                        result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                   }
                                   result->temp = new NewTemp(&secuencia_temporales, result->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);                                    

                                   result->offset = id->offset;
                                   $$ = result;
                                 };

/*Faltan pruebas*/
expBool: exp AND exp         { ExpBin* tmp = new ExpBinBoolLogic($1,$3,std::string("AND"));
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               std::string msg = tmp->revision_binaria($1,$3,tmp,TypeBool::Instance(),0,mensaje_error_tipos,
                                                                       mensaje_diff_operandos);
                               if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                               tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                               $$ = tmp;
                             }
       | exp OR exp          { ExpBin* tmp = new ExpBinBoolLogic($1,$3,std::string("OR"));
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               std::string msg = tmp->revision_binaria($1,$3,tmp,TypeBool::Instance(),0,mensaje_error_tipos,
                                                                       mensaje_diff_operandos);
                               if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                               tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                               $$ = tmp;
                             }
       | exp COMPARISON exp  { ExpBin* tmp;
                               int cmpv = $2;
                               switch(cmpv){
                                    case 1:
                                        tmp = new ExpBinBoolComparison($1,$3,std::string(">"));
                                        break;
                                    case 2:
                                        tmp = new ExpBinBoolComparison($1,$3,std::string("<"));
                                        break;
                                    case 3:
                                        tmp = new ExpBinBoolComparison($1,$3,std::string("<="));
                                        break;
                                    case 4:
                                        tmp = new ExpBinBoolComparison($1,$3,std::string(">="));
                                        break;
                                    case 5:
                                        tmp = new ExpBinBoolComparison($1,$3,std::string("="));
                                        break;
                                    case 6:
                                        tmp = new ExpBinBoolComparison($1,$3,std::string("!="));
                                        break;
                               }
                               std::string msg = tmp->revision_comparison($1,$3,tmp,cmpv,mensaje_error_tipos,mensaje_diff_operandos);
                               if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                               //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                               tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);

                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               $$ = tmp;

                             }
       | NOT exp             { std::string * op = new std::string("not");
                               ExpUn* tmp = new ExpUnBool($2,op);
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               std::string msg = tmp->revision_unaria($2,TypeBool::Instance(),0,tmp,mensaje_error_tipos);
                               if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                               //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                               tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                               $$ = tmp;
                             };

expAritmetica: '-' exp %prec UMINUS  { std::string * op = new std::string("uminus");
                                       ExpUn* tmp = new ExpUn($2,op);
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_unaria($2,TypeInt::Instance(),TypeReal::Instance(),tmp,mensaje_error_tipos);
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp PLUSPLUS          { 
                                       std::string * op = new std::string("pincrease");
                                       ExpUn* tmp = new ExpUn($1,op);
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_unaria($1,TypeInt::Instance(),0,tmp,mensaje_error_tipos);
                                       if(!msg.empty()) driver.error(yylloc,msg);
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp MINUSMINUS        { std::string * op = new std::string("pdecrease");
                                       ExpUn* tmp = new ExpUn($1,op);
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_unaria($1,TypeInt::Instance(),0,tmp,mensaje_error_tipos);
                                       if(!msg.empty()) driver.error(yylloc,msg);
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp UFO exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("<=>"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ($1->get_tipo() == $3->get_tipo() &&
                                           ($1->get_tipo() == TypeInt::Instance() ||
                                            $1->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = TypeInt::Instance();
                                        // El tipo de esta expresion es integer, recordar que UFO devuelve -1,0,1.
                                       } 
                                       else if  ( $1->get_tipo() != $3->get_tipo() &&
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
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp '+' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("+"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_binaria($1,$3,tmp,TypeInt::Instance(),TypeReal::Instance(),mensaje_error_tipos,
                                                                               mensaje_diff_operandos);
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp '-' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("-"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_binaria($1,$3,tmp,TypeInt::Instance(),TypeReal::Instance(),mensaje_error_tipos,
                                                                               mensaje_diff_operandos);                                      
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp '*' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("*"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_binaria($1,$3,tmp,TypeInt::Instance(),TypeReal::Instance(),mensaje_error_tipos,
                                                                               mensaje_diff_operandos);                                      
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;                                      
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp '/' exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("/"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_binaria($1,$3,tmp,TypeReal::Instance(),0,mensaje_error_tipos,
                                                                               mensaje_diff_operandos);                                      
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;                                                 
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp DIV exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("DIV"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_binaria($1,$3,tmp,TypeInt::Instance(),0,mensaje_error_tipos,
                                                                               mensaje_diff_operandos);
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp MOD exp           { ExpBin* tmp = new ExpBin($1,$3,std::string("MOD"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       std::string msg = tmp->revision_binaria($1,$3,tmp,TypeInt::Instance(),0,mensaje_error_tipos,
                                                                               mensaje_diff_operandos);
                                       if (!msg.empty()) driver.error(yylloc,msg), error_state = 1;                                      
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     }
             | exp POW exp           { //El exponente sera integer, la base integer o real.
                                       ExpBin* tmp = new ExpBin($1,$3,std::string("**"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ($3->get_tipo() == TypeInt::Instance()) {
                                           if($1->get_tipo() == TypeInt::Instance() ||
                                              $1->get_tipo() == TypeReal::Instance()) {
                                              tmp->tipo = $1->get_tipo();
                                           }
                                           else {
                                               std::string msg = mensaje_error_tipos("integer' or 'real",$3->get_tipo()->get_name());
                                               driver.error(yylloc,msg);
                                               error_state = 1;
                                               tmp->tipo = TypeError::Instance();
                                           }
                                       }
                                       else {
                                           std::string msg = mensaje_error_tipos("integer",$3->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                           error_state = 1;
                                           tmp->tipo = TypeError::Instance();
                                       }
                                       //tmp->addr = newtemp(&driver,yylloc,tmp->get_tipo());
                                       tmp->temp = new NewTemp(&secuencia_temporales, tmp->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                                       $$ = tmp;
                                     };

valor: BOOL     { 
                  Valor* v = new Bool($1,TypeBool::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  v->temp = new NewTemp(&secuencia_temporales, v->get_tipo(), yylloc.begin.line,
                                            yylloc.begin.column,&driver.tablaSimbolos);
                  $$ = v;
                }
     | STRING   { 
                  Valor* v = new String($1,TypeString::Instance());
                  v->addr = insertar_cadena_caracteres(*v->get_valor_str(),&driver, yylloc);
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  v->temp = new NewTemp(&secuencia_temporales, v->get_tipo(), yylloc.begin.line,
                                            yylloc.begin.column,&driver.tablaSimbolos);
                  $$ = v;
                }
     | CHAR     { 
                  Valor* v = new Char($1,TypeChar::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  v->temp = new NewTemp(&secuencia_temporales, v->get_tipo(), yylloc.begin.line,
                                            yylloc.begin.column,&driver.tablaSimbolos);
                  $$ = v;
                }
     | INTEGER  { 
                  Valor* v  = new ::Integer($1,TypeInt::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  v->temp = new NewTemp(&secuencia_temporales, v->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                  $$ = v;
                }
     | REAL     { 
                  Valor* v = new Real($1,TypeReal::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  v->temp = new NewTemp(&secuencia_temporales, v->get_tipo(), yylloc.begin.line,
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                  $$ = v;
                }
     | arreglo  {
                  /**
                   * Lo que se me ocurre para los arreglos constantes es crear
                   * un identificador unico temporal que los identifique,
                   * guardarlo en la tabla de simbolos y al momento de generar
                   * el codigo intermedio lo hacemos como si fuese una variable:
                   * con el apuntador al Symbol en lugar de con un temporal.
                   **/
                  $$ = $1;
                }


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

/**
 * Inserto cada arreglo en la tabla de simbolos.
 */

/*AQUI ESTA EL PROBLEMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA*/
arreglo: '[' larreglo ']' {
                            Arreglo* tmp;
                            LArreglo *lr = $2;
                            tmp = new Arreglo(lr);
                            tmp->tipo_primitivo = lr->get_tipo();
                            tmp->tipo_estructura = lr->get_tipoEstructura();
                            tmp->tam_tipo_primitivo = tamano_tipo(lr->get_tipo());
                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                            // Esta función me esta dando la dirección en donde se encuentra el arreglo.
                            tmp->direccion = insertar_arreglo_valor(lr, &driver, yylloc); 
                            tmp->temp = new  NewTemp(&secuencia_temporales, lr->get_tipo(), yylloc.begin.line, 
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                            $$ = tmp;
                          };


larreglo: larreglo ',' exp      { 
                                  //Caso: Tipos no nulos
                                  std::string msg;
                                  LArreglo* lar = $1;
                                  Exp* e = $3;
                                  if ($1->get_tipo() != 0 && $3->get_tipo() != 0) {
                                    //Caso Tipos primitivos diferentes
                                    if ($1->get_tipo() != $3->get_tipo()) {
                                        msg = mensaje_error_tipos($1->get_tipo()->get_name(),$3->get_tipo()->get_name());
                                        driver.error(yylloc,msg);
                                        $1->tipo_primitivo = TypeError::Instance();
                                    }
                                    //Caso Tipos estructurales diferentes
                                    else if ($3->get_tipo()->is_array()) {
                                        Arreglo* expArr = (Arreglo *) $3;
                                        if ($1->get_tipoEstructura() != expArr->get_tipoEstructura()) {
                                            msg = mensaje_error_tipos($1->get_tipoEstructura()->get_name(),expArr->get_tipoEstructura()->get_name());
                                            driver.error(yylloc,msg);
                                            $1->tipo_primitivo = TypeError::Instance();
                                        }
                                    }
                                    //Caso sin errores
                                    else{
                                        $1->append($3);
                                    }
                                  }
                                  //Caso: Tipos nulos
                                  else if ($1->get_tipo() == 0 && $3->get_tipo() == 0) {
                                    msg = mensaje_error_tipos("null","null");
                                    driver.error(yylloc,msg);
                                    $1->tipo_primitivo = TypeError::Instance();
                                  }
                                  $$ = $1;
                                }
        | exp                   { 
                                  LArreglo *tmp = new LArreglo();
                                  tmp->tipo_primitivo = $1->get_tipo();
                                  //Caso para arreglos anidados
                                  if($1->get_tipo()->is_array() != 0) {
                                    Arreglo* expArr = (Arreglo *) $1;
                                    tmp->tipo_estructura = expArr->get_tipoEstructura();
                                  }
                                  //Caso para arreglos simples
                                  else {
                                    tmp->tipo_estructura = 0;
                                  }
                                  tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                  tmp->append($1);
                                  $$ = tmp;
                                }
        /*Errores*/
        | larreglo ',' error    { 
                                 $1->tipo_primitivo = TypeError::Instance();
                                 $$ = $1; 
                                }
        | error                 { LArreglo *tmp = new LArreglo(); 
                                  tmp->tipo_primitivo = TypeError::Instance();
                                };

identificador: ID { std::string *str = new std::string($1);
                    Identificador* id = new Identificador(*str);
                    id->line = yylloc.begin.line;
                    id->column = yylloc.begin.column;
                    id->temp = new NewTemp(&secuencia_temporales, TypeVoid::Instance(), yylloc.begin.line, // Voy a dejar el tipo en void mientras tanto.
                                                        yylloc.begin.column,&driver.tablaSimbolos);
                    $$ = id;
                  };


%%

void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  if(!error_state)
    error_state = 1;

  driver.error (l, m);
}
