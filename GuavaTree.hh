/*
 * =====================================================================================
 *
 *       Filename:  GuavaTree.hh
 *
 *    Description:  Clases para la construccion de arbol.
 *
 *        Version:  1.0
 *        Created:  07/03/14 23:14:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas (), Michael Woo 
 *   Organization:  USB
 *
 * =====================================================================================
 */

# include "GuavaSymTable.hh"
# include <list>
# include <utility>
#include <iostream>

/**
 * Clase que define las expresiones del lenguaje.
 */
class Exp{
public:
    virtual TypeS* get_tipo() { return 0; }; 
    virtual void show(std::string) = 0;
};

/**
 * Clase que define los identificadores de variables del lenguaje.
 */
class Identificador:public Exp{
public:
    std::string identificador;
    int line;
    int column;
    TypeS* tipo;
    
    TypeS* get_tipo() { return tipo; }; 
    Identificador();
    Identificador(std::string s, TypeS* t = 0): identificador(s), tipo(t){
    }
    ~Identificador();
    
    virtual void show(std::string);
};

/**
 * Describe los tipos de datos del lenguaje.
 */
class Tipo{
public:
    std::string tipo;
    TypeS* tipoS;
    
    Tipo();
    Tipo(std::string,TypeS* t = 0);   
    ~Tipo();
    
    virtual void show(std::string);
};


/**
 * Define la estructuracion de los arreglos de datos en el lenguaje.
 */
class LArreglo{
    public:
        std::list<Exp*> larr;
        TypeS* tipo;

        LArreglo();
        void append(Exp*);
        ~LArreglo();
        int size(){ return larr.size(); }
        TypeS* get_tipo() { return tipo; 
                          }

        void show(std::string);
};


/**
 * Describe valores constantes del lenguaje.
 */

/*Si valor tendra de componente Tipo, no basta con tener un solo constructor
 *que enlace el token con el tipo determinado?
 */
class Valor:public Exp{
    public:


        virtual TypeS* get_tipo() { return 0; }
        virtual bool is_real() { return false; }
        virtual bool is_int() { return false; }
        virtual bool is_char() { return false; }
        virtual bool is_str() { return false; }
        virtual bool is_array() { return false; }
        virtual bool is_bool() { return false; }

        virtual void show(std::string) = 0;
};

/**
 * Clase que define los numeros reales dentro del lenguaje.
 */
class Real: public Valor{
    public:
        TypeS* tipo; 
        float valor;

        bool is_real() { return true; }
        Real(float valor_, TypeS* tipo_): tipo(tipo_), valor(valor_){
        }
        float get_valor() { return valor; };
        TypeS* get_tipo() { return tipo; }
        ~Real(){
        }

        void show(std::string s){
            std::cout << s << "Valor Real: ";
            std::cout << valor;
            std::cout << std::endl;
        }
};

/**
 * Clase que define los numeros enteros dentro del lenguaje.
 */
class Integer:public Valor{
    public:
        int valor;
        TypeS* tipo;
        bool is_int() { return true; }
        Integer(int valor_ , TypeS* tipo_ ): valor(valor_), tipo(tipo_) {}   
        int getValor() {return valor;}
        TypeS* get_tipo() { return tipo; }
        ~Integer(){}
        void show(std::string s ){
            std::cout << s << "Valor Real: ";
            std::cout << valor;
            std::cout << std::endl;
        }
};

/**
 * Clase que define los caracteres del lenguaje.
 */
class Char: public Valor{
    public:
        char valor;
        TypeS* tipo;

        bool is_char() { return true; }
        Char(char valor_ , TypeS* tipo_): valor(valor_), tipo(tipo_) {}
        char get_valor() { return valor; } 
        ~Char(){}
        TypeS* get_tipo() { return tipo; }

        void show(std::string s){
            std::cout << s << "Caracter: ";
            std::cout << valor;
            std::cout << std::endl;
        }
};

/**
 * Clase que define las cadenas de caracteres del lenguaje.
 */
class String: public Valor{
    public:
        std::string* valor;
        TypeS* tipo;

        bool is_str() { return true; }
        String(char* valor_ , TypeS* tipo_): valor( new std::string(valor_)), tipo(tipo_) {}
        String(std::string* valor_ , TypeS* tipo_): valor(valor_), tipo(tipo_) {}
        std::string* get_valor(){ return valor; } 
        TypeS* get_tipo() { return tipo; }
        ~String(){}

        void show(std::string s){
            std::cout << s << "Cadena de Caracteres: ";
            std::cout << *valor;
            std::cout << std::endl;
        }
};

/**
 * Clase que define el tipo de datos booleanos.
 */
class Bool: public Valor{
    public:
        bool valor;
        TypeS* tipo;

        bool is_bool() { return false; }

        Bool(bool valor_, TypeS* tipo_ ): valor(valor_), tipo(tipo_) {}  
        bool  get_valor() { return valor; }
        TypeS* get_tipo() { return tipo; }
        ~Bool();

        void show(std::string s){
            std::cout << s << "Booleano: ";
            std::cout << valor;
            std::cout << std::endl;
        }
};

/**
 * Clase que define la estructura de un arreglo, indicando sus dimensiones.
 */
class LCorchetes{
    public:
        TypeS* tipo;
        std::list<int> lista;
        LCorchetes(){
            tipo = 0;
        }
        LCorchetes(bool);
        void append(int);
        ~LCorchetes();

        void show(std::string);
};

/**
 * Clase que define la estructura de acceso a elementos de un arreglo.
 */
class LCorchetesExp{
public:
        TypeS* tipo;
        std::list<Exp*> lista;

        LCorchetesExp();
        ~LCorchetesExp();
        TypeS* get_tipo() { return tipo; }
        void append(Exp* e){
            lista.push_front(e);
        }
        void show(std::string s){
            std::cout << "Lista de Expresiones de Corchetes: \n";
            for (std::list<Exp*>::iterator it = lista.begin();
                 it != lista.end();
                 ++it){
                    Exp * tmp = *it;
                    tmp->show(s+ "  ");
                 }
        }
};

/**
 * Define las expresiones unarias del lenguajes.
 */
class ExpUn:public Exp{
    public:
        Exp* exp;
        TypeS* tipo;
        LCorchetes* corchetes;
        std::string *operacion;

        ExpUn(Exp*, std::string*);
        ExpUn(Exp*, LCorchetes*);    
        ~ExpUn();
        TypeS* get_tipo() { return tipo; }

        virtual void show(std::string);
};

/**
 * Define las expresiones binarias del lenguaje.
 */
class ExpBin: public Exp{
    public:
        TypeS* tipo;
        Exp* exp1;
        Exp* exp2;
        std::string operacion;
        ExpBin(); 
        ExpBin(Exp*,Exp*,std::string);
        ~ExpBin();
        TypeS* get_tipo() { return tipo; }

        virtual void show(std::string);
};

/**
 * Clase principal de instruccion.
 */
class Instruccion{
    public:
        virtual TypeS* get_tipo() {return TypeVoid::Instance();} 
        virtual void show(std::string) = 0;
};

class Error: public Instruccion{
public:
    TypeS* get_tipo() { return TypeError::Instance(); }
    void show(std::string){
    
    }
};

/**
 * Describe una lista de instrucciones del lenguaje definidas dentro de bloques
 * de codigo.
 */
class ListaInstrucciones{
    public:
        TypeS* tipo;
        Instruccion* instruccion;
        ListaInstrucciones* listainstrucciones;

        ListaInstrucciones();
        ListaInstrucciones(Instruccion*, ListaInstrucciones*);    
        ~ListaInstrucciones();
        TypeS* get_tipo() { return tipo; }
        void show(std::string);
};

/**
 * Clase que describe una lista de identificadores de estructuras de datos
 * de tipo arreglo.
 */
class LVarArreglo{
    public:
        std::list<std::pair <Identificador, LCorchetes> > lista;

        LVarArreglo();
        LVarArreglo(Identificador, LCorchetes);
        void append(Identificador,LCorchetes);
        std::list<std::pair <Identificador, LCorchetes> > get_list();
        ~LVarArreglo();

        void show(std::string);
};

/**
 * Clase que describe una lista de identificadores.
 */
class LVar{
    public:
        std::list<Identificador> lista; 
        LVar();
        LVar(std::list<Identificador>);
        void append(Identificador);
        ~LVar();
        std::list<Identificador> get_list();

        void show(std::string);
};

/**
 * Clase pariente de las estructuras de datos Record y Union.
 */
class Estructura{
    public:
        virtual Identificador get_id() = 0;
        virtual void show(std::string) = 0;
};

/**
 * Clase que define una lista de variables a ser declaradas.
 * No se si sea bueno, o se vea bien, colocar todos los tipos de clases que
 * puede tener LVariables dependiendo de lo que se este declarando. Si no
 * entiendes preguntame para que te lo explique mejor.
 */
class LVariables {
    public:
        TypeS* tipo;                   /*Tipo de las variables a declarar */

        LVar* listaIds;           /* Lista de identificadores de variables */
        LVarArreglo* listaIdsAr;  /* Lista de identificadores de variables de tipo arreglo */
        Estructura* estructura;   /* Este define a una union o registro. */
        LVariables* listaVar;     /* En caso de declarar mas de una lista de variables. */

        /*Constructores*/
        LVariables();

        /*Caso en el que se declaran variables simples*/
        LVariables(TypeS*, LVar*);

        /*Caso en el que se declaran variables de tipo arreglo*/
        LVariables(TypeS*, LVarArreglo*);

        /*Caso definicion de Records y Unions*/
        LVariables(Estructura*);

        ~LVariables();

        std::list<TypeS*> get_type_list();

        void show(std::string);
};

/**
 * Clase que define un record: Estructura de datos en la que se agrupan
 * diferentes elementos o variables. Cada elemento del record es guardado
 * en una direccion de memoria diferente.
 */
class Record:public Estructura{
    public:
        Record();
        Record(Identificador, LVariables*);
        ~Record();    
        LVariables* get_lvar();
        Identificador get_id();
        void show(std::string);
    private:
        Identificador id;              /* Nombre del record. */
        LVariables* lista;             /* Lista de variables. */
};

/**
 * Clase que define una union: Estructura de datos en la que todos sus
 * elementos comparten la misma direccion de memoria para ser almacenados.
 */
class Union:public Estructura{
    public:
        Union();
        Union(Identificador, LVariables*);
        ~Union();   
        LVariables* get_lvar();
        Identificador get_id();
        void show(std::string);
    private:
        Identificador id;   /* Nombre del union. */
        LVariables* lista;  /* Lista de variables. */
};


/**
 * Clase que describe la definicion de estructuras de datos tipo arreglos.
 */
class Arreglo:public Valor{
    public:
        LArreglo* la;
        TypeS* tipo;

        bool is_array() { return true; }
        Arreglo();
        Arreglo(LArreglo*);    
        ~Arreglo();
        TypeS* get_tipo(){ 
            return tipo;
        }

        void show(std::string s);
};

/**
 * Clase de bloque de declaraciones.
 */
class BloqueDeclare {
public:
    int scope;
    
    BloqueDeclare();
    BloqueDeclare(int);    
    ~BloqueDeclare();
    
    void show(std::string);
};

/**
 * Clase necesaria para establecer varias clausulas de condicionales else
 * en un bloque de instrucciones condicionados por IF.
 */
class LElseIf{
public:
    TypeS* tipo;
    Exp* exp;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    LElseIf* lelseif;

    LElseIf(bool);
    LElseIf(Exp* e, BloqueDeclare* bd, ListaInstrucciones* li){
        exp = e;
        listainstrucciones = li;
        tipo = TypeVoid::Instance();
        lelseif = 0;
    }
    LElseIf(Exp*, BloqueDeclare*, ListaInstrucciones*, LElseIf*);
    LElseIf(BloqueDeclare*, ListaInstrucciones*);
    ~LElseIf();
    TypeS* get_tipo(){return tipo;}

    void show(std::string);
};

/**
 * Clase que define los bloques de codigo sujestos a condiciones para su
 * ejecucion, bloques dentro de instrucciones de clausulas IF THEN ELSE.
 */
class SelectorIf: public Instruccion{
public:
    TypeS* tipo;
    Exp* exp;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    Instruccion* instruccion1; 
    Instruccion* instruccion2;
    LElseIf* lelseif;

    SelectorIf(): tipo(TypeError::Instance()), exp(0), declaraciones(0), listainstrucciones(0),instruccion1(0),instruccion2(0),lelseif(0){} 
    SelectorIf(Exp*, BloqueDeclare*, ListaInstrucciones*, LElseIf*);
    SelectorIf(Exp*, Instruccion*, Instruccion*);    
    ~SelectorIf(); 
    TypeS* get_tipo() { return tipo; } 
    
    void show(std::string);
};

class ErrorBoolExp{
bool error;
public:
    Exp* exp;
    ErrorBoolExp(Exp* e): exp(e), error(false) { }
    ErrorBoolExp(): error(true), exp(0){}
    ~ErrorBoolExp() { delete this; }
    TypeS* get_tipo(){
        if (exp!= 0) return exp->get_tipo();
        return 0;
    }
    bool get_error(){ return error; }

};

/**
 * Clase que define los bloques de instrucciones con iteracion indeterminada.
 */
class LoopWhile: public Instruccion{
public:
    Exp* exp;
    TypeS* tipo;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    LoopWhile(): exp(0), tipo(TypeError::Instance()), declaraciones(0), listainstrucciones(0){}
    LoopWhile(Exp*, BloqueDeclare*, ListaInstrucciones*);
    TypeS* get_tipo() { return tipo; } 
    ~LoopWhile();

    void show(std::string);
};

/**
 * Clase que define las asignaciones de expresiones a variables del
 * lenguaje.
 */
class Asignacion: public Instruccion{
public:
    TypeS* tipo;
    Exp* id;
    Exp* exp;

    Asignacion();
    Asignacion(Exp*, Exp*);
    ~Asignacion();
    TypeS* get_tipo() { return tipo; } 

    void show(std::string);
};

/**
 * clase que guarda la asignacion, exp
 * o si alguna de esta tiene un error.
 */
class ErrorLoopFor{
    bool error;
public:
    Asignacion* asign;
    Exp* exp;
    ErrorLoopFor(): error(true){}
    ErrorLoopFor(Asignacion* a): asign (a), exp(0){}
    ErrorLoopFor(Exp* e): exp(e), asign(0){}
    ~ErrorLoopFor(){
        delete this;
    }
    bool is_error(){ return error; }
    TypeS* get_tipo(){ 
        if (error){
            return 0;                
        } else {
            if (asign != 0) return asign->get_tipo();
            return exp->get_tipo();
        }
    }
};

/**
 * Clase que describe los bloques de instrucciones con iteraciones acotadas.
 */
class LoopFor: public Instruccion{
public:
    Identificador* identificador;
    TypeS* tipo;
    Exp* exp;
    Asignacion* asignacion;
    Exp* exp2;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;

    LoopFor():identificador(0), tipo (TypeError::Instance()), exp (0), asignacion(0), exp2(0), declaraciones(0),listainstrucciones(0){}
    LoopFor(Identificador*, Exp*, Exp*, BloqueDeclare*, ListaInstrucciones*);
    LoopFor(Identificador*, Exp*, Asignacion*, BloqueDeclare*, ListaInstrucciones*);
    ~LoopFor();  
    TypeS* get_tipo() { return tipo; } 
    
    void show(std::string);
};

/**
 * Clase para los incrementos y decrementos (prefijos y postfijos)
 */
class PlusMinus: public Instruccion{
public:
    Identificador* identificador;
    int tipo_inst; /* 0 para el dremento prefijo.
                    * 1 para el decremento postfijo.
                    * 2 para el incremento prefijo.
                    * 3 para el incremento prostfijo. */
    TypeS* tipo;
    
    PlusMinus():identificador(0),tipo_inst(-1),tipo(TypeError::Instance()){}
    PlusMinus(Identificador*, int);
    ~PlusMinus();
    TypeS* get_tipo(){ return tipo; }
    
    void show(std::string);
};

/**
 * Clase de lista de valores o variables, argumento de funciones e
 * instruccions print y read.
 */
class LVaroValor{
public:
    TypeS* tipo;
    std::list<Exp*> lvarovalor;
    LVaroValor(bool);
    void append(Exp* e);
    ~LVaroValor();        
    
    void show(std::string);
};

/**
 * Clase de entrada y salida estandar (Instrucciones print y read)
 */
class EntradaSalida: public Instruccion {
public:
    int tipo; /*0 para entrada: read; 1 para salida: print*/
    Exp* argumento;

    EntradaSalida(int, Exp*);
    TypeS* get_tipo(){
        TypeS* error = (TypeS*) TypeError::Instance();
        if (argumento->get_tipo() ==  error ) return TypeError::Instance();
        return TypeVoid::Instance();
    }
    ~EntradaSalida();

    void show(std::string);
};

/**
 * Clase de llamada funcion.
 */

class LlamadaFuncion: public Exp, public Instruccion{
public:
    TypeS* tipo;
    Identificador* id; /* Identificador de la funcion */
    LVaroValor* lvarovalor;     /* Lista de variables o valores. */

    LlamadaFuncion(Identificador*, LVaroValor*);
    LlamadaFuncion(): tipo(TypeError::Instance()), id(0),lvarovalor(0) {}
    ~LlamadaFuncion();
    TypeS* get_tipo(){ return tipo; }
    
    void show(std::string);
};

/**
 * Clase que determina las instrucciones Continue/Break.
 */
class ContinueBreak: public Instruccion{
public:
    TypeS* tipo;
    int instruccion; // 0 es Continue , 1 es break
    ContinueBreak( int t): instruccion(t), tipo(TypeVoid::Instance()){ }
    ~ContinueBreak(){ }
    void show(std::string s){
        if (instruccion == 0){
            std::cout << s << "Continue \n";
        } else{
            std::cout << s << "Break \n";
        }
    }
    TypeS* get_tipo() { return tipo; }
};

/**
 * Clase para lista de parametros.
 */
class LParam{
public:
    std::list<std::pair<TypeS*, Identificador*>> lParam;
    std::list<TypeS*> lTipos;

    LParam();
    void append(TypeS*, Identificador*);
    void appendTipo(TypeS*);
    std::list<std::pair<TypeS*,Identificador*> > get_list();
    std::list<TypeS*> get_tipos();
    ~LParam();
    
    void show(std::string);
};

/**
 * Clase Funcion
 */
class Funcion{
public:
    TypeS* tipo;
    Identificador identificador;
    LParam parametros; 
    BloqueDeclare declaraciones;
    ListaInstrucciones listaI;
    Exp* retorno;

    Funcion();
    Funcion(TypeS*, Identificador, LParam, BloqueDeclare ,ListaInstrucciones, Exp*);    
    ~Funcion();

    void show(std::string);
};

/**
 * Clase para la lista de funciones.
 */
class LFunciones{
public:
    Funcion* funcion;   /* Funcion */
    LFunciones* lista; /* Lista de funciones */
    
    LFunciones();
    LFunciones(Funcion*, LFunciones*);
    ~LFunciones();
    
    void show(std::string);
};

/**
 * Clase de bloque principal.
 */
class BloquePrincipal {
public:
    BloqueDeclare* globalD; /* Declaraciones globales. */
    LFunciones* funciones;  /* Lista de funciones. */

    BloquePrincipal();
    BloquePrincipal(BloqueDeclare*, LFunciones*);
    ~BloquePrincipal();

    void show(std::string);
};

/**
 * Clase que define el simbolo inicial de la gramatica que describe la
 * estructura de un programa en Guava.
 */
class Program{
public:
    BloquePrincipal bloque;
    Program();
    ~Program();
    Program(BloquePrincipal);

    virtual void show(std::string);
}; 
/**
 * Clase para hacer la revision de LAccesoAtributos.
 */
class LAccesoAtributos{
    std::list<Identificador*> lista;  
public:
    LAccesoAtributos(){}

    LAccesoAtributos(Identificador* i){
        lista.push_front(i);
    }

    ~LAccesoAtributos(){}

    void append(Identificador* i){
        lista.push_front(i);
    }
    
    std::list<Identificador*> get_list(){
        return lista;
    }
    void show(std::string s){
        for ( std::list<Identificador*>::iterator it = lista.begin();
              it != lista.end();
              ++it
            ){
                std::cout << s << "Lista de Acceso Atributos: ";
                Identificador* id = *it;
                id->show(s+ "  ");
            }
    }
};

/**
 * Clase para las expresiones de identificador.
 */
class ExpID: public Exp{
public:
    TypeS* tipo;
    Identificador* identificador;
    LCorchetesExp* lcorchetesexp;  
    LAccesoAtributos* laccesoatributos;

    ExpID():tipo(TypeError::Instance()), identificador(0), lcorchetesexp(0), laccesoatributos(0){}
    ExpID(Identificador* id): identificador(id), lcorchetesexp(0),laccesoatributos(0){}
    ExpID(Identificador* id, LCorchetesExp* lce ): identificador(id), lcorchetesexp(lce), laccesoatributos(0){}
    ExpID(Identificador* id, LAccesoAtributos* la ): identificador(id), laccesoatributos(la),lcorchetesexp(0){}

    TypeS* get_tipo(){ return tipo; }

    void show(std::string s){
        if (identificador != 0) identificador->show(s);
        if (lcorchetesexp != 0) lcorchetesexp->show(s);
        if (laccesoatributos != 0) laccesoatributos->show(s);
    }
};
