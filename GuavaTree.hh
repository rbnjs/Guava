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
 *
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
 
class Arreglo;
class LArreglo;
#include "GuavaSymTable.hh"

class Exp{
public:
    Exp(){
    }
    ~Exp(){}

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class ExpParentizada{
public:
    Exp exp;
    ExpParentizada(Exp e){
        Exp();
        exp = e;
    }
    ~ExpParentizada(){}

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Identificador{
public:
    std::string identificador;
    Identificador(std::string i){
        identificador = i;
    }
    ~Identificador(){}

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};


class Tipo{
public:
    std::string tipo;
    Tipo(){}
    Tipo(std::string t){
        tipo = t;
    }
    ~Tipo(){}

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Valor: public Exp{
public:
    Valor(){}
    virtual ~Valor(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Real: public Valor{
public:
    float real;
    Real(float f){
        Valor();
        real = f;
    }
    ~Real(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Integer: public Valor{
public:
    int integer;
    Integer(int i){
        Valor();
        integer = i;
    }
    ~Integer(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Char: public Valor{
public:
    char ch;
    Char(char c){
        Valor();
        ch = c;
    }
    ~Char(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class String: public Valor{
public:
    std::string str;
    String(char* s){
        str = std::string(s);
    }
    String(std::string s){
        Valor();
        str = s;
    }
    ~String(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class Bool: public Valor{
    bool b;
    Bool(bool b2){
        Valor();
        b2 = b;
    }
    ~Bool(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class LCorchetes{
public:
    Exp exp;
    LCorchetes* lista;
    LCorchetes(Exp e, LCorchetes* l){
        exp = e;
        *lista = *l;
    }
    LCorchetes(Exp e){
        exp = e;
        lista = 0;
    }
    ~LCorchetes(){}
    void show(std::string);
    void verificar(GuavaSymTable);
};



class ExpUn:public Exp{
public:
    Exp exp;
    Exp* exp2;
    LCorchetes* corchetes;
    std::string* operacion;
    ExpUn(Exp e, std::string* op){
        Exp();
        exp = e;
        *operacion = *op;
    }
    ExpUn(Exp e1, Exp* e2, std::string* op){
        exp = e1;
        *exp2 = *e2;
    }
    ExpUn(Exp e1, LCorchetes* lc){
        exp = e1;
        *corchetes = *lc;
    }
    ~ExpUn(){
        delete exp2;
        delete corchetes;
        delete operacion;
    }
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class ExpBin: public Exp{
public:
    Exp exp1,exp2;
    std::string operacion;
    ExpBin(Exp e1,Exp e2,std::string op){
        Exp();
        exp1 = e1;
        exp2 = e2;
        operacion = op;
    }
    ~ExpBin(){}

    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

/**
 * Clase principal de instruccion
 */
class Instruccion{
public:
    Instruccion* instruccion;

    Instruccion(){
    }

    Instruccion(Instruccion* i){
        *instruccion = *i;
    }

    ~Instruccion(){}
    virtual void show(std::string);
    virtual void verificar(GuavaSymTable);
};

class ListaInstrucciones{
public:
    Instruccion* instruccion;
    ListaInstrucciones* listainstrucciones;

    ListaInstrucciones(){}

    ListaInstrucciones(Instruccion* inst, ListaInstrucciones* li = 0){
        *instruccion = *inst;
        *li = *li;
    }
    ~ListaInstrucciones(){
        delete instruccion;
        delete listainstrucciones;
    }

    void show(std::string);
    void verificar(GuavaSymTable);
};

class LVarArreglo{
public:
    std::string tipo;     /* Tipo */
    LCorchetes* corchetes;  /* Corchetes del arreglo */
    LVarArreglo* lista;    /* Lista  */

    LVarArreglo(){}

    LVarArreglo(std::string t, LVarArreglo* l){
        tipo = t;
        *lista = *l;
        corchetes = 0;
    }

    LVarArreglo(std::string t){
        tipo = t;
        corchetes = 0;
        lista = 0;
    }
    ~LVarArreglo(){}
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LVar{
public:
    std::string tipo; /* Tipo del lvar */
    LVar* lista;       /* lista de LVar */
    LVar(){}
    LVar(std::string t, LVar* l = 0){
        tipo = t;
        *lista = *l;
    }

    LVar(std::string t){
        tipo = t;
    }

    ~LVar(){}

    void show(std::string);
    void verificar(GuavaSymTable);
};



/**
 * Clase que define una lista de variables a ser declaradas.
 * No se si sea bueno, o se vea bien, colocar todos los tipos de clases que
 * puede tener LVariables dependiendo de lo que se este declarando. Si no
 * entiendes preguntame para que te lo explique mejor.
 */
class LVariables {
public:
    Tipo t;              /*Tipo de las variables a declarar */
    
    /* Aqui pensaba colocar 'Modo' para ver si son pasadas por valor o por referencia*/

    LVar listaIds;          /* Lista de identificadores de variables */
    LVarArreglo listaIdsAr; /* Lista de identificadores de variables de tipo arreglo */
    Union u;                /* Bloque que define una union */
    Record r;               /* Bloque que defina un record */
    LVariables* listaVar;    /* En caso de declarar mas de una lista de variables. */

    /*Constructores*/

    LVariables(){}

    /*Caso en el que se declaran variables simples*/

    LVariables(Tipo tipo, LVar v) {
        t = tipo;
        listaIds = v;
    }
    LVariables(Tipo tipo, LVar v, LVariables listaVariables) {
        t = tipo;
        listaIds = v;
        *listaVar = listaVariables;
    }
    
    /*Caso en el que se declaran variables de tipo arreglo*/

    LVariables(Tipo tipo, LVarArreglo va) {
        t = tipo;
        listaIdsAr = va;
    }
    LVariables(Tipo tipo, LVarArreglo va, LVariables listaVariables) {
        t = tipo;
        listaIdsAr = va;
        *listaVar = listaVariables;
    }
    
    /*Para el caso en que se declaran uniones y records, simplemente no se
     *podria poner que el Tipo t = Union o Record o el ID de la estructura?
     *VER OBSERVACION 4
     */
    
    /*Caso definicion de Uniones*/
    LVariables(Union estructura) {
        u = estructura;
    }
    LVariables(Union estructura, LVariables listaVariables) {
        u = estructura;
        *listaVar = listaVariables;
    }

    /*Caso definicion de Records*/
    LVariables(Record estructura) {
        r = estructura;
    }
    LVariables(Record estructura, LVariables listaVariables) {
        r = estructura;
        *listaVar = listaVariables;
    }
    ~LVariables(){}
    void show(std::string);
    
    /*Investigar: Como realizar la verificacion si los tipos de listas de
     *            variables son diferentes? No es como python que por ser
     *            debilmente tipado una misma verificacion servia para todo.
     */

    void verificacion(GuavaSymTable);
};

class Record{
public:
    std::string identificador;     /* Nombre del record. */
    LVariables*   lista;            /* Lista de variables. */

    Record(){}

    Record(std::string id, LVariables* l=0){
        *lista = *l;
        identificador = id;
    }
    ~Record(){
    }
    void show(std::string);
    void verificador(GuavaSymTable);
};


class Union{
public:
    std::string identificador;     /* Nombre del union. */
    LVariables*   lista;        /* Lista de variables. */
    
    Union(){}

    Union(std::string id, LVariables* l){
        lista* = *l;
        identificador = id;
    }

    ~Union(){}

void show(std::string);
    void verificador(GuavaSymTable);
};

class LArreglo{
public:
    Exp* exp;
    LArreglo* larr;
    Arreglo* arr;

    LArreglo(Arreglo* a, LArreglo* lar = 0){
        *arr = *a;
        exp = 0;
        *larr = *lar;
    }

    LArreglo(Exp e, LArreglo* lar = 0){
        *exp = e;
        arr = 0;
        *larr = *lar;
    }
    
    void show(std::string);
    void verificar(GuavaSymTable);
};


class Arreglo{
public:
    LArreglo* listaA;
    
    Arreglo(LArreglo* l){
        *listaA = *l;
    }
    
    ~Arreglo(){}
    
    void show(std::string);
    void verificar(GuavaSymTable);
};

/**
 * Clase de bloque de declaraciones.
 */
class BloqueDeclare {
public:
    LVariables listaVar; /* Lista de variables a declarar */
    BloqueDeclare(){}
    BloqueDeclare(LVariables l) {
        listaVar = l;
    }
    ~BloqueDeclare(){}
    void show(std::string);
    void verificacion(GuavaSymTable);
};



class LElseIf{
public:
    Exp exp;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;
    LElseIf* lelseif;
    LElseIf(Exp e, BloqueDeclare d, ListaInstrucciones li, LElseIf* lif = 0){
        exp = e;
        declaraciones = d;
        listainstrucciones = li;
        *lelseif = *lif;
    }
    ~LElseIf(){
        delete lelseif;
    }
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

    SelectorIf(Exp e, BloqueDeclare* d = 0, ListaInstrucciones* l = 0, LElseIf* lif = 0){
        exp = e;
        *declaraciones = *d;
        *listainstrucciones = *l;
        *lelseif = *lif;
    }

    SelectorIf(Exp e, Instruccion* i, Instruccion* i2 = 0){
        exp = e;
        *instruccion1 = *i;
        *instruccion2 = *i2;
    }
    ~SelectorIf(){
        delete declaraciones;
        delete listainstrucciones;
        delete instruccion1;
        delete instruccion2;
        delete lelseif;
    }
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LoopWhile: public Instruccion{
public:
    Exp exp;
    BloqueDeclare declaraciones;
    ListaInstrucciones listainstrucciones;
    LoopWhile(Exp e, BloqueDeclare bd, ListaInstrucciones li){
        exp = e;
        declaraciones = bd;
        listainstrucciones = li;
    }
    ~LoopWhile(){}

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

    Asignacion(){}

    Asignacion(std::string id, Exp* e = 0, LCorchetes* lc = 0 
                , std::string* id2 = 0, Arreglo* arr = 0){
        identificador = id;
        *exp = *e;
        *lcorchetes = *lc;
        *identificador2 = *id2;
        *arreglo = *arr;
    }

    ~Asignacion(){
        delete identificador2;
        delete lcorchetes;
        delete arreglo;
        delete exp;
    }
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

        LoopFor(std::string id, Exp e1,BloqueDeclare d, ListaInstrucciones l,
                Exp* e2 = 0, Asignacion* a = 0){
            identificador = id;
            exp = e1;
            *asignacion = *a;
            exp2 = e2;
            declaraciones = d;
            listainstrucciones = l;
        }

        ~LoopFor(){
            delete asignacion;
            delete exp2;
        }
        void show(std::string);
        void verificar(GuavaSymTable);
};

class PlusMinus: public Instruccion{
    public:
        Exp exp;
        std::string tipo;
        PlusMinus(Exp e, std::string t){
            exp = e;
            tipo = t;
        }
        ~PlusMinus(){}

        void show(std::string);
        void verificar(GuavaSymTable);
};

class LVaroValor{
    public:
        Exp* exp;
        LVaroValor* lvarovalor;
        LVaroValor(Exp* e = 0, LVaroValor* lv = 0){
            exp = e;
            *lvarovalor = *lv;
        }
        ~LVaroValor(){
            delete lvarovalor;
        }
        void show(std::string);
        void verificar(GuavaSymTable);
};

class LlamadaFuncion: public Instruccion{
    public:
        std::string identificador;
        LVaroValor lvarovalor;
        LlamadaFuncion(std::string id, LVaroValor lv){
            identificador = id;
            lvarovalor = lv;
        }
        ~LlamadaFuncion(){}
        void show(std::string);
        void verificar(GuavaSymTable);

};





class LParam{
public:
    Tipo tipo;
    std::string* identificador;
    
    LParam(Tipo t, std::string* id = 0 ){
        tipo = t;
        *identificador = *id; 
    }
    ~LParam(){ delete identificador; }

    void show(std::string);
    void verificar(GuavaSymTable);
};

class Funcion{
public:
    Tipo tipo;
    std::string identificador;
    LParam* parametros;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listaI;
    Exp* retorno;

    Funcion(){}

    Funcion(Tipo t, std::string id, LParam* param = 0, BloqueDeclare* decl = 0,
            ListaInstrucciones* li = 0, Exp * r = 0){
                tipo = t;
                *parametros = *param;
                *declaraciones = *decl;
                *listaI = *li;
                *retorno = *r;
            }
    ~Funcion(){
        delete parametros;
        delete declaraciones;
        delete listaI;
        delete retorno;
    }
    void show(std::string);
    void verificar(GuavaSymTable);
};

class LFunciones{
public:
    Funcion funcion;
    LFunciones* lista;
    
    LFunciones(){}
    
    LFunciones(Funcion f, LFunciones* l = 0){
        funcion = f;
        *lista = *l;
    }

    ~LFunciones(){delete lista;}

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
    BloquePrincipal(BloqueDeclare b, LFunciones l) {
        globalD = b;
        funciones = l;
    }
    ~BloquePrincipal(){}
    void show(std::string);
    void verificacion(GuavaSymTable);
};

