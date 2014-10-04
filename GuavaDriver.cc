/*
 * =====================================================================================
 *
 *       Filename:  GuavaDriver.cc
 *
 *    Description:  Manejador de parser.
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo
 *
 * =====================================================================================
 */
#include "GuavaDriver.hh"
#include "GuavaParser.hh"


/* Variables Globales. */
int current_scope;
int attribute_scope;  
int declare_scope;
int error_state;
std::string identacion ("");
std::list<int> offset_actual;
std::list<GuavaSymTable*> tabla_actual;
int nombre_cadena  (1);
int secuencia_temporales (1);
SimpleSymbol* basepointer = new SimpleSymbol(std::string("bp"));


/**
 * Constructor de la clase GuavaDriver
 */
GuavaDriver::GuavaDriver ()
  : trace_scanning (false), trace_parsing (false)
{
    TypeS* integer = TypeInt::Instance();
    TypeS* real = TypeReal::Instance();
    TypeS* error = TypeError::Instance();
    TypeS* boolean = TypeBool::Instance();
    TypeS* character = TypeChar::Instance();
    TypeS* string = TypeString::Instance();
    TypeS* voidt = TypeVoid::Instance(); 
    
    tablaSimbolos = *(new GuavaSymTable());
    tablaSimbolos.insert_type(std::string("integer"),std::string("type"),0,integer);
    tablaSimbolos.insert_type(std::string("real"),std::string("type"),0,real);
    tablaSimbolos.insert_type(std::string("error"),std::string("type"),0,error);
    tablaSimbolos.insert_type(std::string("boolean"),std::string("type"),0,boolean);
    tablaSimbolos.insert_type(std::string("character"),std::string("type"),0,character);
    tablaSimbolos.insert_type(std::string("string"),std::string("type"),0,string);
    tablaSimbolos.insert_type(std::string("void"),std::string("type"),0,voidt);
}
/**
 * Destructor de la clase GuavaDriver 
 */
GuavaDriver::~GuavaDriver ()
{
}

/** 
 * Funcion que llama al parser.
 * @param std::string &f: Referencia a nombre del string a parsear. 
 * @return int res: Resultado del parseo.
 */
int GuavaDriver::parse (const std::string &f)
{
  file = f;
  gen = new Generator(file);
  scan_begin ();
  yy::GuavaParser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}
/**
 * Funcion que imprime un mensaje de error.
 * @param yy::location& l: Referencia al lugar del error.
 * @param std::string& m: Referencia a mensaje de error.
 */
void GuavaDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}
/**
 * Funcion que imprime un mensaje de error.
 * @param std::string& m: Referencia a mensaje de error.
 */
void GuavaDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

/* Funciones Auxiliares. */

/**
 * Funcion que obtiene recursivamente el TypeS* de un
 * simbolo id.
 */ 
TypeS* obtener_tipo_simbolo(Symbol* id){
    if (id == 0) return 0;
    if (id->true_type != 0) return id->true_type;
    if (id->type_pointer != 0) return obtener_tipo_simbolo(id->type_pointer);
    return 0;
}

/**
 * Retorna un mensaje de error para la impresion y
 * pone error_state en 1
 */
std::string mensaje_estructura_error(std::string nombre){
    std::string msg2 ("The variable '");
    msg2 += nombre+"' is not a record nor an union.";
    error_state = 1;
    return msg2;
}

/**
 * Indica si una categoria es igual a unionVar
 * o recordVar
 */
bool es_estructura(std::string categoria){
    return ((categoria.compare("unionVar") == 0) || categoria.compare("recordVar") == 0);
}

/**
 * Verifica que una funcion que debe retornar algo
 * retorne algo.
 */
void funcion_sin_return(Identificador* fname,GuavaDriver* driver,const yy::location & loc){
    std::string msg ("The function ");
    msg += fname->identificador;
    msg += " doesn't return anything.";
    driver->error(loc,msg);
    error_state = 1;
}
/**
 * Verifica que todos los returns tengan el tipo correcto.
 * Incompleto.
 */
bool verificar_return(Identificador *fname, TypeS* tipo, std::list<Instruccion*> lista ,GuavaDriver* driver){
    bool result = true;
    std::ostringstream convert;
    for (std::list<Instruccion*>::iterator it = lista.begin(); it != lista.end(); ++it){
        Instruccion* tmp = *it;
        if (tmp->get_tipo() != tipo){
            std::string msg ("Returning ");
            msg += tmp->get_tipo()->get_name();
            msg += " instead of " + tipo->get_name();
            convert << tmp->get_line();
            msg += " at line " + convert.str() ;
            convert.flush();
            convert << tmp->get_column();
            msg += " ,column "+convert.str();
            driver->error(msg);
            error_state = 1;
            result = false;
        }
    }
    return result;
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
    msg += "' wasn't declared or doesn't exists in current context.";
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
/**
 * Retorna un mensaje de error cuando los dos tipos son incompatibles.
 */
std::string mensaje_diff_operandos(std::string operador, std::string op1, std::string op2, std::string expected) {
    std::string msg ("Type error: cannot use operator: '");
    msg += operador+"' with types: '"+op1+"' and '"+op2+"', expected both: '"+expected+"'";
    return msg;
}

/**
 * Funcion que dado una instancia de la clase Tipo
 * y la tabla de simbolos retorna la direccion en donde esta el tipo.
 * DEPRECADA. La d nunca se usa.
 */
Symbol* obtener_tipo(std::string str, GuavaDriver *d, GuavaSymTable* t){
    Symbol *s = t->lookup(str);
    if (s == 0) return 0;
    if (s->true_type == 0) return 0;
    return s;
}

/**
 * Funcion que dado una instancia de la clase Tipo
 * y la tabla de simbolos retorna la direccion en donde esta el tipo.
 */
Symbol* obtener_tipo(std::string str, GuavaSymTable* t){
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
        int tam = t->get_dimensiones();
        result = 1;
        return (result * tam * encajar_en_palabra(tamano_tipo(t->get_tipo())) ); 
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
        s = tabla->simple_lookup(it->identificador);
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
    s = tabla->simple_lookup(identificador->identificador);
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
    std::list<int>::reverse_iterator itInt;
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

            itInt = par.second.lista.rbegin();
            size = *itInt;
            TypeArray* arr = 0;
            TypeArray* tmp = new TypeArray(t,0,size);

            for(itInt ; itInt != par.second.lista.rend(); ++itInt) {
                size = *itInt;
                arr = new TypeArray(t,tmp,size);
                tmp = arr;
            }
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
 * Funcion que calcula el tamaño de una cadena de caracteres.
 */
int tamano_cadena(std::string cadena){
   return encajar_en_palabra(cadena.size());
}

/**
 * Funcion que inserta una cadena de caracteres en la tabla de
 * simbolos.
 */
void insertar_cadena_caracteres(std::string cadena, GuavaDriver *d, const yy::location& loc){
    int scope, line, column;
    GuavaSymTable *tabla = tabla_actual.front();
    line = loc.begin.line;
    std::ostringstream convert;
    column = loc.begin.column;
    scope = tabla->currentScope();

    int offset = offset_actual.front();

    convert << nombre_cadena; // Variable global
    if (offset != -1){
        offset_actual.pop_front();
        tabla->insert(convert.str(),std::string("cadena"),scope,TypeString::Instance(),line,column,offset);
        offset += tamano_cadena(cadena); 
        offset_actual.push_front(offset);
    } else {
        tabla->insert(convert.str(),std::string("cadena"),scope,TypeString::Instance(),line,column,0);
    }
    nombre_cadena++;
}

/**
 * Funcion que coloca una variable temporal en la tabla de simbolos
 * y retorna esta misma.
 * @param d: Clase manejadora GuavaDriver
 * @param loc: location del yyparse
 * @param tipo: tipo del temp
 * @param tabla Tabla en la que se quiere buscar el tipo de la variable
 */
Symbol* newtemp(GuavaDriver *d, const yy::location& loc, TypeS* tipo, GuavaSymTable* tabla){
    int scope, line, column;
    line = loc.begin.line;
    std::ostringstream convert;
    column = loc.begin.column;
    scope = tabla->currentScope();
    if (tipo == 0) return 0;


    convert << secuencia_temporales;
    std::string nombre_t =  "_t" + convert.str(); //El nombre de las variables sera _tn, siendo n un numero unico.
    secuencia_temporales++;

    Symbol* nuevo;
    
    if (!tipo->is_array() && !tipo->is_structure()){
        Symbol *p= obtener_tipo(tipo->get_name(),tabla);
        if (p == 0) {
            return 0;
        }
        nuevo = new Symbol(nombre_t, std::string("temporal"),scope,p,line,column,0);
    } else{
        nuevo = new Symbol (nombre_t, std::string("temporal"),scope,tipo, line,column, 0);
    }
    return nuevo;
}


/**
 * Funcion que coloca una variable temporal en la tabla de simbolos
 * y retorna esta misma.
 * @param d: Clase manejadora GuavaDriver
 * @param loc: location del yyparse
 * @param tipo: tipo del temp
 */
Symbol* newtemp(GuavaDriver *d, const yy::location& loc, TypeS* tipo){
    int scope, line, column;
    GuavaSymTable *tabla = tabla_actual.front();
    line = loc.begin.line;
    std::ostringstream convert;
    column = loc.begin.column;
    scope = tabla->currentScope();
    if (tipo == 0) return 0;


    convert << secuencia_temporales;
    std::string nombre_t =  "_t" + convert.str(); //El nombre de las variables sera _tn, siendo n un numero unico.
    secuencia_temporales++;

    Symbol* nuevo;
    
    if (!tipo->is_array() && !tipo->is_structure()){
        Symbol *p= obtener_tipo(tipo->get_name(),tabla);
        if (p == 0) {
            return 0;
        }
        nuevo = new Symbol(nombre_t, std::string("temporal"),scope,p,line,column,0);
    } else{
        nuevo = new Symbol (nombre_t, std::string("temporal"),scope,tipo, line,column, 0);
    }
    return nuevo;
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
 * Funcion que retorna mensaje de tipo recursivo
 * @param t Tipo que se esta buscando
 * @return msg Mensaje final
 */
std::string reportar_tipo_recursivo(std::string t){
    std::string msg ("Cannot declare a variable of a undefined type ''");
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
        s = tabla->simple_lookup(it->identificador);
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
    std::list<int>::reverse_iterator itInt;
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
        s = tabla->simple_lookup(par.first.identificador);
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
            itInt = par.second.lista.rbegin();
            TypeArray* arr = 0;
            TypeArray* tmp = new TypeArray(reference0,0,size);
            
            for(itInt ; itInt != par.second.lista.rend(); ++itInt) {
                size = *itInt;
                arr = new TypeArray(reference0,tmp,size);
                tmp = arr;
            }
            
            scope = tabla->currentScope();
            line = par.first.line;
            column = par.first.column;
            int offset = offset_actual.front();
            if (offset != -1){
                offset_actual.pop_front();
                tabla->insert(par.first.identificador,std::string("array"),scope,arr,line,column, offset);
                offset += tamano_tipo(arr); 
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
 * @param tipo          Tipo que retorna la funcion
 * @param lp            Lista de parametros.
 * @param d             Clase manejadora GuavaDriver
 * @param current_scope Entorno actual
 * @param loc           Lugar actual de la funcion.
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
    Symbol *s = d->tablaSimbolos.lookup(id->identificador);
    //Se verifica la existencia de una funcion con el mismo nombre
    if (s != 0 && !s->sym_catg.compare("function")) {
        std::string msg("Function: '");
        msg += id->identificador;
        msg += "' has been already declared in the current context.";
        d->error(loc,msg);
    }
    else {
        tabla->insert_type(id->identificador,std::string("function"),0,function);
    }
}

/**
 * Dereferencia un TypeS* tipo Referencia.
 * Funciona como un & en C/C++
 * @param referencia Referencia a la cual hacerle dereferencia
 */
TypeS* dereference(TypeS* referencia){
    TypeS* tmp = referencia->get_tipo();
    return tmp;
}

/**
 * Verifica la existencia de un tipo y lo agrega a la tabla. 
 * @param identificador Identificador del tipo
 * @param d Manejador GuavaDriver
 * @param loc Lugar en donde se encuentra el parser en el momento de llamar a la funcion
 * @param is_union Variable booleana que nos dice si el tipo es union o no
 */
void verificar_existencia_tipo(Identificador* id, GuavaDriver* d,const yy::location& loc, bool is_union){
    TypeStructure *structure;
    if (is_union) {
        structure = new TypeUnion();
        offset_actual.push_front(-1);
        GuavaSymTable* tmp = structure->get_tabla();
        tmp->set_parent(structure);
    } else {
        structure = new TypeRecord();
        offset_actual.push_front(0);
        GuavaSymTable* tmp = structure->get_tabla();
        tmp->set_parent(structure);
    }
    structure->set_name(id->identificador);
    GuavaSymTable *tabla = tabla_actual.front();
    int n = tabla->currentScope();
    identacion += "  ";
    Symbol *tmp;
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

/**
 * Revisa si un identificador es una variable global y le da un
 * address
 */
void revision_scope_id(Symbol* id, ExpID* result, GuavaDriver* driver, const yy::location& loc, GuavaSymTable* tabla){
    if (id->scope == 1) { //El scope de las variables temporales es uno
        result->addr = id;
    } else {
        result->bp = (Symbol*) basepointer;
        result->addr = newtemp(driver,loc,result->get_tipo(),tabla);
    }
}


/**
 * Revisa si un identificador es una variable global y le da un
 * address
 */
void revision_scope_id(Symbol* id, ExpID* result, GuavaDriver* driver, const yy::location& loc){
    if (id->scope == 1) { //El scope de las variables temporales es uno
        result->addr = id;
    } else {
        result->bp = (Symbol*) basepointer;
        result->addr = newtemp(driver,loc,result->get_tipo());
    }
}


/**
 * Revisa si un identificador es una variable global y le da un
 * address
 */
void revision_scope_id(Symbol* id, Identificador* result, GuavaDriver* driver, const yy::location& loc){
    if (id->scope == 1) { //El scope de las variables temporales es uno
        result->addr = id;
    } else {
        result->bp = (Symbol*) basepointer;
        result->addr = newtemp(driver,loc,result->get_tipo());
    }
}

/**
 * Funcion que retorna el contenido del arreglo en cuanto al tipo.
 * @param tipo_arreglo Tipo del arreglo actual
 */
TypeS* contents(TypeS* tipo){
    if (tipo == 0 || !tipo->is_array()) return 0;

    TypeArray* tipo_arreglo = (TypeArray*) tipo;

    TypeArray* tmp = (TypeArray*) tipo_arreglo->get_tipoEstructura();
    if (tmp->is_array()){
        return tmp->get_tipoEstructura();
    }else{
        return tmp->get_tipo();
    }
}


/**
 * Obtencion de los quads para la clase ExpID
 * Esto hay que probarlo bastante.
 */
std::list<GuavaQuads*>* ExpID::generar_quads(){
    std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>; 
    std::ostringstream convert;
    Symbol* r;
    if (identificador == 0) return 0;

    // Me voy moviendo por la expresion hasta llegar a la 
    // "base" de esta
    if (exp_id != 0){
        if (tabla != 0){
            r = tabla->lookup(identificador->identificador);
            exp_id->offset_structure += r->offset;
        }
        result = exp_id->generar_quads(); 
    }

    //Caso en el que no es un arreglo
    if (lcorchetesexp == 0){
        //Caso en el que esta solo
        if (tabla == 0){
            if (bp != 0){
                //Caso en el que no es global
                convert << offset;
                SimpleSymbol* offset_ = new SimpleSymbol(convert.str());
                GuavaQuads* nuevo_q = new GuavaQuadsExp("[]",bp,offset_,addr);
                result->push_back(nuevo_q);
            }else{
                //Caso en el que es global
                GuavaQuads* nuevo_q = new GuavaQuadsExp(":=",identificador->addr,0,addr);
                result->push_back(nuevo_q);
            }
        } else {
            //Caso en el que no esta solo
            if (bp != 0){
                // Caso en el que no es global        
                Symbol* f = tabla->lookup(identificador->identificador);
                convert << (offset_structure + f->offset);
                SimpleSymbol* offset_ = new SimpleSymbol(convert.str());
                GuavaQuads* nuevo_q = new GuavaQuadsExp("[]",bp,offset_,addr);
                result->push_back(nuevo_q);
            } else {
                Symbol* f = tabla->lookup(identificador->identificador);
                convert << f->offset;
                SimpleSymbol* offset_ = new SimpleSymbol(convert.str());
                GuavaQuads* nuevo_q = new GuavaQuadsExp(":=",addr,offset_,addr);
                result->push_back(nuevo_q);
            }
        }
        return result;
    } else{
        //Caso arreglo
        TypeS* tipo = type_array;
        std::list<Exp*>::iterator it = lcorchetesexp->lista.begin();
        Exp *exp_ini = *it;
        ++it;
        convert << tamano_tipo(tipo);
        SimpleSymbol* width = new SimpleSymbol(convert.str());
        GuavaQuads* nuevo_q = new GuavaQuadsExp("*",exp_ini->addr,width, addr);
        result->push_back(nuevo_q);
        for (it; it != lcorchetesexp->lista.end(); ++it  ){
            tipo = contents(tipo);
            Symbol * t = temp->newtemp();
            Exp* exp_ = *it;
            convert.flush();
            convert << tamano_tipo(tipo);
            width = new SimpleSymbol(convert.str());
            GuavaQuads* nuevo_q1 = new GuavaQuadsExp("*",exp_->addr,width,t);
            GuavaQuads* nuevo_q2 = new GuavaQuadsExp("+",addr,t,array);
            result->push_back(nuevo_q1);
            result->push_back(nuevo_q2);
        }
        GuavaQuads* nuevo_q3;
        if (bp != 0){
            nuevo_q3 = new GuavaQuadsExp("[]",bp,array,addr);
        } else {
            nuevo_q3 = new GuavaQuadsExp("[]",identificador->addr,array, addr);
        }
        result->push_back(nuevo_q3);
        return result;
    }
    return 0;
}
