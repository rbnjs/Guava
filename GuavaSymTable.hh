/*
 * =====================================================================================
 *
 *       Filename:  GuavaSymTable.hh
 *
 *    Description:  Clase de tabla de simbolo para Guava.
 *
 *        Version:  1.0
 *        Created:  05/03/14 13:50:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization: USB 
 *
 * =====================================================================================
 */
//Symbol: Clase que define una entrada de la tabla de simbolos.
class Symbol{
public:
    Symbol();          /* Constructor de la clase */
    Symbol(std::string, std::string, int, S)
    virtual ~Symbol(); /* Destructor */

    std::string sym_name; /* Nombre del simbolo */
    std::string sym_catg; /* Categoria del simbolo */
    int scope;            /* Identificador del scope del simbolo */
    Symbol *type;         /* Apuntador la descripcion del tipo del simbolo */

    /* Funcion auxiliar para realizar comparaciones entre simbolos.
     * return: 0 si son iguales en nombre y scope.
     *         1 si son diferentes.
     */
    int compare(Symbol a, Symbol b) {
        if(a.sym_name.compare(b.sym_name) == 0 && a.scope == b.scope) {
            return 0;
        }
        return 1;
    }
};

class GuavaSymTable{
public:
    GuavaSymTable(); /* Constructor de la clase */
    virtual ~GuavaSymTable(); /*  Destructor */

    void insert(Symbol elem);              /* Inserta un simbolo a la tabla */
    void lookup(const std::string elem, int alcance);     /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    void enterScope();
    void exitScope();
    Symbol lookup(std::string elem, int alcance);     /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    void show();                                          /* Muestra la tabla */
private:
    std::stack<int> pila;
    std::map<std::string, std::list<Symbol>> tabla;
};

//insert: Inserta un simbolo en la tabla de simbolos.
void GuavaSymTable::insert(Symbol elem) {
    //Lista de colisiones, en caso de haber.
    std::map<std::string, std::list<Symbol>>::iterator sym_list;

    // Se verifica si el simbolo ya existe en la tabla
    if(tabla.count(elem.sym_name)>0) {
        sym_list = tabla.find(elem.sym_name);
        for(std::list<Symbol>::iterator it=sym_list.begin();
            it != sym_list.end(); it++) {
            // Caso en el que el simbolo se encuentra en el mismo scope.
            if(elem.compare(it) == 0) {
                /* ERROR YA EL SIMBOLO EXISTE EN ESTE SCOPE */
            }
        }
        // Caso en el que el simbolo no existe en el scope, pero si en otros
        sym_list.push_back(elem);
    }
    // Caso en el que el simbolo no pertenece a la tabla.
    else {
        std::list<Symbol> empty_list;
        tabla.insert(std::pair<std::string, std::list<Symbol>> 
                     (elem.sym_name, empty_list));
    }
}

//lookup: Busca y asigna el scope del simbolo a ser evaluado.

//enter_scope: Entra en un nuevo scope y empila el numero identificador del mismo.

//exit_scope: Sale del scope y desempila el identificador.
