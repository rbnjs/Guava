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

# include "GrafoBloques.hh"
# include <list>
# include <utility>
# include <iostream>
# include <sstream>
#include <functional>


/**
 * Clase que representa los Labels booleanos.
 *
 */
class BoolLabel{
public:
    GuavaQuads* true_label;
    GuavaQuads* false_label;
    BoolLabel(GuavaQuads* true_, GuavaQuads* false_):  true_label(true_), false_label(false_){}
    BoolLabel(){}
    ~BoolLabel(){}
};

/**
 * Clase que representa todas las clases booleanas
 */
class ExpBool{
public:
    BoolLabel* labels_bool;
    ExpBool(){ labels_bool = new BoolLabel(); }
    ~ExpBool(){};
};

/**
 * Clase que define las expresiones del lenguaje.
 */
class Exp{
public:

    Symbol* addr;
    NewTemp* temp;
    std::list<GuavaQuads*>* listaQuads;
    virtual TypeS* get_tipo() { return 0; }; 
    virtual void show(std::string) = 0;
    /**
     * Funcion que retorna un apuntador a lista de Quads
     */
    virtual std::list<GuavaQuads*>* generar_quads(){ return 0; };
    /**
     * Funcion que a partir de la lista de quads respectivos, retorna el
     * codigo intermedio asociado.
     */
    std::string gen();

    virtual BoolLabel* bool_label(){return 0;}

    virtual GuavaSymTable* get_tabla(){return 0;}

    virtual bool exp_id(){ return false; }

    virtual bool exp_un(){ return false; }

    virtual bool exp_bin(){ return false; }

    virtual bool exp_bool(){ return false; }

    virtual bool exp_llamada(){ return false; }

    virtual bool operator==(Exp* e){
        return true;
    }
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
    Symbol* bp;
    
    TypeS* get_tipo() { return tipo; }; 
    Identificador();
    Identificador(std::string s, TypeS* t = 0): identificador(s), tipo(t){
    }
    ~Identificador();
    
    virtual void show(std::string);
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    bool operator==(Identificador id){
        return identificador.compare(id.identificador);
    }
};


/**
 * Define la estructuracion de los arreglos de datos en el lenguaje.
 */
class LArreglo{
public:
    std::list<Exp*> larr;
    TypeS* tipo_primitivo;
    TypeS* tipo_estructura;
    int line;
    int column;

    LArreglo();
    void append(Exp*);
    ~LArreglo();
    int size(){ return larr.size(); }
    TypeS* get_tipo() { return tipo_primitivo; }
    TypeS* get_tipoEstructura() { return tipo_estructura; }
    //TypeS* get_tipo_array() { return (new TypeArray(tipo,larr.size())); } 
    void show(std::string);

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    bool operator==(LArreglo la){
        if (la.size() != larr.size()) return false;
        std::list<Exp*>::iterator it_la = la.larr.begin();
        for (std::list<Exp*>::iterator it = larr.begin();
             it != larr.end(); ++it ){
            if (*it == *it_la){

            } else{
                return false;
            }
        }
        return true;
    }
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

    virtual void  set_line_column(int l, int c){}
    virtual void show(std::string) = 0;
    virtual std::string* get_valor_str(){ return 0; }

    virtual std::list<GuavaQuads*>* generar_quads(){ return 0; };

};

/**
 * Clase que define los numeros reales dentro del lenguaje.
 */
class Real: public Valor{
public:
    int line;
    int column;
    TypeS* tipo; 
    float valor;

    bool is_real() { return true; }
    Real(float valor_, TypeS* tipo_): tipo(tipo_), valor(valor_){
        std::ostringstream convert;
        convert << valor;
        addr = new Symbol(convert.str());
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
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    /* Por ser un valor constante, no hace falta asignarselo a un temporal,
     * evitamos que sea dedicado un registro para guardar su valor. MIPS
     * acepta constantes.
     *
     * Sera analogo a todas las constantes.
     */
    std::list<GuavaQuads*>* generar_quads(){ 
        return 0;
    };

    bool operator==(Real r){
        return (valor == r.valor);
    }
};

/**
 * Clase que define los numeros enteros dentro del lenguaje.
 */
class Integer:public Valor{
public:
    int valor;
    TypeS* tipo;
    int line;
    int column;

    bool is_int() { return true; }
    Integer(int valor_ , TypeS* tipo_ ): valor(valor_), tipo(tipo_) {
        std::ostringstream convert;
        convert << valor;
        addr = new Symbol(convert.str());
    }   
    int getValor() {return valor;}
    TypeS* get_tipo() { return tipo; }
    ~Integer(){}
    void show(std::string s ){
        std::cout << s << "Valor Real: ";
        std::cout << valor;
        std::cout << std::endl;
    }
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    std::list<GuavaQuads*>* generar_quads(){
        return 0;
    };
    
    bool operator==(Integer r){
        return (valor == r.valor);
    }
};

/**
 * Clase que define los caracteres del lenguaje.
 */
class Char: public Valor{
public:
    char valor;
    TypeS* tipo;
    int line;
    int column;

    bool is_char() { return true; }
    Char(char valor_ , TypeS* tipo_): valor(valor_), tipo(tipo_) {
        std::ostringstream convert;
        convert << "'" << valor << "'";
        addr = new Symbol(convert.str());
    }
    char get_valor() { return valor; } 
    ~Char(){}
    TypeS* get_tipo() { return tipo; }

    void show(std::string s){
        std::cout << s << "Caracter: ";
        std::cout << valor;
        std::cout << std::endl;
    }
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
   
    /* Para el caso de los caracteres constantes se manejara igual que con los
     * numeros constantes (reales y enteros). Recordando que los caracteres
     * son codigos hexadecimales.
     *
     * Habria que pensar en la conversion: Seria en el codigo intermedio o ya
     * en el final?. Por los momentos, se deja como el
     * caracter solo entre comillas.
     */
    std::list<GuavaQuads*>* generar_quads(){ 
        return 0;
    };
    
    bool operator==(Char r){
        return (valor == r.valor);
    }
};

/**
 * Clase que define las cadenas de caracteres del lenguaje.
 */
class String: public Valor{
public:
    std::string* valor;
    TypeS* tipo;
    int line;
    int column;

    bool is_str() { return true; }
    String(char* valor_ , TypeS* tipo_): valor( new std::string(valor_)), tipo(tipo_) {
        addr = new Symbol(*valor);
    }
    String(std::string* valor_ , TypeS* tipo_): valor(valor_), tipo(tipo_) {}
    std::string* get_valor(){ return valor; } 
    TypeS* get_tipo() { return tipo; }
    ~String(){}

    void show(std::string s){
        std::cout << s << "Cadena de Caracteres: ";
        std::cout << *valor;
        std::cout << std::endl;
    }
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    std::string* get_valor_str(){
        return valor;
    }
    
    /* Los Strings seran guardados en memoria en un "identificador unico".
     * Por los momentos se mantiene entonces que su valor sea asignado a un
     * temporal.
     */
    std::list<GuavaQuads*>* generar_quads(){ 
        std::ostringstream convert;
        Symbol* nombre = new Symbol(*valor); 
        addr = temp->newtemp();
        GuavaQuads* nuevo = new GuavaQuadsExp(std::string(":="),nombre, 0, addr);
        listaQuads = new std::list<GuavaQuads*>();
        listaQuads->push_back(nuevo);
        return listaQuads;
    };
};

/**
 * Clase que define el tipo de datos booleanos.
 */
class Bool: public Valor, public ExpBool{
public:
    bool valor;
    TypeS* tipo;
    int line;
    int column;

    bool is_bool() { return true; }

    virtual BoolLabel* bool_label(){return labels_bool;}

    Bool(bool valor_, TypeS* tipo_ ): valor(valor_), tipo(tipo_), ExpBool() {
        std::ostringstream convert;
        convert << valor;
        addr = new Symbol(convert.str());
    }  
    bool  get_valor() { return valor; }
    TypeS* get_tipo() { return tipo; }
    ~Bool();

    void show(std::string s){
        std::cout << s << "Booleano: ";
        std::cout << valor;
        std::cout << std::endl;
    }
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    bool exp_bool(){ return true; }

    std::list<GuavaQuads*>* generar_quads(){ 
        std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>;
        if (valor){
            GuavaQuads* go_to = new GuavaGoTo(labels_bool->true_label);
        }else {
            GuavaQuads* go_to = new GuavaGoTo(labels_bool->false_label);
        }
        return result;
    };

    bool operator==(Bool b){
        return (valor == b.valor);
    }
};

/**
 * Clase que define la estructura de un arreglo, indicando sus dimensiones.
 */
class LCorchetes{
public:
    TypeS* tipo;
    int line;
    int column;
    std::list<int> lista;
    LCorchetes(){
        tipo = 0;
    }
    LCorchetes(bool);
    void append(int);
    ~LCorchetes();

    void show(std::string);
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

};

/**
 * Clase que define la estructura de acceso a elementos de un arreglo.
 */
class LCorchetesExp{
public:
    TypeS* tipo;
    std::list<Exp*> lista;
    int line;
    int column;
    Symbol* addr;

    LCorchetesExp();
    ~LCorchetesExp();
    TypeS* get_tipo() { return tipo; }
    void append(Exp* e){
        lista.push_front(e);
    }
    void show(std::string s){
        std::cout << s << "Lista de Expresiones de Corchetes: \n";
        for (std::list<Exp*>::iterator it = lista.begin();
            it != lista.end();
            ++it){
                Exp * tmp = *it;
                tmp->show(s+ "  ");
            }
    }
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

};

/**
 * Define las expresiones unarias del lenguajes.
 */
class ExpUn:public Exp{
public:
    Exp* exp;
    int line;
    int column;
    TypeS* tipo;
    LCorchetes* corchetes;
    std::string *operacion;

    ExpUn(Exp*, std::string*);
    ExpUn(Exp*, LCorchetes*);    
    ~ExpUn();
    TypeS* get_tipo() { return tipo; }

    virtual void show(std::string);
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    std::string revision_unaria(Exp* exp_1, TypeS* tipo_esperado1, TypeS* tipo_esperado2, ExpUn* tmp, std::string (*f)(std::string,std::string) );
   
    /**  
     * Genero los quads para las expresiones unarias.
     */
    virtual std::list<GuavaQuads*>* generar_quads(){
        listaQuads = exp->generar_quads();
        addr = temp->newtemp();
        GuavaQuads* nuevo;
        if (operacion->compare(std::string("pincrease")) == 0){
            nuevo = new GuavaQuadsExp("+",exp->addr, new Symbol("1"),addr);
        } else if (operacion->compare(std::string("pdecrease")) == 0) {
            nuevo = new GuavaQuadsExp("-",exp->addr, new Symbol("1"),addr);
        }else {
            nuevo = new GuavaQuadsExp(*operacion,exp->addr, 0, addr);
        }
        //Se verifica si la expresion es un identificador
        if (listaQuads == 0) {
            listaQuads = new std::list<GuavaQuads*>();
        }
        listaQuads->push_back(nuevo);
        GuavaQuads* comentario = new GuavaComment("EXPRESION UNARIA", line, column);
        listaQuads->push_front(comentario);
        return listaQuads;
    }

    bool operator==(Exp* un_){
        if (!un_->exp_un()) return false;
        ExpUn* un = (ExpUn*) un_;
        return ((exp == un->exp) && operacion->compare(*un->operacion) && (corchetes == un->corchetes) );
    }
};

class ExpUnBool: public ExpUn, public ExpBool{
public:
    ExpUnBool(Exp* , std::string*);

    virtual BoolLabel* bool_label(){return labels_bool;}
    bool exp_bool(){ return true; }

    std::list<GuavaQuads*>* generar_quads();
};

/**
 * Define las expresiones binarias del lenguaje.
 */
class ExpBin: public Exp{
public:
    TypeS* tipo;
    int line;
    int column;
    Exp* exp1;
    Exp* exp2;
    std::string operacion;

    /**
     * Constructor para las expresiones binarias.
     */
    ExpBin();
    ExpBin(Exp*,Exp*,std::string);
    ~ExpBin();

    TypeS* get_tipo() { return tipo; }

    virtual void show(std::string);

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    std::string revision_binaria(Exp* exp_1, Exp* exp_2, ExpBin* tmp, TypeS* tipo_esperado1,
                                 TypeS* tipo_esperado2, std::string (*mensaje_error_tipos)(std::string,std::string),
                                 std::string (*mensaje_diff_operandos)(std::string,std::string,std::string,std::string));
    std::string revision_comparison(Exp* exp_1, Exp* exp_2, ExpBin* tmp, int cmpv,
                                    std::string (*mensaje_error_tipos)(std::string,std::string),
                                    std::string (*mensaje_diff_operandos)(std::string,std::string,std::string,std::string));

    virtual std::list<GuavaQuads*>* generar_quads(){ 
        std::list<GuavaQuads*>* quads1 = exp1->generar_quads();
        std::list<GuavaQuads*>* quads2 = exp2->generar_quads();
        addr = temp->newtemp();
        GuavaQuads * nuevo = new GuavaQuadsExp(operacion,exp1->addr,exp2->addr,addr);
        //Se verifica que la expresion izquierda no sea un identificador
        if (quads1 != 0) {
            //Se verifica que la expresion derecha no sea un identificador
            if (quads2 != 0) {
                quads1->splice(quads1->end(),*quads2);
            }
            quads1->push_back(nuevo);
            listaQuads = quads1;
        }
        //Se verifica que la expresion derecha no sea un identificador
        else if (quads2 != 0){
            quads2->push_back(nuevo);
            listaQuads = quads2;
        }
        //Caso ambas expresiones identificadores
        else {
            listaQuads = new std::list<GuavaQuads *>();
            listaQuads->push_back(nuevo);
        }
        GuavaQuads* comentario = new GuavaComment("EXPRESION BINARIA.",line, column);
        listaQuads->push_front(comentario);
        return listaQuads;
    }

    bool operator==(Exp* e_){
        if (!e_->exp_bin()) return false;
        ExpBin* e = (ExpBin*) e_;
        return ((exp1 == e->exp1) && (exp2 == e->exp2));
    }

};

class ExpBinBoolComparison: public ExpBin, public ExpBool{
public:
    ExpBinBoolComparison(Exp*,Exp*,std::string);
    ~ExpBinBoolComparison(){}
    BoolLabel* bool_label(){return labels_bool;}
    bool exp_bool(){ return true; }
    std::list<GuavaQuads*>* generar_quads();
};

class ExpBinBoolLogic: public ExpBin, public ExpBool{
public:
    bool AND = false;
    ExpBinBoolLogic(Exp*,Exp*,std::string);
    ~ExpBinBoolLogic(){}
    BoolLabel* bool_label(){return labels_bool;}
    bool exp_bool(){ return true; }
    std::list<GuavaQuads*>* generar_quads();
};


/**
 * Clase principal de instruccion.
 */
class Instruccion{
public:
    GuavaQuads* next;
    virtual TypeS* get_tipo() {return TypeVoid::Instance();} 
    virtual void show(std::string) = 0;
    virtual bool es_return(){ return false; }
    virtual bool continue_break(){ return false; } 
    virtual bool tiene_lista_instrucciones() { return false; }
    virtual bool selector_if() { return false; } 
    virtual int get_line() { return 0; }
    virtual int get_column() { return 0; }
    virtual std::list<GuavaQuads*>* generar_quads(){ return 0; }
    virtual void set_begin(GuavaQuads*){ }
};



/**
 * Clase Error
 */
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
    GuavaQuads* next;

    ListaInstrucciones();
    ListaInstrucciones(Instruccion*, ListaInstrucciones*);    
    ~ListaInstrucciones();
    TypeS* get_tipo() { return tipo; }
    void show(std::string);
    std::list<Instruccion*> obtener_return();
    std::list<GuavaQuads*>* generar_quads();

    std::list<Instruccion*> obtener_continue_break();

    void set_begin(GuavaQuads*);

    void set_next(Instruccion* inst);

};

/**
 * Clase de instruccion retorno.
 */
class Retorno: public Instruccion{
public:
    int line;
    int column;
    Exp* exp;
    TypeS* tipo;
    Symbol* tmp_return;
    

    Retorno(Exp* e): exp(e){ if (e != 0) tipo = e->get_tipo(); }
    Retorno(Exp* e,int line_,int col_):exp(e), line(line_), column(col_){ if (e != 0) tipo = e->get_tipo(); }
    ~Retorno(){}

    void show(std::string s){
        std::ostringstream convert; 
        convert << line;
        std::string linea = convert.str();
        convert.flush();
        convert << column;
        std::string columna = convert.str();
        std::cout << s << "Retorno, linea: " << linea << ", columna: " << columna << "\n";
        if (exp != 0) exp->show(s+"  ");
    }

    TypeS* get_tipo(){
        if (exp == 0){
            return TypeVoid::Instance();
        }
        return tipo;
    }

    bool es_return(){ return true; }

    int get_line() { return line; }
    int get_column() { return column; }

    std::list<GuavaQuads*>* generar_quads();
};


/**
 * Clase que describe una lista de identificadores de estructuras de datos
 * de tipo arreglo.
 */
class LVarArreglo{
public:
    std::list<std::pair <Identificador, LCorchetes> > lista;
    int line;
    int column;

    LVarArreglo();
    LVarArreglo(Identificador, LCorchetes);
    void append(Identificador,LCorchetes);
    std::list<std::pair <Identificador, LCorchetes> > get_list();
    ~LVarArreglo();

    void show(std::string);
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
};

/**
 * Clase que describe una lista de identificadores.
 */
class LVar{
public:
    int line;
    int column;
    std::list<Identificador> lista; 
    LVar();
    LVar(std::list<Identificador>);
    void append(Identificador);
    ~LVar();
    std::list<Identificador> get_list();

    void show(std::string);
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
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
    int line;
    int column;
    Record();
    Record(Identificador, LVariables*);
    ~Record();    
    LVariables* get_lvar();
    Identificador get_id();
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
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
    int line;
    int column;
    Union();
    Union(Identificador, LVariables*);
    ~Union();   
    LVariables* get_lvar();
    Identificador get_id();
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
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
    TypeS* tipo_primitivo;
    int tam_tipo_primitivo;
    TypeS* tipo_estructura;
    int line;
    int column;
    Symbol* direccion;

    bool is_array() { return true; }
    Arreglo();
    Arreglo(LArreglo*);    
    ~Arreglo();
    /**  
     * Retorna el tipo primitivo del arreglo
     */
    TypeS* get_tipo(){ 
        return tipo_primitivo;
    }
    /** 
     * Nos retorna el tipo completo del arreglo.
     */
    TypeS* get_tipoEstructura() {
        return tipo_estructura;
    }


    void show(std::string s);

    void set_line_column(int l, int c) {
        line = l;
        column = c;
    }

    bool operator==(Arreglo a){
        if (la == a.la){
            return true;
        } else {
            return false;
        }
    }

    std::list<GuavaQuads*>* generar_quads();
    
};

/**
 * Clase de bloque de declaraciones.
 */
class BloqueDeclare {
public:
    int scope;
    int line;
    int column;
    
    BloqueDeclare();
    BloqueDeclare(int);    
    ~BloqueDeclare();
    
    void show(std::string);
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
};
/**
 * Clase que reune a todas aquellas instrucciones que tienen lista de instrucciones.
 */
class InstruccionConLista: public Instruccion{
public:
    bool tiene_lista_instrucciones(){
        return true;
    }
    ListaInstrucciones*  obtener_lista_instrucciones() { return 0; } 
    
};

/**
 * Clase necesaria para establecer varias clausulas de condicionales else
 * en un bloque de instrucciones condicionados por IF.
 */
class LElseIf: public InstruccionConLista{
public:
    TypeS* tipo = 0;
    Exp* exp = 0;
    int line;
    int column;
    BloqueDeclare* declaraciones = 0;
    ListaInstrucciones* listainstrucciones = 0;
    LElseIf* lelseif = 0;

    LElseIf(bool);
    LElseIf(Exp*, BloqueDeclare*, ListaInstrucciones*, LElseIf*);
    LElseIf(BloqueDeclare*, ListaInstrucciones*, LElseIf*);

    ~LElseIf();
    TypeS* get_tipo(){return tipo;}

    void show(std::string);

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    ListaInstrucciones* obtener_lista_instrucciones(){
        return listainstrucciones;
    }

    bool es_vacio(){ return (exp == 0 && lelseif == 0 && declaraciones == 0 && listainstrucciones == 0); }

    virtual std::list<GuavaQuads*>* generar_quads();

};

class Else: public LElseIf{
public:
    Else(BloqueDeclare* b, ListaInstrucciones* li, LElseIf* leif = 0);
    ~Else(){}
    std::list<GuavaQuads*>* generar_quads();
};

class ElseIf: public LElseIf{
public:
    ElseIf(Exp* e, BloqueDeclare* bd, ListaInstrucciones* li, LElseIf* leif = 0);
    ~ElseIf(){}
    std::list<GuavaQuads*>* generar_quads();
};

/**
 * Clase que define los bloques de codigo sujestos a condiciones para su
 * ejecucion, bloques dentro de instrucciones de clausulas IF THEN ELSE.
 */
class SelectorIf: public InstruccionConLista{
public:
    TypeS* tipo;
    Exp* exp;
    int line;
    int column;

    SelectorIf(): tipo(TypeError::Instance()){}
    SelectorIf(Exp* exp_): exp(exp_), tipo(TypeVoid::Instance()){}
    ~SelectorIf(){}

    TypeS* get_tipo() { return tipo; } 
    
    virtual void show(std::string) { }

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    
    bool selector_if() { return true; }

    virtual ListaInstrucciones* obtener_lista_instrucciones(){
        return 0;
    }

    virtual Instruccion* obtener_instruccion1(){ return 0; }

    virtual Instruccion* obtener_instruccion2(){ return 0; }

    virtual std::list<GuavaQuads*>* generar_quads();
};

/** 
 * Clase del SelectorIfSimple
 */
class SelectorIfSimple: public SelectorIf{
public:
    Instruccion* instruccion1; 
    Instruccion* instruccion2;

    SelectorIfSimple(Exp*, Instruccion*, Instruccion*);    
    ~SelectorIfSimple(){}

    /* Getters y setters */

    Instruccion* obtener_instruccion1(){ return instruccion1; }

    Instruccion* obtener_instruccion2(){ return instruccion2; }

    std::list<GuavaQuads*>* generar_quads();

    void show(std::string);

};

class SelectorIfComplejo: public SelectorIf{
public:
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    LElseIf* lelseif;

    SelectorIfComplejo(Exp*, BloqueDeclare*, ListaInstrucciones*, LElseIf*);

    ~SelectorIfComplejo(){}

    ListaInstrucciones* obtener_lista_instrucciones(){
        return listainstrucciones;
    }

    std::list<GuavaQuads*>* generar_quads();

    void show(std::string);
    
};

/**
 *
 */
class ErrorBoolExp{
bool error;
public:
    int line;
    int column;
    Exp* exp;
    ErrorBoolExp(Exp* e): exp(e), error(false) { }
    ErrorBoolExp(): error(true), exp(0){}
    ~ErrorBoolExp() { delete this; }
    TypeS* get_tipo(){
        if (exp!= 0) return exp->get_tipo();
        return 0;
    }
    bool get_error(){ return error; }

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    
    BoolLabel* bool_label(){
        return exp->bool_label();
    }

};

/**
 * Clase que define los bloques de instrucciones con iteracion indeterminada.
 */
class LoopWhile: public InstruccionConLista{
public:
    Exp* exp;
    TypeS* tipo;
    int line;
    int column;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    GuavaQuads* begin;


    /* Constructores y destructores. */
    LoopWhile(): exp(0), tipo(TypeError::Instance()), declaraciones(0), listainstrucciones(0){}
    LoopWhile(Exp*, BloqueDeclare*, ListaInstrucciones*);

    TypeS* get_tipo() { return tipo; } 
    ~LoopWhile();

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    void show(std::string);

    ListaInstrucciones* obtener_lista_instrucciones(){
        return listainstrucciones;
    }

    virtual std::list<GuavaQuads*>* generar_quads(){ return 0; }

};

class WhileDo: public LoopWhile{
public:
    WhileDo(Exp*, BloqueDeclare*, ListaInstrucciones*);
    ~WhileDo(){}

    std::list<GuavaQuads*>* generar_quads();
};

class DoWhile: public LoopWhile{
public:
    DoWhile(Exp*, BloqueDeclare*, ListaInstrucciones*);
    ~DoWhile(){}

    std::list<GuavaQuads*>* generar_quads();
};

/**
 * Clase que define las asignaciones de expresiones a variables del
 * lenguaje.
 */
class Asignacion: public Instruccion{
public:
    TypeS* tipo;
    Exp* id;
    int line;
    int column;
    Exp* exp;

    Asignacion();
    Asignacion(Exp*, Exp*);
    ~Asignacion();
    TypeS* get_tipo() { return tipo; } 

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    std::list<GuavaQuads*>* generar_quads();

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
    int line;
    int column;
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

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
};

/**
 * Clase que representa un Exp con identificador
 */
class ProtoExpID: public Exp{
public:
    bool exp_id(){ return true; }
};


/**
 * Clase para las expresiones de identificador.
 */
class ExpID: public ProtoExpID{
public:
    int line,column;
    TypeS* tipo;
    ExpID* exp_id = 0;
    Identificador* identificador = 0;
    LCorchetesExp* lcorchetesexp = 0;  
    GuavaSymTable* tabla = 0;
    int offset = -1;
    
    //LUEGO DEL GRAN CAMBIO ESTO SE PUEDE BORRAR
    Symbol* bp = 0;

    //Unions y records
    int offset_structure = 0;

    /**
     * Constructores de la clase.
     */
    ExpID():tipo(TypeError::Instance()), identificador(0), lcorchetesexp(0){}
    ExpID(Identificador* id): identificador(id){}
    ExpID(Identificador* id, LCorchetesExp* lce ): identificador(id), lcorchetesexp(lce){}
    ExpID(ExpID* exp_,Identificador* id): exp_id(exp_),identificador(id){}
    ExpID(ExpID* exp_,Identificador* id, LCorchetesExp* lce): exp_id(exp_),identificador(id),lcorchetesexp(lce){}

    ~ExpID(){
    }

    TypeS* get_tipo(){ return tipo; }

    GuavaSymTable* get_tabla(){ return tabla; }

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    void show(std::string s){
        if (identificador != 0) identificador->show(s);
        if (lcorchetesexp != 0) lcorchetesexp->show(s);
    }

    /**
     * Genera los quads para cada tipo de expresion con identificador
     * Aun se encuentra incompleta.
     */
    virtual std::list<GuavaQuads*>* generar_quads();

    /**
     * Realiza una revision sencilla en un identificador
     */
    static std::string revision_exp_id(Symbol* id,Identificador* identificador,ExpID* result, int line, int column, TypeS* (*obtener_tipo_simbolo)(Symbol*)); 

    /**
     * Realiza la revison del caso arreglo sencillo.
     */
    static std::string revision_exp_id_arreglo(Symbol* id ,Identificador* identificador, NewTemp* temp,
                                                      LCorchetesExp* lce,ExpID* result,int line, int column,
                                                      TypeS* (*obtener_tipo_simbolo)(Symbol*),std::string (*mensaje_error_tipo)(std::string,std::string));

    void init_array(Symbol* id, TypeS* tipo, TypeS* (*contents)(TypeS*));

    int offset_acceso_estructuras(ExpID* );
    
    bool operator==(ExpID);
};



/**
 * Clase que describe los bloques de instrucciones con iteraciones acotadas.
 */
class LoopFor: public InstruccionConLista{
public:
    ExpID* identificador;
    TypeS* tipo;
    Exp* exp_bool;
    int line;
    int column;
    Asignacion* asignacion;
    Exp* exp_aritmetica;
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listainstrucciones;
    GuavaQuads* begin;

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    LoopFor():identificador(0), tipo (TypeError::Instance()), exp_bool (0), asignacion(0), exp_aritmetica(0), declaraciones(0),listainstrucciones(0){}
    LoopFor(ExpID*, Exp*, Exp*, BloqueDeclare*, ListaInstrucciones*);
    LoopFor(ExpID*, Exp*, Asignacion*, BloqueDeclare*, ListaInstrucciones*);
    ~LoopFor();  
    TypeS* get_tipo() { return tipo; } 
    
    void show(std::string);

    ListaInstrucciones* obtener_lista_instrucciones(){
        return listainstrucciones;
    }

    virtual std::list<GuavaQuads*>* generar_quads(){ return 0; }
};


class LoopForExp:public LoopFor{
public:
    LoopForExp(ExpID*, Exp*, Exp*, BloqueDeclare*, ListaInstrucciones*);
    ~LoopForExp(){}
    std::list<GuavaQuads*>* generar_quads();
};

class LoopForAsignacion: public LoopFor{
public:
    LoopForAsignacion(ExpID*, Exp*, Asignacion*, BloqueDeclare*, ListaInstrucciones*);
    ~LoopForAsignacion(){}
    std::list<GuavaQuads*>* generar_quads();
};

/**
 * Clase para los incrementos y decrementos (prefijos y postfijos)
 */
class PlusMinus: public Instruccion{
public:
    int line;
    int column;
    ExpID* identificador;
    int tipo_inst; /* 0 para el dremento prefijo.
                    * 1 para el decremento postfijo.
                    * 2 para el incremento prefijo.
                    * 3 para el incremento prostfijo. */
    TypeS* tipo;

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    
    PlusMinus():identificador(0),tipo_inst(-1),tipo(TypeError::Instance()){}
    PlusMinus(ExpID*, int);
    ~PlusMinus();
    TypeS* get_tipo(){ return tipo; }
    
    void show(std::string);

    std::list<GuavaQuads*>* generar_quads();
};

/**
 * Clase de lista de valores o variables, argumento de funciones e
 * instruccions print y read.
 */
class LVaroValor{
public:
    TypeS* tipo;
    int line;
    int column;
    std::list<Exp*> lvarovalor;

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    LVaroValor(bool);
    void append(Exp* e);
    ~LVaroValor();        

    int size(){
        return lvarovalor.size();
    }

    std::list<Exp*>::iterator begin(){
        return lvarovalor.begin();
    }

    std::list<Exp*>::iterator end(){
        return lvarovalor.end();
    }
    
    void show(std::string);
};

/**
 * Clase de entrada y salida estandar (Instrucciones print y read)
 */
class EntradaSalida: public Instruccion {
public:
    int tipo; /*0 para entrada: read; 1 para salida: print*/
    int line;
    int column;
    Exp* argumento;
    
    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    EntradaSalida(int, Exp*);
    TypeS* get_tipo(){
        TypeS* error = (TypeS*) TypeError::Instance();
        if (argumento->get_tipo() ==  error ) return TypeError::Instance();
        return TypeVoid::Instance();
    }
    ~EntradaSalida();

    void show(std::string);

    std::list<GuavaQuads*>* generar_quads(){
        bool tipo_entrada_salida = (tipo == 0);
        GuavaQuads* salida_entrada;
        std::string operacion (tipo_entrada_salida ? "read" : "print");
        std::list<GuavaQuads*>* result = argumento->generar_quads();
        if (tipo_entrada_salida){
            salida_entrada = new GuavaEntradaSalida(operacion,argumento->addr, argumento->addr);
        } else {
            salida_entrada = new GuavaEntradaSalida(operacion, argumento->addr);
        }
        result->push_back(salida_entrada);
        GuavaQuads* comentario = new GuavaComment("ENTRADA Y SALIDA.", line, column);
        result->push_front(comentario);
        return result;
    }
};

/**
 * Clase de llamada funcion.
 */

class LlamadaFuncion: public Exp, public Instruccion{
public:
    TypeS* tipo;
    int line;
    int column;
    Identificador* id; /* Identificador de la funcion */
    LVaroValor* lvarovalor;     /* Lista de variables o valores. */

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    LlamadaFuncion(Identificador*, LVaroValor*);
    LlamadaFuncion(): tipo(TypeError::Instance()), id(0),lvarovalor(0) {}
    ~LlamadaFuncion();
    TypeS* get_tipo(){ return tipo; }
    
    void show(std::string);

    std::list<GuavaQuads*>* generar_quads();

};

/**
 * Clase que determina las instrucciones Continue/Break.
 */
class ContinueBreak: public Instruccion{
public:
    GuavaQuads* begin;
    TypeS* tipo;
    int line;
    int column;
    int instruccion; // 0 es Continue , 1 es break

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
    ContinueBreak( int t): instruccion(t), tipo(TypeVoid::Instance()){ }
    ~ContinueBreak(){ }
    void show(std::string s){
        std::ostringstream convert; 
        convert << line;
        std::string linea = convert.str();
        convert.flush();
        convert << column;
        std::string columna = convert.str();
        if (instruccion == 0){
            std::cout << s << "Continue, linea: " << linea << ", columna: " << columna << "\n";
        } else{
            std::cout << s << "Break , linea: " << linea << ", columna: " << columna << "\n";
        }
    }
    TypeS* get_tipo() { return tipo; }

    bool continue_break(){ return true; }

    std::list<GuavaQuads*>* generar_quads(){
        GuavaQuads* go_to;
        if (tipo == 0){
            go_to = new GuavaGoTo(begin);
        }else {
            go_to = new GuavaGoTo(next);
        }
        std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>; 
        result->push_back(go_to);
        GuavaQuads* comentario = new GuavaComment("CONTINUE/BREAK",line,column);
        result->push_front(comentario);
        return result;
    }

    void set_begin(GuavaQuads* begin_){
        begin = begin_;
    }
};

/**
 * Clase para lista de parametros.
 */
class LParam{
public:
    std::list<std::pair<TypeS*, Identificador*>> lParam;
    int line;
    int column;
    std::list<TypeS*> lTipos;

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }
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
    int line;
    int column;
    Identificador* identificador;
    LParam* parametros; 
    BloqueDeclare* declaraciones;
    ListaInstrucciones* listaI;
    GuavaQuads* label;

    void set_line_column(int l, int c){
        line = l;
        column = c;
    }

    Funcion();
    Funcion(TypeS*, Identificador*, LParam*, BloqueDeclare* ,ListaInstrucciones*);    
    ~Funcion();

    void show(std::string);

    /**
     * Genera los quads para una funcion.
     * Este es el unico momento en que se usa GuavaLabel con un identificador.
     **/
    std::list<GuavaQuads*>* generar_quads(){
        label = new GuavaLabel(identificador->identificador);
        std::list<GuavaQuads*>* quads =  listaI->generar_quads();
        quads->push_front(label);
        GuavaQuads* comentario = new GuavaComment("FUNCION",line,column);
        quads->push_front(comentario);
        return quads;
    }
};

/**
 * Clase para la lista de funciones.
 */
class LFunciones{
public:
    Funcion* funcion;   /* Funcion */
    LFunciones* lista; /* Lista de funciones */
    std::list<GuavaQuads*>* lista_quads; /* Lista de quads */
    
    LFunciones();
    LFunciones(Funcion*, LFunciones*);
    ~LFunciones();
    
    void show(std::string);

    std::list<GuavaQuads*>* generar_quads(){
        std::list<GuavaQuads*>* result = 0;
        std::list<GuavaQuads*>* code = 0;
        if (funcion != 0) result = funcion->generar_quads();
        if (result == 0){
            result = new std::list<GuavaQuads*>();
        }
        if (lista != 0) code = lista->generar_quads();
        if (code != 0) result->splice(result->end(),*code);
        return result;
    }
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
    std::list<ProtoExpID*> lista; //Esto es una lista de ExpID
public:
    LAccesoAtributos(){}

    LAccesoAtributos(ProtoExpID* i){
        lista.push_front(i);
    }

    LAccesoAtributos(std::list<ProtoExpID*> l):lista(l){
    }
    

    ~LAccesoAtributos(){}

    void append(ProtoExpID* i){
        lista.push_front(i);
    }
    
    std::list<ProtoExpID*> get_list(){
        return lista;
    }

    void show(std::string s){
        for ( std::list<ProtoExpID*>::iterator it = lista.begin();
              it != lista.end();
              ++it
            ){
                std::cout << s << "Lista de Acceso Atributos: ";
                Exp* id = *it;
                id->show(s+ "  ");
            }
    }
};

class ExpIdentificador: public ExpID{
public:
    ExpIdentificador(Identificador* id);
    ExpIdentificador(ExpID* exp_,Identificador* id);
    ~ExpIdentificador(){}

    virtual std::list<GuavaQuads*>* generar_quads();
    
};

class ExpIDLCorchetes: public ExpID{
public:
    ExpIDLCorchetes(Identificador* id, LCorchetesExp* lce );
    ExpIDLCorchetes(ExpID*,Identificador*, LCorchetesExp* );
    ~ExpIDLCorchetes(){}
    virtual std::list<GuavaQuads*>* generar_quads();
};
