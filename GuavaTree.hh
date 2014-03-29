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
 *         Author:  Ruben Serradas (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */

/**
 * PARTE DE OBSERVACIONES:
 * 1- Para la regla de lvariables: tipo no puede ser void, no puede existir
 *    una variable que sea de tipo void.
 * 2- Para la regla de lcorchetes: Esta regla es para la declaracion de
 *    arreglos, estamos permitiendo que entre corchetes pueda existir una
 *    exp, solo puede ser una expresion si esta retorna un valor integer.
 *    Lo dejaremos asi y lo verificamos en la verificacion estatica de tipos?
 *    O lo cambiaremos a solo expresiones de tipo integer?
 * 3- Me tienes que explicar la regla de arreglo y larreglo.
 * 4- Podemos considerar las uniones y records como tipo o son los IDs de
 *    cada uno los que definen el nombre del tipo?
 * 5- Se debe definir de abajo hacia arriba, sino la compilacion no funcionara.
 *
 */

#include "GuavaSymTable.hh"
#include <list>
#include <utility>
/**
 * Clase que define las expresiones del lenguaje.
 */
class Exp{
public:
    Exp* exp;
    
    Exp();
    Exp(Exp*);
    ~Exp();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Describe las expresiones parentizadas.
 */
class ExpParentizada: public Exp{
public:
    Exp exp;

    ExpParentizada(Exp);    
    ~ExpParentizada();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define los identificadores de variables del lenguaje.
 */
class Identificador:public Exp{
public:
    std::string identificador;
    
    Identificador();
    Identificador(std::string); 
    ~Identificador();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Describe los tipos de datos del lenguaje.
 */
class Tipo{
public:
    std::string tipo;
    
    Tipo();
    Tipo(std::string);   
    ~Tipo();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Describe valores constantes del lenguaje.
 */
class Valor: public Exp{
public:
    Valor* valor;

    Valor(Valor*);
    Valor();
    ~Valor();

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define los numeros reales dentro del lenguaje.
 */
class Real: public Valor{
public:
    float real;
    
    Real(float);    
    ~Real();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define los numeros enteros dentro del lenguaje.
 */
class Integer:public Valor{
public:
    int integer;
    Integer();
    Integer(int);    
    ~Integer();
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define los caracteres del lenguaje.
 */
class Char: public Valor{
public:
    char ch;
    
    Char(char);
    ~Char();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define las cadenas de caracteres del lenguaje.
 */
class String: public Valor{
public:
    std::string str;

    String(char*);    
    String(std::string);    
    ~String();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define el tipo de datos booleanos.
 */
class Bool: public Valor{
public:
    bool b;
    
    Bool(bool);    
    ~Bool();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define la estructura de un arreglo, indicando sus dimensiones.
 */
class LCorchetes{
public:
    std::list<Integer> lista;
        
    LCorchetes();
    void append(Integer);
    ~LCorchetes();
        
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Define las expresiones unarias del lenguajes.
 */
class ExpUn:public Exp{
public:
    Exp exp;
    LCorchetes* corchetes;
    std::string* operacion;
    
    ExpUn(Exp, std::string*);
    ExpUn(Exp, LCorchetes*);    
    ~ExpUn();

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Define las expresiones binarias del lenguaje.
 */
class ExpBin: public Exp{
public:
    Exp exp1,exp2;
    std::string operacion;
    ExpBin(); 
    ExpBin(Exp,Exp,std::string);
    ~ExpBin();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase principal de instruccion.
 */
class Instruccion{
public:
    Instruccion* instruccion;
    
    Instruccion();
    Instruccion(Instruccion*);
    ~Instruccion();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Describe una lista de instrucciones del lenguaje definidas dentro de bloques
 * de codigo.
 */
class ListaInstrucciones{
public:
    Instruccion* instruccion;
    ListaInstrucciones* listainstrucciones;
    
    ListaInstrucciones();
    ListaInstrucciones(Instruccion*, ListaInstrucciones*);    
    ~ListaInstrucciones();
    
    void show(std::string);
    void verificar(GuavaSymTable);
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
    void verificar(GuavaSymTable);
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
    void verificar(GuavaSymTable);
};

/**
 * Clase pariente de las estructuras de datos Record y Union.
 */
class Estructura{
public:
    Estructura* estructura;
    
    Estructura();
    Estructura(Estructura*);
    ~Estructura();
    
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase que define una lista de variables a ser declaradas.
 * No se si sea bueno, o se vea bien, colocar todos los tipos de clases que
 * puede tener LVariables dependiendo de lo que se este declarando. Si no
 * entiendes preguntame para que te lo explique mejor.
 */
class LVariables {
public:
    Tipo t;                 /*Tipo de las variables a declarar */
    int modo;               /*Modo de pasaje de la variable: Por referencia=1, por valor=0*/

    LVar listaIds;          /* Lista de identificadores de variables */
    LVarArreglo listaIdsAr; /* Lista de identificadores de variables de tipo arreglo */
    Estructura estructura;  /* Este define a una union o registro. */
    LVariables* listaVar;    /* En caso de declarar mas de una lista de variables. */

    /*Constructores*/
    LVariables();

    /*Caso en el que se declaran variables simples*/
    LVariables(Tipo, LVar, LVariables *);

    /*Caso en el que se declaran variables de tipo arreglo*/
    LVariables(Tipo, LVarArreglo, LVariables *);

    /*Para el caso en que se declaran uniones y records, simplemente no se
     *podria poner que el Tipo t = Union o Record o el ID de la estructura?
     *VER OBSERVACION 4
     */
    
    /*Caso definicion de Records y Unions*/
    LVariables(Estructura, LVariables *);

    ~LVariables();
    
    void show(std::string);
    /*Investigar: Como realizar la verificacion si los tipos de listas de
     *            variables son diferentes? No es como python que por ser
     *            debilmente tipado una misma verificacion servia para todo.
     */
    void verificar(GuavaSymTable);
};

/**
 * Clase que define un record: Estructura de datos en la que se agrupan
 * diferentes elementos o variables. Cada elemento del record es guardado
 * en una direccion de memoria diferente.
 */
class Record:public Estructura{
public:
    Identificador id;     /* Nombre del record. */
    LVariables* lista;             /* Lista de variables. */
    
    Record();
    Record(Identificador, LVariables*);
    ~Record();    
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que define una union: Estructura de datos en la que todos sus
 * elementos comparten la misma direccion de memoria para ser almacenados.
 */
class Union:public Estructura{
public:
    Identificador id;   /* Nombre del union. */
    LVariables* lista;  /* Lista de variables. */
    
    Union();
    Union(Identificador, LVariables*);
    ~Union();   

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Define la estructuracion de los arreglos de datos en el lenguaje.
 */
class LArreglo{
public:
    std::list<Exp> larr;

    LArreglo();
    void append(Exp);
    ~LArreglo();
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que describe la definicion de estructuras de datos tipo arreglos.
 */
class Arreglo:public Valor{
public:
    LArreglo* listaA;

    Arreglo();
    Arreglo(LArreglo*);    
    ~Arreglo();
    
    void show(std::string);
    void verificar(GuavaSymTable);
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
    void verificar(GuavaSymTable);
};

/**
 * Clase necesaria para establecer varias clausulas de condicionales else
 * en un bloque de instrucciones condicionados por IF.
 */
class LElseIf{
public:
    Exp* exp;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;
    LElseIf* lelseif;

    LElseIf();
    LElseIf(Exp, BloqueDeclare, ListaInstrucciones, LElseIf*);
    LElseIf(BloqueDeclare, ListaInstrucciones);
    ~LElseIf();

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que define los bloques de codigo sujestos a condiciones para su
 * ejecucion, bloques dentro de instrucciones de clausulas IF THEN ELSE.
 */
class SelectorIf: public Instruccion{
public:
    Exp exp;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    Instruccion* instruccion1; 
    Instruccion* instruccion2;
    LElseIf* lelseif;
    
    SelectorIf(Exp, BloqueDeclare*, ListaInstrucciones*, LElseIf*);
    SelectorIf(Exp, Instruccion*, Instruccion*);    
    ~SelectorIf(); 
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que define los bloques de instrucciones con iteracion indeterminada.
 */
class LoopWhile: public Instruccion{
public:
    Exp exp;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;

    LoopWhile(Exp, BloqueDeclare, ListaInstrucciones);
    ~LoopWhile();

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que define las asignaciones de expresiones a variables del
 * lenguaje.
 */
class Asignacion: public Instruccion{
public:
    Identificador identificador;
    Identificador* identificador2;
    LCorchetes* lcorchetes;
    Arreglo* arreglo;
    Exp* exp;

    Asignacion();
    Asignacion(Identificador, Exp);
    Asignacion(Identificador, LCorchetes, Exp);
    Asignacion(Identificador,Identificador,Exp);
    Asignacion(Identificador, Arreglo);
    ~Asignacion();

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que describe los bloques de instrucciones con iteraciones acotadas.
 */
class LoopFor: public Instruccion{
public:
    Identificador identificador;
    Exp exp;
    Asignacion* asignacion;
    Exp* exp2;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;

    LoopFor(Identificador, Exp, Exp, BloqueDeclare, ListaInstrucciones);
    LoopFor(Identificador, Exp, Asignacion, BloqueDeclare, ListaInstrucciones);
    ~LoopFor();  
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase para los incrementos y decrementos (prefijos y postfijos)
 */
class PlusMinus: public Instruccion{
public:
    Identificador identificador;
    int tipo; /* 0 para el dremento prefijo.
               * 1 para el decremento postfijo.
               * 2 para el incremento prefijo.
               * 3 para el incremento prostfijo. */
    
    PlusMinus(Identificador, int);
    ~PlusMinus();
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase de lista de valores o variables, argumento de funciones e
 * instruccions print y read.
 */
class LVaroValor{
public:
    std::list<Exp> lvarovalor;
    LVaroValor();
    void append(Exp e);
    ~LVaroValor();        
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase de entrada y salida estandar (Instrucciones print y read)
 */
class EntradaSalida: public Instruccion {
public:
    int tipo; /*0 para entrada: read; 1 para salida: print*/
    LVaroValor argumento;

    EntradaSalida(int, LVaroValor);
    ~EntradaSalida();

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase de llamada funcion.
 */

class LlamadaFuncion: public Instruccion{
public:
    Identificador id; /* Identificador de la funcion */
    LVaroValor lvarovalor;     /* Lista de variables o valores. */

    LlamadaFuncion(Identificador, LVaroValor);
    ~LlamadaFuncion();
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase para lista de parametros.
 */
class LParam{
public:
    std::list<std::pair<Tipo, Identificador> > lParam;

    LParam();
    void append(Tipo, Identificador);
    
    ~LParam();
    std::list<std::pair<Tipo,Identificador> > get_list();
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase Funcion
 */
class Funcion{
public:
    Tipo tipo;
    Identificador identificador;
    LParam parametros; 
    BloqueDeclare declaraciones;
    ListaInstrucciones listaI;
    Exp* retorno;

    Funcion();
    Funcion(Tipo, Identificador, LParam, BloqueDeclare ,ListaInstrucciones, Exp*);    
    ~Funcion();

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase para la lista de funciones.
 */
class LFunciones{
public:
    Funcion funcion;   /* Funcion */
    LFunciones* lista; /* Lista de funciones */
    
    LFunciones();
    LFunciones(Funcion, LFunciones*);
    ~LFunciones();
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase de bloque principal.
 */
class BloquePrincipal {
public:
    BloqueDeclare globalD; /* Declaraciones globales. */
    LFunciones funciones;  /* Lista de funciones. */

    BloquePrincipal();
    BloquePrincipal(BloqueDeclare, LFunciones);
    ~BloquePrincipal();

    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase que define el simbolo inicial de la gramatica que describe la
 * estructura de un programa en Guava.
 */
class Program{
public:
    BloquePrincipal bloque;
    
    Program();
    Program(BloquePrincipal);
    ~Program();

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
}; 

