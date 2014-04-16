/*
 * =====================================================================================
 *
 *       Filename:  Symbol.hh
 *
 *    Description:  Symbol.
 *
 *        Version:  1.0
 *        Created:  12/03/14 14:25:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include <map>
#include "Types.hh"


typedef union {
    float* real;
    std::string* str;
    int* integer;
    char* ch;
    bool* boolean;   
} Referencia;

typedef union {
    float real;
    int integer;
    char ch;
    std::string * str;
    bool boolean;
    
} ValorUnion;

typedef union {
    ValorUnion valor;
    Referencia referencia;
} ValorSimbolo;

/** 
 * Clase simbolo de Guava.
 */
class Symbol{
public:
    std::string sym_name;   /* Nombre del simbolo */
    std::string sym_catg;   /* Categoria del simbolo */
    int scope;              /* Identificador del scope del simbolo */
    std::string type;       /* DEPRECATED */ 

    int *arreglo;           /* Dimensiones del arreglo */
    int size;               /* Tamaño del arreglo */
    int fieldScope;         /* Alcance de los simbolos de una estructura, union o funcion */
    int line;               /* Linea en la que fue encontrado el simbolo */ 
    int column;             /* Columna en la que fue encontrado el simbolo */ 
    ValorSimbolo contenido; /* Contenido del simbolo */
    bool referencia;        /* Nos dice si el simbolo es una referencia o no. */  
    bool symbol_type;       /* Nos dice si el simbolo es un tipo */

    TypeS* true_type;
    std::map<std::string, std::list<Symbol> >::iterator type_pointer; 

    /**
     * Constructor de la clase Symbol para variable.
     */
    Symbol(std::string name, std::string catg, int scop, std::string type, int linea, int columna);

    /**
     * Constructor para arreglo 
     */
    Symbol(std::string, std::string, int, std::string,int,int, int*,int); 
   
    /**
     * Constructor para estructuras.
     */
    Symbol(std::string,std::string,int,std::string,int,int,int);

    /**
     * Constructor para tipos
     */
    Symbol(std::string,std::string,int,TypeS*);

    Symbol();

    /**
     * Destructor de la clase Symbol.
     */
    ~Symbol();

    /**
     * Se utiliza el operador == para comparar. 
     */
    bool operator==(Symbol b);

    /** 
     * Compara nombres y alcance 
     */
    bool compare(std::string s, int sc);
    
    /**
     * Muestra lo que tiene el Symbol. 
     */
    virtual void show(std::string);
};


