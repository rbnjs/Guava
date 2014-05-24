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
%{
/* Aqui definimos el tamaño de todos los tipos basicos. */ 
#define SIZE_REFERENCE 8
#define SIZE_INT       4
#define SIZE_CHAR      1
#define SIZE_REAL      8
#define SIZE_BOOL      1
#define WORD           4
%}
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
    TypeS *classTipo;
    //Tipo *classTipo;
    BloqueDeclare *classBloqueDeclare;
    BloquePrincipal *classBloquePrincipal;
    EntradaSalida *classEntradaSalida;
    Identificador *classIdentificador;
    LAccesoAtributos *classLAccesoAtributos;
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
/* Variables globales. */
int current_scope;
int attribute_scope;  
int declare_scope;
int error_state;
std::string identacion ("");
std::list<int> offset_actual;
std::list<GuavaSymTable*> tabla_actual;

/**
 * Avisa si la variable es de categoria estructura
 * e imprime .
 */
bool es_estructura_error(std::string categoria,std::string nombre ,  GuavaDriver* driver, const yy::location& loc){
    if ((categoria.compare("unionVar") != 0) && categoria.compare("recordVar") != 0){
        std::string msg2 ("The ");
        msg2 += categoria;
        msg2 += "  ";
        msg2 += nombre;
        msg2 += " is not a record nor an union";
        driver->error(loc,msg2);
        error_state = 1;
        return false;
    }
    return true;
}
/**
 * Indica si una categoria es igual a unionVar
 * o recordVar
 */
bool es_estructura(std::string categoria){
    return ((categoria.compare("unionVar") == 0) || categoria.compare("recordVar") == 0);
}


/**
 * Reporta cuando una variable se trata de usar y esta no 
 * estaba declarada.
 */
Symbol* variable_no_declarada(std::string name, GuavaDriver* driver, const yy::location& loc, GuavaSymTable* t){
    Symbol* id;
    if ((id = t->lookup(name)) == 0) {
        std::cout << "1 \n";
        std::string msg ("Undeclared identifier '");
        msg += name;
        msg += "'";
        driver->error(loc,msg);
        error_state = 1;
        return id;
    }
    return id;
}

/**
 * Reporta cuando una variable se trata de usar y esta no 
 * estaba declarada con un scope determinado.
 */
Symbol* variable_no_declarada(std::string name, GuavaDriver* driver, const yy::location& loc, int scope, GuavaSymTable* t){
    Symbol* id;
    if ((id = t->lookup(name, scope )) == 0) {
        std::string msg ("Undeclared identifier '");
        msg += name;
        msg += "'";
        driver->error(loc,msg);
        error_state = 1;
        return id;
    }
    return id;
}
/**
 * Retorna el error de que una variable ya ha sido
 * declarada.
 */
std::string reportar_existencia(Symbol *s, std::string id) {
    std::stringstream linea, columna;
    std::string msg("variable name: '");
    msg += id;
    msg += "' already used in line: ";
    linea << s->column;
    msg += columna.str();
    error_state = 1;
    return msg;
}

/**
 * Retorna un mensaje de que
 * el tipo id no existe.
 */
std::string tipo_no_existe(std::string id){
    std::string msg("Type '");
    msg += id;
    msg += "' wasn't declared or doesn't exists in current context";
    error_state = 1;
    return msg;
}
/**
 * Retorna un mensaje de que el id
 * no es un tipo en verdad.
 */
std::string no_es_tipo(std::string id){
    std::string msg("Identifier '");
    msg += id;
    msg += "' is not a type.";
    error_state = 1;
    return msg;
}

/**
 * Funcion que dado una instancia de la clase Tipo
 * y la tabla de simbolos retorna la direccion en donde esta el tipo.
 */
Symbol* obtener_tipo(std::string str, GuavaDriver *d, GuavaSymTable* t){
    Symbol *s = t->lookup(str);
    if (s == 0) return 0;
    if (s->true_type == 0) return 0;
    return s;
}
/**
 * "Encaja" el tamaño dado de un TypeS
 * en la palabra.
 */
int encajar_en_palabra(int tam){
    if (tam % WORD == 0) return tam;
    return (tam + (WORD - (tam % WORD)));  
}

/**
 * Dado un tipo basico, retorna el tamaño de este.
 * En caso de que TypeS* sea otra cosa aparte de un tipo basico
 * se retorna -1.
 */
int tamano_tipo(TypeS* t){
    if (t->is_bool()) return encajar_en_palabra(SIZE_BOOL);
    if (t->is_real()) return encajar_en_palabra(SIZE_REAL);
    if (t->is_int()) return encajar_en_palabra(SIZE_INT);
    if (t->is_char()) return encajar_en_palabra(SIZE_CHAR);
    if (t->is_reference()) return encajar_en_palabra(SIZE_REFERENCE);
    if (t->is_str()) return encajar_en_palabra(SIZE_REFERENCE);
    int result;

    if (t->is_structure()){
        result = 0;
        TypeS* tmp;
        TypeStructure *s = (TypeStructure*) t;
        std::list<TypeS*> list = s->atributos->get_types(0);
        while (!list.empty()){
            tmp = list.front();
            result += encajar_en_palabra(tamano_tipo(tmp));
            list.pop_front();
        }
        return result;
    }

    if (t->is_union()){
        result = 0;
        TypeS* tmp;
        TypeUnion* u = (TypeUnion*) t;
        std::list<TypeS*> list = u->atributos->get_types(0);
        while (!list.empty()){
            tmp = list.front();
            result = std::max(result, encajar_en_palabra(tamano_tipo(tmp)));
            list.pop_front();
        }
        return result;
    }

    if (t->is_array()){
        std::pair<int, int*> dimensiones = t->get_dimensiones();
        result = 1;
        for (int i = 0 ; i < dimensiones.first; ++i){
            result *= dimensiones.second[i];
        }
        return (result * encajar_en_palabra(tamano_tipo(t->get_tipo())) ); 
    }
    return -1; 
}

/**
 * Inserta un simbolo simple.
 * $4 -> vars ; $2 -> t
 */
void insertar_simboloSimple(LVar *vars, TypeS *t, std::string estilo, GuavaDriver *d, const yy::location& loc) {
    std::list<Identificador> l = vars->get_list();
    std::list<Identificador>::iterator it = l.begin();
    int scope,line, column;
    Symbol *s;

    GuavaSymTable *tabla = tabla_actual.front();

    Symbol *p=  obtener_tipo(t->get_name(),d, &d->tablaSimbolos);
    if (p == 0) {
        d->error(loc,tipo_no_existe(t->get_name()));
        return;
    }

    for(it; it!=l.end(); ++it) {
        s = d->tablaSimbolos.simple_lookup(it->identificador);
        if(s != 0)
            d->error(loc,reportar_existencia(s,it->identificador));
        else {
            scope = tabla->currentScope();
            line = it->line;
            column = it->column;
            int offset = offset_actual.front();
            if (offset != -1){
                offset_actual.pop_front();
                tabla->insert(it->identificador,estilo,scope,p,line,column,offset);
                offset += tamano_tipo(t); 
                offset_actual.push_front(offset);
            } else {
                tabla->insert(it->identificador,estilo,scope,p,line,column,0);
            }
        }
    }
}
/**
 * Inserta una sola variable simple.
 */
void insertar_simboloSimple(Identificador* identificador, TypeS *t, std::string estilo, GuavaDriver *d, const yy::location& loc) {
    int scope,line, column;
    Symbol *s;

    GuavaSymTable *tabla = tabla_actual.front();

    Symbol *p =  d->tablaSimbolos.lookup(t->get_name());
    if (p == 0)  d->error(loc,tipo_no_existe(t->get_name()));

    line = loc.begin.line;
    column = loc.begin.column;
    scope = tabla->currentScope();
    s = d->tablaSimbolos.simple_lookup(identificador->identificador);
    if (s != 0) {
        d->error(loc,reportar_existencia(s,identificador->identificador));
        return;
    }
    int offset = offset_actual.front();

    if (offset != -1){
        offset_actual.pop_front();
        tabla->insert(identificador->identificador,estilo,scope,p,line,column,offset);
        offset += tamano_tipo(t); 
        offset_actual.push_front(offset);
    } else {
            tabla->insert(identificador->identificador,estilo,scope,p,line,column,0);
    }
}

/**
 * Inserta una variable arreglo.
 * Cosas que usan el driver:
 * int scop = drvier.tablaSimbolos.currentScope();
 * Symbol *tmp = driver.tablaSimbolos.simple_lookup(par.first.identificador)
 * driver.tablaSimbolos.insert(it.first.identificador,std::string("array"),scop,t->tipo,line,column,arreglo,size);
 */
void insertar_simboloArreglo(LVarArreglo *vars, TypeS *t, GuavaDriver *d, const yy::location& loc) {
    std::list< std::pair<Identificador, LCorchetes> > l = vars->get_list();
    std::list< std::pair<Identificador, LCorchetes> >::iterator it = l.begin();
    std::list<Integer>::iterator itInt;
    std::pair<Identificador, LCorchetes> par;
    int size, scope, line, column;
    int *arreglo;
    Symbol *s;

    GuavaSymTable *tabla = tabla_actual.front();

    for(it; it != l.end(); ++it) {
        par = *it;
        s = tabla->simple_lookup(par.first.identificador);
        if(s != 0)
            d->error(loc,reportar_existencia(s,par.first.identificador));
        else {
            size = par.second.lista.size();
            arreglo = new int[size];
            itInt = par.second.lista.begin();

            for(int i=0; i != size; i++) {
                arreglo[i] = itInt->getValor();
                ++itInt;
            }
            TypeArray* arr = new TypeArray(t,size,arreglo); // Tipo de arreglo con la información concerniente.
            scope = tabla->currentScope();
            line = par.first.line;
            column = par.first.column;
            int offset = offset_actual.front();
            if (offset != -1){
                offset_actual.pop_front();
                tabla->insert(par.first.identificador,std::string("array"),scope,arr,line,column,offset);
                offset += tamano_tipo(t); 
                offset_actual.push_front(offset);
            } else {
                tabla->insert(par.first.identificador,std::string("array"),scope,arr,line,column,offset);
            }
        }
    }
}
/**
 * Dado un tipo "tipo", busca en la tabla ese tipo y
 * retorna un TypeS*.
 * Revisa los tipos basicos en la tabla de Driver.
 * Revisa otros tipos en t.
 */
TypeS* obtener_tipo_real(std::string tipo ,GuavaDriver *d, const yy::location& loc, GuavaSymTable* t){
    Symbol *p1 = obtener_tipo(tipo,d, t);

    if (p1 == 0) { 
        d->error(loc,tipo_no_existe(tipo));
        return 0;
    }
    if (p1->true_type == 0) { 
        d->error(loc,no_es_tipo(tipo));
        return 0;
    }
    if (p1 != 0 && p1->true_type != 0) return p1->true_type;
}

/**
 * Inserta una lista de variables de tipo estructura a la tabla
 * y retorna el tipo de esta.
 */
TypeS* insertar_simboloEstructura(LVar *vars, std::string tipo,std::string estilo,GuavaDriver *d, const yy::location& loc){
    std::list<Identificador> l = vars->get_list();
    std::list<Identificador>::iterator it = l.begin();
    int scope,line, column;
    Symbol *s;

    GuavaSymTable *tabla = tabla_actual.front();
    TypeS* reference = obtener_tipo_real(tipo,d,loc, tabla);
    if (reference == 0) return 0;

    for(it; it!=l.end(); ++it) {
        s = d->tablaSimbolos.simple_lookup(it->identificador);
        if(s != 0)
            d->error(loc,reportar_existencia(s,it->identificador));
        else {
            scope = tabla->currentScope();
            line = it->line;
            column = it->column;
            int offset = offset_actual.front();
            if (offset != -1){
                offset_actual.pop_front();
                tabla->insert(it->identificador,estilo,scope,reference,line,column, offset);
                offset += tamano_tipo(reference); 
                offset_actual.push_front(offset);
            } else {
                tabla->insert(it->identificador,estilo,scope,reference,line,column, 0);
            }
        }
    }
    return reference;
}

/**
 * Inserta una variable arreglo de estructura
 * El arreglo de estructura es un arreglo de variables que hacen
 * referencia a las estructuras. A su vez la variable arreglo
 * es una referencia al arreglo.
 */
TypeS* insertar_simboloArregloEstructura(LVarArreglo *vars, std::string t, GuavaDriver *d, const yy::location& loc) {
    std::list< std::pair<Identificador, LCorchetes> > l = vars->get_list();
    std::list< std::pair<Identificador, LCorchetes> >::iterator it = l.begin();
    std::list<Integer>::iterator itInt;
    std::pair<Identificador, LCorchetes> par;
    int size, scope, line, column;
    int *arreglo;
    Symbol *s;

    GuavaSymTable *tabla = tabla_actual.front();
    TypeS* reference0 = obtener_tipo_real(t,d,loc, tabla); 
    if (reference0 == 0) return 0;

    for(it; it != l.end(); ++it) {
        par = *it;
        s = d->tablaSimbolos.simple_lookup(par.first.identificador);
        if(s != 0)
            d->error(loc,reportar_existencia(s,par.first.identificador));
        else {
            size = par.second.lista.size();
            arreglo = new int[size];
            itInt = par.second.lista.begin();
            for(int i=0; i != size; i++) {
                arreglo[i] = itInt->getValor();
                ++itInt;
            }
            
            TypeArray* arr = new TypeArray(reference0,size,arreglo); // Tipo de arreglo con la información concerniente.
            scope = tabla->currentScope();
            line = par.first.line;
            column = par.first.column;
            int offset = offset_actual.front();
            if (offset != -1){
                offset_actual.pop_front();
                tabla->insert(par.first.identificador,std::string("array"),scope,arr,line,column, offset);
                offset += tamano_tipo(reference0); 
                offset_actual.push_front(offset);
            } else {
                tabla->insert(par.first.identificador,std::string("array"),scope,arr,line,column, 0);
            }
        }
    }
    return reference0;
}
/**
 * Inserta una funcion a la tabla.
 */
void insertar_funcion(TypeS* tipo, Identificador* id, LParam* lp ,GuavaDriver* d,int current_scope, const yy::location& loc){
    std::list<std::pair<TypeS*,Identificador*> > lista = lp->get_list();
    std::list <TypeS*> parametros;
    std::pair<TypeS*, Identificador*> par;
    std::list<std::pair<TypeS*,Identificador*> >::iterator it = lista.begin();
    for ( it ; it != lista.end(); ++it){
        par = *it;
        parametros.push_front(par.first); 
    }
    TypeS* function = new TypeFunction(tipo,parametros);
    GuavaSymTable *tabla = tabla_actual.front();
    tabla->insert_type(id->identificador,std::string("function"),0,function);
}

/**
 * Retorna un mensaje de error de tipos.
 */
std::string mensaje_error_tipos(std::string esperado, std::string encontrado) {
    std::string msg ("Type error: expected '");
    msg += esperado;
    msg += "'";
    msg += " found '";
    msg += encontrado;
    msg += "'";
    
    return msg;
}

/**
 * Dereferencia un TypeS* tipo Referencia.
 * Funciona como un & en C/C++
 */
TypeS* dereference(TypeS* referencia){
    TypeS* tmp = referencia->get_tipo();
    return tmp;
}
/**
 * Verifica que el acceso que se quiere realizar tiene sentido.
 */
void verificar_acceso_atributos(Symbol* id, std::list<Identificador*> la, GuavaDriver* driver, const yy::location& loc){
    if (id->true_type != 0){
        GuavaSymTable* tabla;
        TypeS* tipo = id->true_type; 
        if (tipo->is_structure()){
            TypeStructure* estructura = (TypeStructure*) tipo;
            tabla = estructura->atributos;
        } else{
            TypeUnion* estructura = (TypeUnion*) tipo;
            tabla = estructura->atributos;
        }
        if (la.empty()) return;
        Identificador* identificador = la.front();
        Symbol *tmp; 
        la.pop_front();

        //variable_no_declarada(std::string name, GuavaDriver* driver, const yy::location& loc, GuavaSymTable* t)

        if (( tmp = variable_no_declarada(identificador->identificador, driver, loc, tabla) ) != 0){
           verificar_acceso_atributos(tmp,la, driver, loc ); 
        }     

    } else{
        if (la.empty()) return;
        Identificador* identificador = la.front();
        Symbol *tmp; 
        la.pop_front();

        variable_no_declarada(identificador->identificador, driver, loc, &driver->tablaSimbolos);
    }
}

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
%type <classSelectorIf> selectorif selectorifLoop 
%type <classLoopWhile> loopwhile 
%type <classLoopFor> loopfor 
%type <classAsignacion> asignacion
%type <classInstruccion> instruccion instruccionLoop
%type <classInstruccion> instruccion1 instruccionLoop1
%type <classListaInstrucciones> listainstrucciones listainstruccionesLoop
%type <classLParam> lparam lparam2
%type <classLElseIf> lelseif lelseifLoop
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

program: bloqueprincipal { //$$ = Program(*$1); 
                         };

bloqueprincipal: { 
                  tabla_actual.push_front(&driver.tablaSimbolos);
                  driver.tablaSimbolos.enterScope(); 
                 } 
                 bloquedeclare lfunciones  { //$$ = new BloquePrincipal(*$2, *$3);
                                             if (!error_state) {
                                                std::cout << "Funciones: " << '\n';
                                                driver.tablaSimbolos.show(0,identacion+ "  ");
                                                std::cout << "Variables globales: \n";
                                                driver.tablaSimbolos.show(1,identacion+ "  ");
                                             }
                                           };

bloquedeclare: /* Vacio */                { $$ = new BloqueDeclare(-1); 
                                          }
             | { declare_scope = driver.tablaSimbolos.currentScope(); 
                 offset_actual.push_front(0);
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
                                                         TypeS* tmp = insertar_simboloEstructura($3,$1->identificador,std::string("unionVar"),&driver,yylloc); 
                                                         LVariables *tmpLV = new LVariables(tmp,$3); 
                                                         $$ = tmpLV;
                                                        }
          | lvariables identificador UNION lvar ';'     { 
                                                         TypeS* tmp = insertar_simboloEstructura($4,$2->identificador,std::string("unionVar"),&driver,yylloc); 
                                                         LVariables *tmpLV = new LVariables(tmp,$4); 
                                                         $1->listaVar = tmpLV;
                                                         $$ = $1;
                                                        }
          | identificador RECORD lvar                   {
                                                         TypeS* tmp = insertar_simboloEstructura($3,$1->identificador,std::string("recordVar"),&driver,yylloc); 
                                                         LVariables *tmpLV = new LVariables(tmp,$3); 
                                                         $$ = tmpLV;
                                                        }
          | lvariables identificador RECORD lvar ';'    { 
                                                         TypeS* tmp = insertar_simboloEstructura($4,$2->identificador,std::string("recordVar"),&driver,yylloc); 
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

union: UNION identificador '{' { TypeUnion* structure = new TypeUnion();
                                 structure->nombre = $2->identificador;
                                 GuavaSymTable *tabla = tabla_actual.front();
                                 int n = tabla->currentScope();
                                 tabla->insert_type($2->identificador, std::string("unionType"),n,structure); 
                                 tabla_actual.push_front(structure->atributos);
                                 identacion += "  ";
                                 offset_actual.push_front(-1);
                               }
                              lvariables '}' { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                if (!error_state) {
                                                    identacion.erase(0,2);
                                                    std::cout << identacion << "Union " << $2->identificador << " {\n";
                                                    tabla->show(tabla->currentScope(),identacion+ "  "); 
                                                    std::cout << identacion <<"}\n";
                                                }
                                                offset_actual.pop_front();
                                                tabla_actual.pop_front();
                                             }

record: RECORD identificador '{'{
                                 TypeStructure* structure = new TypeStructure();
                                 structure->nombre = $2->identificador;
                                 GuavaSymTable *tabla = tabla_actual.front();
                                 int n = tabla->currentScope();
                                 tabla->insert_type($2->identificador, std::string("recordType"),n,structure); 
                                 tabla_actual.push_front(structure->atributos);
                                 identacion += "  ";
                                 offset_actual.push_front(0);
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

lvar: identificador           { LVar *tmp = new LVar();
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
            | lvararreglo ',' error lcorchetes         {};



lcorchetes: '[' INTEGER ']'         { 
                                      LCorchetes *nuevo =  new LCorchetes();
                                      nuevo->append(*(new Integer($2)));
                                      $$ = nuevo;
                                    }
          | lcorchetes '[' INTEGER ']' { 
                                         $1->append(*(new Integer($3)));
                                         $$ = $1; 
                                       }
          /*Errores*/
          | '[' error ']'           {/*Definicion erronea del tamano del arreglo*/}
          | lcorchetes '[' error ']' {};

lcorchetesExp: '[' exp ']'               {}
             | lcorchetesExp '[' exp ']' {}
             | '[' error ']'             {}
             |  lcorchetesExp '[' error ']' {}


lfunciones: funcionmain                    { //*$$ = LFunciones(*$2,0);*/
                                           }
          | lfunciones1 funcionmain        { /*$$ = LFunciones(*$2,$1); */ 
                                           }

lfunciones1: funcion              { /*$$ = LFunciones(*$1,0);*/
                                  }
           | lfunciones1 funcion  { /*$$ = LFunciones(*$2,$1);*/
                                  }

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                   TypeS* function = new TypeFunction(TypeVoid::Instance());
                                                   int line = yylloc.begin.line;
                                                   int column = yylloc.begin.column;
                                                   driver.tablaSimbolos.insert(std::string("main"),std::string("function"),
                                                                                    0,function,line,column, current_scope);
                                                   identacion += "  ";
                                                 } 
                                                bloquedeclare listainstrucciones  '}' { /*Tipo v = Tipo(std::string("void"));
                                                                                        LParam lp = LParam();
                                                                                        *$$ = Funcion(v,Identificador(std::string("main")),lp,*$8,*$9,0);*/ 
                                                                                        if (!error_state) {
                                                                                          std::cout <<  "main {\n"; 
                                                                                          std::cout << "Parametros y variables:\n";
                                                                                          driver.tablaSimbolos.show(current_scope,identacion);
                                                                                          driver.tablaSimbolos.exitScope(); 
                                                                                          std::cout << "}\n";
                                                                                          identacion.erase(0,2);
                                                                                        }
                                                                                      }
/*Errores*/
/*Mala especificacion del encabezado de la funcion*/
          | FUNCTION TYPE_VOID MAIN '(' error ')' '{' { current_scope = driver.tablaSimbolos.enterScope();
                                                        identacion += "  ";
                                                      } 
                                                     bloquedeclare listainstrucciones  '}' { /*Tipo v = Tipo(std::string("void"));
                                                                                             LParam lp = LParam();
                                                                                             *$$ = Funcion(v,Identificador(std::string("main")),lp,*$8,*$9,0);*/
                                                                                            }


funcion: FUNCTION tipo identificador '('  { current_scope = driver.tablaSimbolos.enterScope(); }
                                         lparam { 
                                                  insertar_funcion($2,$3,$6,&driver,current_scope,yylloc); 
                                                  identacion += "  ";
                                                 } ')' '{' 
                                                       bloquedeclare listainstrucciones RETURN exp ';' '}' { /**$$ = Funcion(*$2,Identificador(std::string($3))
                                                                                                                            ,*$5,*$9,*$10,*$12);*/ 
                                                                                                             if (!error_state) {
                                                                                                               std::cout << $3->identificador << "{\n";
                                                                                                               std::cout << "Parametros y variables:\n";
                                                                                                               driver.tablaSimbolos.show(current_scope,identacion);
                                                                                                               std::cout << "}\n";
                                                                                                               driver.tablaSimbolos.exitScope();
                                                                                                               identacion.erase(0,2);
                                                                                                             }
                                                                                                           }

        | FUNCTION TYPE_VOID identificador '(' { current_scope = driver.tablaSimbolos.enterScope(); } 
                                               lparam  {  
                                                         TypeS* v = TypeVoid::Instance();
                                                         insertar_funcion(v,$3,$6,&driver,current_scope,yylloc); 
                                                         identacion += "  ";
                                                       } ')' '{' bloquedeclare listainstrucciones '}'
                                                                                                      { 
                                                                                                        if (!error_state) {
                                                                                                            std::cout << $3->identificador << "{\n";
                                                                                                            std::cout << "Parametros y variables:\n";
                                                                                                            driver.tablaSimbolos.show(current_scope,identacion);
                                                                                                            std::cout << "}\n";
                                                                                                            driver.tablaSimbolos.exitScope();
                                                                                                            identacion.erase(0,2);
                                                                                                        }
                                                                                                      }

/*Errores*/
/*Mala especificacion del encabezado de la funcion*/
        | FUNCTION tipo identificador '(' error ')' '{' { current_scope =  driver.tablaSimbolos.enterScope(); 
                                                          identacion += "  ";
                                                        }
                                                       bloquedeclare listainstrucciones RETURN exp ';' '}' {  
                                                                                                           }

/*Mala especificacion del encabezado de la funcion*/
        | FUNCTION TYPE_VOID identificador '(' error ')' '{' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                               int line = yylloc.begin.line;
                                                               int column = yylloc.begin.column;
                                                               identacion += "  ";
                                                             }
                                                            bloquedeclare listainstrucciones '}'           { 
                                                                                                            };
/*LISTO*/
lparam: /* Vacio */          { $$ = new LParam(); 
                             } 
      | lparam2              { 
                             } 

lparam2: tipo identificador               { LParam* tmp = new LParam(); 
                                            tmp->append($1,$2);
                                            $$ = tmp;
                                            insertar_simboloSimple($2,$1,std::string("param"),&driver,yylloc);
                                          } 
        | tipo REFERENCE identificador    { LParam* tmp = new LParam(); 
                                            tmp->append($1,$3);
                                            $$ = tmp;
                                            insertar_simboloSimple($3,$1,std::string("param"),&driver,yylloc); // llamada a otra funcion
                                          } 
        | lparam2 ',' tipo identificador  { 
                                            $1->append($3,$4);
                                            $$ = $1;
                                            insertar_simboloSimple($4,$3,std::string("param"),&driver,yylloc);
                                          }
        | lparam2 ',' tipo REFERENCE 
                      identificador       { 
                                            $1->append($3,$5);
                                            $$ = $1;
                                            insertar_simboloSimple($5,$3,std::string("param"),&driver,yylloc);
                                          }
        
        | tipo error                        { $$ = new LParam();    }
        | tipo REFERENCE error              { $$ = new LParam();    }
        | lparam2 ',' tipo error            { $$ = new LParam();    }
        | lparam2 ',' tipo REFERENCE error  { $$ = new LParam();    };


listainstrucciones: /* Vacio */                        { //$$ = ListaInstrucciones(); 
                                                       }
                  |listainstrucciones instruccion ';'  { //$$ = ListaInstrucciones($1,$3); 
                                                       }
                  | listainstrucciones instruccion1    { //$$ = ListaInstrucciones($1,$2); 
                                                       };

instruccion: asignacion     { 
                            }
           | llamadafuncion { 
                            }
           | MINUSMINUS identificador  { 
                                         if (variable_no_declarada($2->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$2, 0);
                                         }
                                       }
           | identificador MINUSMINUS { if ( variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$1, 1); 
                                         }
                                       }
           | PLUSPLUS identificador    { if ( variable_no_declarada($2->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$2, 2); 
                                         }
                                       }
           | identificador PLUSPLUS    { if ( variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$1, 3); 
                                         }
                                       }
           | entradasalida  { 
                            }
           | CONTINUE       {
                            }
           | BREAK          {
                            }
           /*Errores*/
           | error identificador       {/*Error en la especificacion del incremento o decremento*/}
           | identificador error       {/*Error en la especificacion del incremento o decremento*/}



instruccion1: loopfor        { 
                             }
            | loopwhile      { 
                             }
            | selectorif     { 
                             };

listainstruccionesLoop: /* Vacio */                                {}
                      | listainstruccionesLoop instruccionLoop ';' {}
                      | listainstruccionesLoop instruccionLoop1    {} 

instruccionLoop: asignacion     { 
                                }
           | llamadafuncion     { 
                                }
           | MINUSMINUS identificador  {
                                         if ( variable_no_declarada($2->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$2, 0);
                                         }
                                       }
           | identificador MINUSMINUS { if ( variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$1, 1); 
                                         }
                                       }
           | PLUSPLUS identificador    { if ( variable_no_declarada($2->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$2, 2); 
                                         }
                                       }
           | identificador PLUSPLUS    { if ( variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()) != 0){
                                            $$ = new PlusMinus(*$1, 3); 
                                         }
                                       }
           | entradasalida  { 
                            }
           | CONTINUE       {
                            }
           | BREAK          {
                            }
           /*Errores*/
           | error identificador       {/*Error en la especificacion del incremento o decremento*/}
           | identificador error       {/*Error en la especificacion del incremento o decremento*/}


instruccionLoop1: loopfor        { 
                                 }
                | loopwhile      { 
                                 }
                | selectorifLoop { 
                                 };



asignacion: expID ASSIGN exp  {
                              } 
            /*Errores*/
            | error ASSIGN exp  {
                                }
            | expID ASSIGN error {};


/*Esto hay que cambiarlo.*/
entradasalida: READ '(' lvarovalor ')' { //*$$ = EntradaSalida(0, *$3); 
                                       }
             | PRINT '(' lvarovalor ')'  { //*$$ = EntradaSalida(1, *$3); 
                                         };

loopfor: FOR '(' identificador ';' expBool ';' errorloopfor ')' '{' { variable_no_declarada($3->identificador,&driver,yylloc, tabla_actual.front()); 
                                                                      driver.tablaSimbolos.enterScope();   
                                                                      identacion += "  "; 
                                                                    }
                                                            bloquedeclare listainstruccionesLoop '}' { /*Identificador id = Identificador(std::string($3));
                                                                                                    *$$ = LoopFor(id,$5,*$7,*$11,*$12);*/ 
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
                                                      bloquedeclare listainstruccionesLoop '}' { /*Identificador id = Identificador(std::string($3));
                                                                                              *$$ = LoopFor(id,$5,*$7,*$11,*$12);*/ 
                                                                                           }
       | FOR '(' identificador ';' error  ';' errorloopfor ')' '{' { variable_no_declarada($3->identificador,&driver,yylloc, tabla_actual.front());
                                                                   }
                                                                 bloquedeclare listainstruccionesLoop '}' { /*Identificador id = Identificador(std::string($3));
                                                                                                         *$$ = LoopFor(id,$5,*$7,*$11,*$12);*/ 
                                                                                                      };
/**
 * Regla utilizada en el manejo de errores del encabezado de una iteracion
 * acotada
 */
errorloopfor : asignacion {}
             | exp        {}
             | error      {};


/*LISTO*/
loopwhile: WHILE '(' errorloopwhile ')' DO '{' { 
                                                 driver.tablaSimbolos.enterScope();   
                                                 identacion += "  ";
                                               }
                                             bloquedeclare listainstruccionesLoop '}' { /**$$ = LoopWhile($3,*$8,*$9); */
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
                   bloquedeclare listainstruccionesLoop '}' WHILE '(' errorloopwhile ')' { /**$$ = LoopWhile($9,*$4,*$5); */
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
errorloopwhile : expBool    {}
               | error  {};

selectorif: IF '(' errorif ')' THEN '{' { 
                                          driver.tablaSimbolos.enterScope();   
                                          identacion += "  ";
                                        }
                                        bloquedeclare listainstrucciones '}' lelseif { /**$$ = SelectorIf($3,$8,$9,$11);*/
                                                                                        driver.tablaSimbolos.exitScope();
                                                                                        identacion.erase(0,2);
                                                                                    
                                                                                 }
           | IF '(' errorif ')' THEN instruccion ';'                             { //*$$ = SelectorIf($3,$6,0); 
                                                                                 }
           | IF '(' errorif ')' THEN instruccion ELSE instruccion ';'            { //*$$ = SelectorIf($3,$6,$8); 
                                                                                 };


lelseif: /* Vacio */                                                               { //*$$ = LElseIf(); 
                                                                                   }
       | lelseif1 ELSE '{' { 
                             driver.tablaSimbolos.enterScope();   
                           }
                           bloquedeclare listainstrucciones '}'                              { /**$$ = LElseIf(*$4,*$5); */
                                                                                               driver.tablaSimbolos.exitScope();
                                                                                             };

lelseif1: /*Vacio*/
        | lelseif1 ELSE IF '(' errorif ')' THEN '{' { 
                                                      driver.tablaSimbolos.enterScope();   
                                                    }
                                                    bloquedeclare listainstrucciones '}' { /**$$ = LElseIf($4,*$9,*$10,$12);*/
                                                                                           driver.tablaSimbolos.exitScope();
                                                                                         };


selectorifLoop: IF '(' errorif ')' THEN '{' { 
                                              driver.tablaSimbolos.enterScope();   
                                              identacion += "  ";
                                            }
                                           bloquedeclare listainstruccionesLoop '}' lelseifLoop { /**$$ = SelectorIf($3,$8,$9,$11);*/
                                                                                                  driver.tablaSimbolos.exitScope();
                                                                                                  identacion.erase(0,2);
                                                                                                }
           | IF '(' errorif ')' THEN instruccionLoop ';'                                        { 
                                                                                                 //*$$ = SelectorIf($3,$6,0); 
                                                                                                }
           | IF '(' errorif ')' THEN instruccion ELSE instruccionLoop ';'                       { //*$$ = SelectorIf($3,$6,$8); 
                                                                                                };


lelseifLoop: /* Vacio */                                                               { //*$$ = LElseIf(); 
                                                                                   }
           | lelseifLoop1 ELSE '{' { 
                                   driver.tablaSimbolos.enterScope();   
                                   }
                                 bloquedeclare listainstruccionesLoop '}'  { 
                                                                             driver.tablaSimbolos.exitScope();
                                                                           };

lelseifLoop1: /*Vacio*/
        | lelseifLoop1 ELSE IF '(' errorif ')' THEN '{' { 
                                                          driver.tablaSimbolos.enterScope();   
                                                        }
                                                      bloquedeclare listainstruccionesLoop '}' { /**$$ = LElseIf($4,*$9,*$10,$12);*/
                                                                                                driver.tablaSimbolos.exitScope();
                                                                                               };

/**
 * Regla utilizada para el manejo de errores de los selectores de bloques e
 * instrucciones if-then-else.
 */
errorif : expBool   {}
        | error     {};

llamadafuncion: identificador '(' lvarovalor ')' { //*$$ = LlamadaFuncion(Identificador(std::string($1)),*$3); 
                                                    if (driver.tablaSimbolos.lookup($1->identificador,0) == 0){
                                                        std::string msg ("Undefined function '");
                                                        msg += $1->identificador;
                                                        msg += "'";
                                                        driver.error(yylloc,msg);
                                                        error_state = 1;
                                                    }
                                                 }
              | error '(' lvarovalor ')'         {/*Llamado a una funcion con identificador erroneo*/};


lvarovalor: /* Vacio */   { 
                            $$ = new LVaroValor(); 
                          }
          | lvarovalor2   { $$ = $1;
                          };      
          
lvarovalor2: lvarovalor2 ',' exp     { 
                                      $1->append(*$3);
                                      $$ = $1;
                                     }
           | exp                     {
                                       LVaroValor *tmp = new LVaroValor();
                                       tmp->append(*$1);
                                       $$ = tmp; 
                                     }
           | lvarovalor2 ',' error   {}
           | error                   {
                                       LVaroValor *tmp = new LVaroValor();
                                       $$ = tmp;
                                     };

exp: expAritmetica  { $$ = $1; }
   | expBool        { $$ = $1; } 
   | valor          { $$ = $1; }
   | expID          { $$ = $1; } 
   | '(' exp ')'    { $$ = $2; }
   | llamadafuncion { $$ = $1; /*Supondremos que una llamada a una funcion es una expresion*/}
   | '(' error ')'  {};
      

expID: identificador   { TypeS* tipo;
                         Symbol* id;
                         if ( (id = variable_no_declarada($1->identificador,&driver,yylloc, tabla_actual.front()))  != 0) {
                                $$ = new Identificador($1->identificador);
                                tipo = id->type_pointer->true_type;
                                $$->tipo = tipo;
                         }
                       }
     | identificador lcorchetesExp    {
                                        variable_no_declarada($1->identificador,&driver, yylloc, tabla_actual.front());
                                      }
     | identificador lAccesoAtributos { 
                                        Symbol * id;
                                        Identificador *prueba = $1;
                                        if ((id = variable_no_declarada(prueba->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                            if (es_estructura_error(id->sym_catg, $1->identificador,&driver,yylloc)){
                                                std::list<Identificador*> tmp = $2->get_list();
                                                tmp.pop_front();
                                                verificar_acceso_atributos(id, tmp, &driver,yylloc) ;
                                            }
                                        }
                                       };

 
/*Faltan pruebas*/
expBool: exp AND exp         { if ($1->tipo == TypeBool::Instance() &&
                                   $3->tipo == TypeBool::Instance())
                               { $$ = new ExpBin($1,$3,std::string("AND"));
                                 $$->tipo = $1->tipo;
                               }
                               else {
                               }
                             }
       | exp OR exp          { if ($1->tipo == TypeBool::Instance() &&
                                   $3->tipo == TypeBool::Instance())
                               { $$ = new ExpBin($1,$3,std::string("OR"));
                                 $$->tipo = $1->tipo;
                               }
                               else {
                               }
                             }
       | exp COMPARISON exp  { if ($1->tipo == $3->tipo &&
                                   ($1->tipo == TypeInt::Instance() ||
                                    $1->tipo == TypeReal::Instance())) {
                                 int cmpv = $2;
                                 switch(cmpv){
                                      case 1:
                                          $$ = new ExpBin(*$1,*$3,std::string(">"));
                                          $$->tipo = TypeBool::Instance();
                                          break;
                                      case 2:
                                          $$ = new ExpBin(*$1,*$3,std::string("<"));
                                          $$->tipo = TypeBool::Instance();
                                          break;
                                      case 3:
                                          $$ = new ExpBin(*$1,*$3,std::string("<="));
                                          $$->tipo = TypeBool::Instance();
                                          break;
                                      case 4:
                                          $$ = new ExpBin(*$1,*$3,std::string(">="));
                                          $$->tipo = TypeBool::Instance();
                                          break;
                                      case 5:
                                          $$ = new ExpBin(*$1,*$3,std::string("="));
                                          $$->tipo = TypeBool::Instance();
                                          break;
                                      case 6:
                                          $$ = new ExpBin(*$1,*$3,std::string("!="));
                                          $$->tipo = TypeBool::Instance();
                                          break;
                                 }
                               }
                               else {
                               }
                             }
       | NOT exp             { if ($2->tipo == TypeBool::Instance())
                               { std::string * op = new std::string("NOT");
                                 $$ = new ExpUn(*$2,op);
                                 $$->tipo = $2->tipo;
                               }
                               else {
                               }
                             };
      


expAritmetica: '-' exp %prec UMINUS  { if ($2->tipo == TypeInt::Instance() ||
                                           $2->tipo == TypeReal::Instance())
                                       { std::string * op = new std::string("-");
                                         $$ = new ExpUn(*$2,op);
                                         $$->tipo = $2->tipo;
                                       }
                                       else {
                                       }
                                     }
             | exp PLUSPLUS          { if ($1->tipo == TypeInt::Instance())
                                       { std::string * op = new std::string("++");
                                         $$ = new ExpUn(*$1,op);
                                         $$->tipo = $1->tipo;
                                         std::cout << "\n\nHOLA MIJOOOMM\n\n";
                                       }
                                       else {
                                         std::cout << "\n\nHELLEGOOD\n\n";
                                       }
                                     }
             | exp MINUSMINUS        { if ($1->tipo == TypeInt::Instance())
                                       { std::string * op = new std::string("--");
                                         $$ = new ExpUn(*$1,op);
                                         $$->tipo = $1->tipo;
                                       }
                                       else {
                                       }
                                     }
             | exp UFO exp           { if ($1->tipo == $3->tipo &&
                                           ($1->tipo == TypeInt::Instance() ||
                                            $1->tipo == TypeReal::Instance()))
                                       { $$ = new ExpBin(*$1,*$3,std::string("<=>"));
                                         $$->tipo = TypeInt::Instance();
                                        // El tipo de esta expresion es integer, recordar que UFO devuelve -1,0,1.
                                       }
                                       else {
                                       }
                                     }
             | exp '+' exp           { $$ = new ExpBin(*$1,*$3,std::string("+"));
                                       if ($1->tipo == $3->tipo && 
                                           ($1->tipo == TypeInt::Instance() ||
                                            $1->tipo == TypeReal::Instance()))
                                       { $$->tipo = $1->tipo;
                                       }
                                       else {
                                         if ($1->tipo != TypeInt::Instance() &&
                                             $1->tipo != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         $$->tipo = TypeError::Instance();
                                       }
                                     }
             | exp '-' exp           { $$ = new ExpBin(*$1,*$3,std::string("-"));
                                       if ($1->tipo == $3->tipo &&
                                           ($1->tipo == TypeInt::Instance() ||
                                            $1->tipo == TypeReal::Instance()))
                                       { $$->tipo = $1->tipo;
                                       }
                                       else {
                                         if ($1->tipo != TypeInt::Instance() &&
                                             $1->tipo != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         $$->tipo = TypeError::Instance();
                                       }
                                     }
             | exp '*' exp           { $$ = new ExpBin(*$1,*$3,std::string("*"));
                                       if ($1->tipo == $3->tipo &&
                                           ($1->tipo == TypeInt::Instance() ||
                                            $1->tipo == TypeReal::Instance()))
                                       { $$->tipo = $1->tipo;
                                       }
                                       else {
                                         if ($1->tipo != TypeInt::Instance() &&
                                             $1->tipo != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         $$->tipo = TypeError::Instance();
                                       }
                                     }
             | exp '/' exp           { $$ = new ExpBin(*$1,*$3,std::string("/"));
                                       if ($1->tipo == $3->tipo &&
                                           ($1->tipo == TypeInt::Instance() ||
                                            $1->tipo == TypeReal::Instance()))
                                       { $$->tipo = $1->tipo;
                                       }
                                       else {
                                         if ($1->tipo != TypeInt::Instance() &&
                                             $1->tipo != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$1->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",$3->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         $$->tipo = TypeError::Instance();
                                       }
                                     }
             | exp DIV exp           { $$ = new ExpBin(*$1,*$3,std::string("DIV"));
                                       if ($1->tipo == $3->tipo &&
                                           $1->tipo == TypeInt::Instance())
                                       { $$->tipo = $1->tipo;
                                       }
                                       else {
                                         if ($1->tipo != TypeInt::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer'",$1->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer'",$3->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         $$->tipo = TypeError::Instance();
                                       }
                                     }
             | exp MOD exp           { $$ = new ExpBin(*$1,*$3,std::string("MOD"));
                                       if ($1->tipo == $3->tipo &&
                                           $1->tipo == TypeInt::Instance())
                                       { $$->tipo = $1->tipo;
                                       }
                                       else {
                                         if ($1->tipo != TypeInt::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer'",$1->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer'",$3->tipo->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         $$->tipo = TypeError::Instance();
                                       }
                                     }
             | exp POW exp           { //OJO: Se puede aplicar exponenciacion a numeros reales?
                                     };

/*Funciona*/
valor: BOOL     { 
                  $$ = new Bool($1);
                  $$->tipo = TypeBool::Instance();
                }
     | STRING   { 
                  $$ = new String($1);
                  $$->tipo = TypeString::Instance();
                }
     | CHAR     { 
                  $$ = new Char($1);
                  $$->tipo = TypeChar::Instance();
                }
     | INTEGER  { 
                  $$ = new Integer($1);
                  $$->tipo = TypeInt::Instance();
                }
     | REAL     { 
                  $$ = new Real($1);
                  $$->tipo = TypeReal::Instance();
                }
     | arreglo  {
                  $$ = $1;
                }

/*Funciona*/

/* PRUEBA CON LA NUEVA FORMA DE USAR TIPOS*/
tipo: TYPE_REAL     { 
                      $$ = TypeReal::Instance();
                      //$$ = new Tipo(*(new std::string("real")), TypeReal::Instance() );
                    }
     | TYPE_INTEGER { 
                      $$ = TypeInt::Instance();
                      //$$ = new Tipo(*(new std::string("integer")), TypeInt::Instance() );
                    }
     | TYPE_BOOLEAN { 
                      $$ = TypeBool::Instance();
                      //$$ = new Tipo(*(new std::string("boolean")), TypeBool::Instance() );
                    }
     | TYPE_CHAR    { 
                      $$ = TypeChar::Instance();
                      //$$ = new Tipo(*(new std::string("character")), TypeChar::Instance() );
                    }
     | TYPE_STRING  { 
                      $$ = TypeString::Instance();
                      //$$ = new Tipo(*(new std::string("string")), TypeString::Instance() );
                    };


/*Funciona*/
arreglo: '[' larreglo ']' {
                            Arreglo* tmp;
                            LArreglo *lr = $2;
                            tmp = new Arreglo(lr);
                            $$ = tmp; 
                          };

/*Funciona. Faltan ejemplos mas interesantes.*/

larreglo: larreglo ',' exp      { 
                                  $1->append(*$3);
                                  $$ = $1;
                                }
        | exp                   { 
                                  LArreglo *tmp = new LArreglo();
                                  tmp->append(*$1);
                                  $$ = tmp;
                                 
                                }
        /*Errores*/
        | larreglo ',' error    { $$ = $1; }
        | error                 { LArreglo *tmp = new LArreglo(); };


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
