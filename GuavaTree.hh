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

class Exp{
public:
    Exp* exp;
    Exp();
    Exp(Exp*);
    ~Exp();
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class ExpParentizada: public Exp{
public:
    Exp exp;
    ExpParentizada(Exp);    
    ~ExpParentizada();
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Identificador:public Exp{
    public:
        std::string identificador;
        Identificador(std::string);    
        ~Identificador();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};


class Tipo{
    public:
        std::string tipo;
        Tipo();
        Tipo(std::string);   
        ~Tipo();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class Valor: public Exp{
    public:
        Valor* valor;

        Valor(Valor*);
        Valor();
        ~Valor();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class Real: public Valor{
    public:
        float real;
        Real(float f);    
        ~Real();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class Integer: public Valor{
    public:
        int integer;
        Integer(int i);    
        ~Integer();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class Char: public Valor{
    public:
        char ch;
        Char(char);
        ~Char();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class String: public Valor{
    public:
        std::string str;
        String(char*);    
        String(std::string);    
        ~String();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class Bool: public Valor{
    public:
        bool b;
        Bool(bool);    
        ~Bool();
        virtual void show(std::string);
        virtual void verificar(GuavaSymTable);
};

class LCorchetes{
    public:
        Exp exp;
        LCorchetes* lista;
        LCorchetes(Exp, LCorchetes*);    
        LCorchetes(Exp);    
        ~LCorchetes();
        void show(std::string);
        void verificar(GuavaSymTable);
};



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

class ExpBin: public Exp{
public:
    Exp exp1,exp2;
    std::string operacion;
    ExpBin(Exp,Exp,std::string);
    ~ExpBin();
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase principal de instruccion
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

class LVarArreglo{
public:
    std::string tipo;     /* Tipo */
    LCorchetes* corchetes;  /* Corchetes del arreglo */
    LVarArreglo* lista;    /* Lista  */
    LVarArreglo();
    LVarArreglo(std::string t, LVarArreglo* l);
    LVarArreglo(std::string t);    
    ~LVarArreglo();
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LVar{
public:
    std::string id;    /* id de la variable*/
    LVar* lista;       /* lista de LVar */
    LVar();
    LVar(std::string, LVar*);
    LVar(std::string t);
    ~LVar();
    void show(std::string);
    void verificar(GuavaSymTable);
};

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
    LVariables(Tipo, LVar);   
    LVariables(Tipo, LVar, LVariables);

    /*Caso en el que se declaran variables de tipo arreglo*/
    LVariables(Tipo, LVarArreglo);    
    LVariables(Tipo, LVarArreglo, LVariables);

    /*Para el caso en que se declaran uniones y records, simplemente no se
     *podria poner que el Tipo t = Union o Record o el ID de la estructura?
     *VER OBSERVACION 4
     */
    
    /*Caso definicion de Uniones*/
    LVariables(Estructura);     
    LVariables(Estructura, LVariables);

    ~LVariables();
    void show(std::string);
    
    /*Investigar: Como realizar la verificacion si los tipos de listas de
     *            variables son diferentes? No es como python que por ser
     *            debilmente tipado una misma verificacion servia para todo.
     */

    void verificar(GuavaSymTable);
};

class Record:public Estructura{
public:
    std::string identificador;     /* Nombre del record. */
    LVariables* lista;             /* Lista de variables. */
    Record();
    Record(std::string, LVariables*);
    ~Record();    
    void show(std::string);
    void verificar(GuavaSymTable);
};


class Union:public Estructura{
public:
    std::string identificador;     /* Nombre del union. */
    LVariables*   lista;           /* Lista de variables. */
    Union();
    Union(std::string, LVariables*);
    ~Union();    
    void show(std::string);
    void verificar(GuavaSymTable);
};

class IArreglo{
public:
    virtual ~IArreglo(){}

    virtual void show(std::string)=0;
    virtual void verificar(GuavaSymTable)=0;
};

class LArreglo{
public:
    Exp* exp;
    LArreglo* larr;
    IArreglo* arr;

    LArreglo(IArreglo*, LArreglo*);

    LArreglo(Exp, LArreglo*);

    ~LArreglo();
    
    void show(std::string);
    void verificar(GuavaSymTable);
};


class Arreglo:public IArreglo{
public:
    LArreglo* listaA;
    
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
    LVariables listaVar; /* Lista de variables a declarar */
    BloqueDeclare();
    BloqueDeclare(LVariables);    
    ~BloqueDeclare();
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LElseIf{
public:
    Exp exp;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;
    LElseIf* lelseif;
    LElseIf(Exp, BloqueDeclare, ListaInstrucciones, LElseIf*);
    LElseIf(BloqueDeclare, ListaInstrucciones);
    ~LElseIf();    
    void show(std::string);
    void verificar(GuavaSymTable);
};

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

class Asignacion: public Instruccion{
public:
    std::string identificador;
    std::string* identificador2;
    LCorchetes* lcorchetes;
    Arreglo* arreglo;
    Exp* exp;
    Asignacion();
    Asignacion(std::string, Exp*, LCorchetes*, std::string*, Arreglo*);
    ~Asignacion();    
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LoopFor: public Instruccion{
public:
    std::string identificador;
    Exp exp;
    Asignacion* asignacion;
    Exp* exp2;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;
    LoopFor(std::string, Exp, BloqueDeclare, ListaInstrucciones, Exp*, Asignacion*);
    ~LoopFor();  
    void show(std::string);
    void verificar(GuavaSymTable);
};

class PlusMinus: public Instruccion{
public:
    Exp exp;
    std::string tipo;
    PlusMinus(Exp, std::string);
    ~PlusMinus();
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LVaroValor{
public:
    Exp* exp;
    LVaroValor* lvarovalor;
    LVaroValor();
    LVaroValor(Exp*, LVaroValor*); 
    ~LVaroValor();        
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase de llamada funcion.
 */
class LlamadaFuncion: public Instruccion{
public:
    std::string identificador; /* Identificador de la funcion */
    LVaroValor lvarovalor;     /* Lista de variables o valores. */
    LlamadaFuncion(std::string, LVaroValor);
    ~LlamadaFuncion();
    void show(std::string);
    void verificar(GuavaSymTable);

};

/**
 * Clase para lista de parametros.
 */
class LParam{
public:
    Tipo tipo;
    std::string* identificador;
    LParam();
    LParam(Tipo, std::string*);
    LParam(Tipo, std::string*, LParam);
    ~LParam();
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase Funcion
 */
class Funcion{
public:
    Tipo tipo;
    std::string identificador;
    LParam* parametros;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listaI;
    Exp* retorno;
    Funcion();
    Funcion(Tipo, std::string, LParam*, BloqueDeclare* ,ListaInstrucciones*, Exp *);    
    ~Funcion();    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase para la lista de funciones-
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

class Program{
public:
    BloquePrincipal bloque;
    Program();
    Program(BloquePrincipal);
    ~Program();
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
}; 

