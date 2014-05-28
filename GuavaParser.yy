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
 * Funcion que obtiene recursivamente el TypeS* de un
 * simbolo id.
 */ 
TypeS* obtener_tipo_simbolo(Symbol* id){
    if (id->true_type != 0) return id->true_type;
    if (id->type_pointer != 0) return obtener_tipo_simbolo(id->type_pointer);
    return 0;
}

/**
 * Avisa si la variable es de categoria estructura
 * e imprime .
 */
bool es_estructura_error(std::string categoria,std::string nombre ,  GuavaDriver* driver, const yy::location& loc){
    if ((categoria.compare("unionType") != 0) && categoria.compare("recordType") != 0){
        std::string msg2 ("The ");
        msg2 += categoria+" '"+nombre+"' is not a record nor an union.";
        driver->error(loc,msg2);
        error_state = 1;
        return true;
    }
    return false;
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
    Symbol* id = 0;
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
 * Retorna el mensaje de error de que una variable ya ha sido
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
 * Retorna el mensaje de error de un tipo ya ha sido
 * declarada.
 */
std::string reportar_existencia_tipo(Symbol *s, std::string id) {
    std::stringstream linea, columna;
    std::string msg("Type name '");
    msg += id;
    msg += "' already used in this context.";
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
 * Retorna un mensaje de error de tipos.
 */
std::string mensaje_error_tipos(std::string esperado, std::string encontrado) {
    std::string msg ("Type error: expected '");
    msg += esperado+"' found: '"+encontrado+"'";
    return msg;
}

std::string mensaje_diff_operandos(std::string operador, std::string op1, std::string op2, std::string expected) {
    std::string msg ("Type error: cannot use operator: '");
    msg += operador+"' with types: '"+op1+"' and '"+op2+"', expected both: '"+expected+"'";
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
        TypeRecord *s = (TypeRecord*) t;
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
    std::list<int>::iterator itInt;
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
                arreglo[i] = *itInt;
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
                offset += tamano_tipo(arr); 
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
 * Retorna mensaje de tipo recursivo
 */
std::string reportar_tipo_recursivo(std::string t){
    std::string msg ("Can not declare a variable of a undefined type ''");
    msg += t;
    msg += "'";
    error_state = 1;
    return msg;
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
    TypeS* parent = 0;

    for(it; it!=l.end(); ++it) {
        s = d->tablaSimbolos.simple_lookup(it->identificador);
        if(s != 0)
            d->error(loc,reportar_existencia(s,it->identificador));
        else if ( (parent = tabla->get_parent()) != 0) {
           if (parent->get_name() == tipo){
                d->error(loc,reportar_tipo_recursivo(tipo));
           } else {
                goto agregar;
           }
        }
        else {
        agregar:
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
    std::list<int>::iterator itInt;
    std::pair<Identificador, LCorchetes> par;
    int size, scope, line, column;
    int *arreglo;
    Symbol *s;

    GuavaSymTable *tabla = tabla_actual.front();
    TypeS* reference0 = obtener_tipo_real(t,d,loc, tabla); 
    if (reference0 == 0) return 0;
    TypeS* parent;

    for(it; it != l.end(); ++it) {
        par = *it;
        s = d->tablaSimbolos.simple_lookup(par.first.identificador);
        if(s != 0)
            d->error(loc,reportar_existencia(s,par.first.identificador));
        else if ( (parent = tabla->get_parent()) != 0) {
           if (parent->get_name() == t){
            d->error(loc,reportar_tipo_recursivo(t));
           } else {
            goto agregar;
           }
        }
        else {
        agregar:
            size = par.second.lista.size();
            arreglo = new int[size];
            itInt = par.second.lista.begin();
            for(int i=0; i != size; i++) {
                arreglo[i] = *itInt;
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
    std::list<TypeS*> prueba = parametros;
    TypeFunction* function = new TypeFunction(tipo,prueba);
    GuavaSymTable *tabla = tabla_actual.front();
    tabla->insert_type(id->identificador,std::string("function"),0,function);
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
TypeS* verificar_acceso_atributos(Symbol* id, std::list<Identificador*> la, GuavaDriver* driver, const yy::location& loc){
    if (id->true_type != 0) {
        GuavaSymTable* tabla;
        TypeS* tipo = id->true_type; 
        if (tipo->is_structure()) {
            TypeRecord* estructura = (TypeRecord*) tipo;
            tabla = estructura->atributos;
        }
        else {
            TypeUnion* estructura = (TypeUnion*) tipo;
            tabla = estructura->atributos;
        }
        if (la.empty()) return id->true_type;
        Identificador* identificador = la.back();
        Symbol *tmp; 
        la.pop_back();

        //variable_no_declarada(std::string name, GuavaDriver* driver, const yy::location& loc, GuavaSymTable* t)

        if (( tmp = variable_no_declarada(identificador->identificador, driver, loc, tabla) ) != 0){
            return verificar_acceso_atributos(tmp,la, driver, loc ); 
        }     
    } 
    else{
        if (la.empty()) return obtener_tipo_simbolo(id);
        Identificador* identificador = la.front();
        Symbol *tmp; 
        la.pop_front();

        variable_no_declarada(identificador->identificador, driver, loc, &driver->tablaSimbolos);
    }

    return 0;
}

/**
 * Verifica la existencia de un tipo y lo agrega a la tabla. 
 */
void verificar_existencia_tipo(Identificador* id, GuavaDriver* d,const yy::location& loc, bool is_union){
    TypeStructure *structure;
    if (is_union){
        structure = new TypeUnion();
        offset_actual.push_front(-1);
        GuavaSymTable* tmp = structure->get_tabla();
        tmp->set_parent(structure);
    } else{
        structure = new TypeRecord();
        offset_actual.push_front(0);
        GuavaSymTable* tmp = structure->get_tabla();
        tmp->set_parent(structure);
    }
    structure->set_name(id->identificador);
    GuavaSymTable *tabla = tabla_actual.front();
    int n = tabla->currentScope();
    identacion += "  ";
    Symbol * tmp = 0;
    if ( (tmp = tabla->lookup(id->identificador)) == 0){
        if (tabla->get_parent() == 0){
            tabla->insert_type(id->identificador, std::string("unionType"),n,structure); 
        } else {
            if (tabla->get_parent()->get_name() == id->identificador){
                d->error(loc, reportar_existencia_tipo(tmp,id->identificador));
            } else {
                tabla->insert_type(id->identificador, std::string("unionType"),n,structure); 
            }
        }
    } else {
        d->error(loc, reportar_existencia_tipo(tmp,id->identificador));
    }
    tabla_actual.push_front(structure->get_tabla());
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
%type <classLElseIf> lelseif lelseifLoop lelseif1 lelseifLoop1
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

%start program
/*%destructor { delete $$; } ID*/
%% /* Reglas */

program: bloqueprincipal { //$$ = Program(*$1); 
                         };

bloqueprincipal: { 
                     tabla_actual.push_front(&driver.tablaSimbolos);
                     driver.tablaSimbolos.enterScope(); 
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
                                           }

lfunciones1: funcion                       { $$ = new LFunciones($1,0);
                                           }
           | lfunciones1 funcion           { 
                                             LFunciones* func = new LFunciones($2,0);
                                             $1->lista = func;
                                             $$ = $1;
                                           }

funcionmain: FUNCTION TYPE_VOID MAIN '(' ')' '{' { current_scope = driver.tablaSimbolos.enterScope(); 
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   int line = yylloc.begin.line;
                                                   int column = yylloc.begin.column;
                                                   driver.tablaSimbolos.insert(std::string("main"),std::string("function"),
                                                                                0,tipo,line,column, current_scope);
                                                   identacion += "  ";
                                                 } 
           bloquedeclare listainstrucciones  '}' { LParam lp = LParam();
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   $$ = new  Funcion(tipo,Identificador(std::string("main")),lp,*$8,*$9,0); 
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
                                                         LParam lp = LParam();
                                                         $$ = new Funcion(t,Identificador(std::string("main")),lp,*$9,*$10,0);
                                                       }


funcion: FUNCTION tipo identificador '('  { current_scope = driver.tablaSimbolos.enterScope(); }
                                        lparam { 
                                                 insertar_funcion($2,$3,$6,&driver,current_scope,yylloc); 
                                                 identacion += "  ";
                                               } ')' '{' 
                                        bloquedeclare listainstrucciones RETURN exp ';' '}' { if ($2->get_tipo() == $13->get_tipo()) {
                                                                                                TypeS* tipo = new TypeFunction($2->get_tipo(),$6->get_tipos());
                                                                                                $$ = new Funcion(tipo,*$3,*$6,*$10,*$11,$13);
                                                                                              }
                                                                                              else {
                                                                                                std::string msg = mensaje_error_tipos($2->get_name(),$13->get_tipo()->get_name());
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

       | FUNCTION TYPE_VOID identificador '(' { current_scope = driver.tablaSimbolos.enterScope(); } 
                                            lparam  {  
                                                      TypeS* v = TypeVoid::Instance();
                                                      insertar_funcion(v,$3,$6,&driver,current_scope,yylloc); 
                                                      identacion += "  ";
                                                    } ')' '{' bloquedeclare listainstrucciones '}'
                                                                                                  { TypeS* tipo = new TypeFunction(TypeVoid::Instance(),$6->get_tipos());
                                                                                                    $$ = new Funcion(tipo,*$3,*$6,*$10,*$11,0);
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
                                            bloquedeclare listainstrucciones RETURN exp ';' '}' { $$ = new Funcion(); 
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



instruccion1: loopfor        { 
                             }
            | loopwhile      { 
                             }
            | selectorif     { 
                             };

listainstruccionesLoop: /* Vacio */                                {
                                                                       $$ = new ListaInstrucciones(); 
                                                                   }
                      | listainstruccionesLoop instruccionLoop ';' {
                                                                     ListaInstrucciones * result;
                                                                     if ( $1->get_tipo() == TypeError::Instance()
                                                                          || $2->get_tipo() == TypeError::Instance()){
                                                                        result = new ListaInstrucciones($2,$1); 
                                                                        result->tipo = TypeError::Instance();
                                                                     } 
                                                                     else {
                                                                        result = new ListaInstrucciones($2,$1); 
                                                                     }
                                                                     $$ = result;
                                                                   }
                      | listainstruccionesLoop instruccionLoop1    {
                                                                     ListaInstrucciones * result;
                                                                     if ( $1->get_tipo() == TypeError::Instance()
                                                                          || $2->get_tipo() == TypeError::Instance()){
                                                                         result = new ListaInstrucciones($2,$1); 
                                                                         result->tipo = TypeError::Instance();
                                                                     } 
                                                                     else {
                                                                         result = new ListaInstrucciones($2,$1); 
                                                                     }
                                                                     $$ = result;
                                                                   } 

instruccionLoop: asignacion     { 
                                }
               | llamadafuncion     { 
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
                                                     } 
                                                     else {
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
                                                     } 
                                                     else {
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
                                                     } 
                                                     else {
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
                                                     } 
                                                     else {
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
                                           };


instruccionLoop1: loopfor        { 
                                 }
                | loopwhile      { 
                                 }
                | selectorifLoop { 
                                 };



asignacion: expID ASSIGN exp   {
                                 if ($1->get_tipo() == TypeError::Instance() ||
                                     $3->get_tipo() == TypeError::Instance() /*||
                                     $1->get_tipo() != $3->get_tipo()*/){
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
                                 } /*else if ( $1->get_tipo() != 0 || $1->get_tipo()->is_array() && $3->get_tipo()->is_array()) {
                                    TypeArray* arr1 = (TypeArray*) $1->get_tipo();
                                    TypeArray* arr2 = (TypeArray*) $3->get_tipo();
                                    std::cout << "\n\nAQUI\n\n";
                                    if (arr1->get_tipo() == arr2->get_tipo() &&
                                        arr1->get_dimensiones().first &&
                                        arr2->get_dimensiones().second) {
                                    }
                                 }*/ else {
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

loopfor: FOR '(' identificador ';' expBool ';' errorloopfor ')' '{' { 
                                                                      variable_no_declarada($3->identificador,&driver,yylloc, tabla_actual.front()); 
                                                                      driver.tablaSimbolos.enterScope();   
                                                                      identacion += "  "; 
                                                                    }
                                
                                bloquedeclare listainstruccionesLoop '}' {  ErrorLoopFor* asign_exp = $7;
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
                        bloquedeclare listainstruccionesLoop '}' { 
                                                                   $$ = new LoopFor();
                                                                 }
       | FOR '(' identificador ';' error  ';' errorloopfor ')' '{' { 
                                                                     variable_no_declarada($3->identificador,&driver,yylloc, tabla_actual.front());
                                                                   }
                                bloquedeclare listainstruccionesLoop '}' { 
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
                  bloquedeclare listainstruccionesLoop '}' { 
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
           bloquedeclare listainstruccionesLoop '}' WHILE '(' errorloopwhile ')' { 
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

selectorifLoop: IF '(' errorif ')' THEN '{' { 
                                              driver.tablaSimbolos.enterScope();   
                                              identacion += "  ";
                                            }
                    bloquedeclare listainstruccionesLoop '}' lelseifLoop {
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
              | IF '(' errorif ')' THEN instruccionLoop ';'              { 
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
              | IF '(' errorif ')' THEN instruccion ELSE instruccionLoop ';'    {
                                                                                  ErrorBoolExp* err_exp = $3;
                                                                                  SelectorIf * result;
                                                                                  if (err_exp->get_error()
                                                                                     || err_exp->get_tipo() == TypeError::Instance()
                                                                                      || $6->get_tipo() == TypeError::Instance()
                                                                                      || $8->get_tipo() == TypeError::Instance()
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

lelseifLoop: /* Vacio */                                                { 
                                                                      $$ = new LElseIf(false);
                                                                    }
       | lelseifLoop1 ELSE '{' { 
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
        | lelseifLoop1                                              { };
 

lelseifLoop1: ELSE IF '(' errorif ')' THEN '{' { 
                                             driver.tablaSimbolos.enterScope();   
                                            }
                            bloquedeclare listainstrucciones '}' {
                                                                   LElseIf* result; 
                                                                   if ( $4->get_error()
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
        | lelseifLoop1 ELSE IF '(' errorif ')' THEN '{' { 
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
                            TypeS* tipo = tmp->get_tipo();
                            $$ = tmp; 
                          };

/*Funciona. Faltan ejemplos mas interesantes.*/

larreglo: larreglo ',' exp      { 
                                  if ($1->get_tipo() != $3->get_tipo()
                                     || $1->get_tipo() == TypeError::Instance()
                                     || $3->get_tipo() == TypeError::Instance()){
                                        std::string msg;
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
