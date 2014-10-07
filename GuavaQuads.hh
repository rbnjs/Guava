/*
 * =====================================================================================
 *
 *       Filename:  GuavaQuads.hh
 *
 *    Description:  Quads para el lenguaje.
 *
 *        Version:  1.0
 *        Created:  16/09/14 10:20:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include <string>
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream
#include "GuavaSymTable.hh"


class NewTemp{
private:
    int* secuencia_temporales;
    TypeS* tipo;
    int line, column;
    GuavaSymTable* tabla;
public:

    NewTemp(int* secuencia, TypeS* tipo_, int line_,int column_, GuavaSymTable* table_):
        secuencia_temporales(secuencia),tipo(tipo_),line(line_),column(column_),tabla(table_){}

    ~NewTemp(){}


    void set_tipo(TypeS* tipo_){
        tipo = tipo_;
    }

    /**
     * Funcion que dado una instancia de la clase Tipo
     * y la tabla de simbolos retorna la direccion en donde esta el tipo.
     */
    Symbol* buscar_tipo_new_temp(std::string str){
        Symbol *s = tabla->lookup(str);
        if (s == 0) return 0;
        if (s->true_type == 0) return 0;
        return s;
    }

    /**
     * Funcion que coloca una variable temporal en la tabla de simbolos
     * y retorna esta misma.
     * No es necesario calcular el offset de las variables temporales
     * @param d: Clase manejadora GuavaDriver
     * @param loc: location del yyparse
     * @param tipo: tipo del temp
     */
    Symbol* newtemp(){
        int scope;
        std::ostringstream convert;
        scope = tabla->currentScope();
        if (tipo == 0) return 0;

        convert << *secuencia_temporales;
        std::string nombre_t =  "_t" + convert.str(); //El nombre de las variables sera _tn, siendo n un numero unico.
        *secuencia_temporales += 1;

        Symbol* nuevo;
    
        if (!tipo->is_array() && !tipo->is_structure()){
            Symbol *p= buscar_tipo_new_temp(tipo->get_name());
            if (p == 0) {
                return 0;
            }
            nuevo = new Symbol(nombre_t, std::string("temporal"),scope,p,line,column,0);
        } else{
            nuevo = new Symbol (nombre_t, std::string("temporal"),scope,tipo, line,column, 0);
        }

        return nuevo;
    }
};


class GuavaQuads{
private:
    std::string op;
public:
    GuavaQuads(std::string op_): op(op_){}
    ~GuavaQuads(){}

    /**
     * Getters y setters.
     */
    std::string get_op(){ return op; }
    void set_op(std::string s){
        op = s;
    }

    /** 
     * Generador
     */
    virtual std::string gen(){
        return "";
    }

    virtual bool fall(){ return false; }

};

/**
 * Clase que representa un Quad para una expresion
 */
class GuavaQuadsExp:public GuavaQuads{
protected:
    SimpleSymbol* arg1 = 0;
    SimpleSymbol* arg2 = 0;
    SimpleSymbol* result = 0;
public: 
    /**
     * Constructor de la clase
     * @param op_ Operando
     * @param arg1_ Argumento 1
     * @param arg2_ Argumento 2
     * @param result_ Resultado
     */
    GuavaQuadsExp(std::string op_, SimpleSymbol* arg1_, SimpleSymbol* arg2_, SimpleSymbol* result_): GuavaQuads(op_), arg1(arg1_), arg2(arg2_), result(result_){}
    /**
     * Destructor de la clase
     */
    ~GuavaQuadsExp(){}

    /**
     * Getters de la clase
     */
    SimpleSymbol* get_arg1()  { return arg1; }
    SimpleSymbol* get_arg2()  { return arg2; }
    SimpleSymbol* get_result(){ return result; }

    /**
     * Funcion que genera codigo a partir de un Quad
     * El generador muestra el codigo de esta manera:
     * resultado := arg1 op arg2 (dos argumentos)
     * resultado := op arg1 (un argumentos)
     */
    virtual std::string gen(){
        std::string code ("");
        //Caso Operaciones Binarias
        if (arg2 != 0){
            //Acceso a elementos de arreglo, base pointer.
            if (this->get_op().compare(std::string("[]")) == 0) {
                code += result->sym_name + ":=" + arg1->sym_name + "[" + arg2->sym_name + "]";
            }
            else {
                code += result->sym_name + ":=" + arg1->sym_name + this->get_op() + arg2->sym_name;
            }
        //Caso Operaciones Unarias
        } else {
            if (this->get_op().compare(std::string(":=")) == 0) {
                code += result->sym_name + ":=" + arg1->sym_name;
            }
            // Menos unario
            if (this->get_op().compare(std::string("uminus")) == 0) {
                code += result->sym_name + ":=-" + arg1->sym_name;
            }
            // Post incremento
            if (this->get_op().compare(std::string("pincrease")) == 0) {
                code += result->sym_name + ":=" + arg1->sym_name + "++";
            }
            // Post decremento
            if (this->get_op().compare(std::string("pdecrease")) == 0) {
                code += result->sym_name + ":=" + arg1->sym_name + "--";
            }
        }
        code += "\n";
        return code;
    }
};

/**  
 * Clase que representa un label.
 */
class GuavaLabel: public GuavaQuads{
public:
    /**
     * Constructor para GuavaLabel.
     * @param label Label que sera guardado en op.
     */
    GuavaLabel(std::string label): GuavaQuads(label){}

    GuavaLabel();

    ~GuavaLabel(){}

    virtual std::string gen(){
        return (this->get_op() + ":\n");
    }
};
/**
 * Clase que representa Fall
 */
class GuavaFall: public GuavaLabel{
public:

    GuavaFall(): GuavaLabel(){}

    ~GuavaFall(){}

    virtual bool fall(){ return true; } 
};

/** 
 * Clase que representa un comentario.
 */
class GuavaComment: public GuavaQuads{
public: 
    int line;
    int column;
    /**
     * Constructor del comentario
     */
    GuavaComment(std::string comment):GuavaQuads(comment){}
    GuavaComment(std::string comment, int line_, int column_):GuavaQuads(comment),line(line_),column(column_){}
    ~GuavaComment(){}

    
    virtual std::string gen(){
        std::ostringstream convert_l,convert_c;
        convert_l << line; 
        convert_c << column;
        std::string comment = "#" + this->get_op() + ", line: " + convert_l.str() + "column: " + convert_c.str() +  "\n";
        return comment;
    }
};

class GuavaGoTo:public GuavaQuads{
public:
    SimpleSymbol* go_to;
    GuavaGoTo(Symbol* label): GuavaQuads("goto"), go_to(label){}
    GuavaGoTo(GuavaQuads* label): GuavaQuads("goto"){
        go_to = new SimpleSymbol(label->get_op());
    }
    ~GuavaGoTo(){}

    virtual std::string gen(){
        return "goto " + go_to->sym_name; 
    }
};
/** 
 * Clase que represena un If dentro 
 * de nuestro lenguaje intermedio.
 */
class GuavaQuadsIf:public GuavaQuadsExp{
public:

    /** 
     * Constructores para la clase GuavaQuadsIf
     *
     * Se puede colocar el GuavaLabel para mayor comodidad y este se transforma en un SimpleSymbol
     *
     * @param op_ Operacion con la que se va a comparar (>, <, = ...)
     * @param arg1_ Argumento 1. Este seria el addr de la expresion1
     * @param arg2_ Argumento 2. Este seria el addr de la expresion2
     * @param result_ Label a donde va a saltar.
     */ 
    GuavaQuadsIf(std::string op_, SimpleSymbol* arg1_, SimpleSymbol* arg2_, SimpleSymbol* result_): GuavaQuadsExp(op_,arg1_,arg2_,result_){}
    GuavaQuadsIf(std::string op_, SimpleSymbol* arg1_, SimpleSymbol* arg2_, GuavaQuads* result_): 
                            GuavaQuadsExp(op_,arg1_,arg2_,new SimpleSymbol(result_->get_op())){}
    ~GuavaQuadsIf(){}

    std::string gen(){
        std::string code ("");
        if (arg2!= 0) code += "if " + arg1->sym_name+ " " + this->get_op() + " " + arg2->sym_name+ " goto " + result->sym_name;
        else code += "if " + arg1->sym_name+ " " + " goto " + result->sym_name;
        return code;
    }
};

/** 
 * Clase que represena un If dentro 
 * de nuestro lenguaje intermedio.
 */
class GuavaQuadsIfNot:public GuavaQuadsExp{
public:

    /** 
     * Constructores para la clase GuavaQuadsIf
     *
     * Se puede colocar el GuavaLabel para mayor comodidad y este se transforma en un SimpleSymbol
     *
     * @param op_ Operacion con la que se va a comparar (>, <, = ...)
     * @param arg1_ Argumento 1. Este seria el addr de la expresion1
     * @param arg2_ Argumento 2. Este seria el addr de la expresion2
     * @param result_ Label a donde va a saltar.
     */ 
    GuavaQuadsIfNot(std::string op_, SimpleSymbol* arg1_, SimpleSymbol* arg2_, SimpleSymbol* result_): GuavaQuadsExp(op_,arg1_,arg2_,result_){}
    GuavaQuadsIfNot(std::string op_, SimpleSymbol* arg1_, SimpleSymbol* arg2_, GuavaQuads* result_): 
                            GuavaQuadsExp(op_,arg1_,arg2_,new SimpleSymbol(result_->get_op())){}
    ~GuavaQuadsIfNot(){}

    std::string gen(){
        std::string code ("");
        if (arg2!= 0) code += "ifnot " + arg1->sym_name+ " " + this->get_op() + " " + arg2->sym_name+ " goto " + result->sym_name;
        else code += "ifnot " + arg1->sym_name+ " " + " goto " + result->sym_name;
        return code;
    }
};

class GuavaParam: public GuavaQuads{
public:
    SimpleSymbol* addr;
    GuavaParam(SimpleSymbol* addr_): GuavaQuads(std::string("param")), addr(addr_){}
    ~GuavaParam(){}

    std::string gen(){
        std::string result ("param ");
        result += addr->sym_name;
        return result;
    }
};

class GuavaCall: public GuavaQuadsExp{
public:
    GuavaCall(std::string id, SimpleSymbol* arg, SimpleSymbol* addr): GuavaQuadsExp(id,arg,0,addr){}
    ~GuavaCall(){}
    
    std::string gen(){
        std::string result ("call ");
        result += this->get_op();
        result += ", " + this->get_arg1()->sym_name;
        return result; 
    }
};

class GuavaEntradaSalida:public GuavaQuadsExp{
public:
    GuavaEntradaSalida(std::string op, SimpleSymbol* arg, SimpleSymbol* addr = 0): GuavaQuadsExp(op,arg,0,addr){}
    ~GuavaEntradaSalida(){}
    std::string gen(){
        std::string result =this->get_op();
        if (this->get_result() == 0){
            result += this->get_arg1()->sym_name + "\n";
        }else{
            result += this->get_arg1()->sym_name + " " + this->get_result()->sym_name + "\n";
        }
        return result;
    }
};
