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
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
/** 
 * Clase simbolo de Guava.
 */
class Symbol{
public:
    std::string sym_name; /* Nombre del simbolo */
    std::string sym_catg; /* Categoria del simbolo */
    int scope;            /* Identificador del scope del simbolo */
    Symbol *type;         /* Apuntador la descripcion del tipo del simbolo */

    /**
     * Constructor de la clase Symbol.
     */
    Symbol(std::string name, std::string catg, int scop, Symbol s);

    /**
     * Constructor de la clase Symbol.
     */
    Symbol(std::string name, std::string catg, int scop);

    /**
     * Destructor de la clase Symbol.
     * */
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
    std::string show();
};

