/*
 * Primer esqueleto de la tabla de simbolos y las funciones asociadas a esta.
 */

//Includes necesarios
#include <string>

//Tamano de la tabla de hash que describe la tabla de simbolos
#define TAM 500

//Estructura de tabla de simbolos
struct sym_tab {
  /* Campos de cada entrada a la tabla de simbolos, siguiendo la estructura
   * de una tabla de Leblanc-Cook
   */
  sd::string sym_name; //nombre del simbolo
  sd::string sym_catg; //categoria del simbolo {variable, funcion, etc.}
  int scope;           //identificador del scope (uno por cada bloque)
  sym_tab *type;       //apuntador a las entradas de la tabla que describan el
                       //tipo que representa el simbolo.
  /*Aqui no se si poner algun otro campo que describa la entrada */
  sym_tab *next;       //siguiente entrada por si existen colisiones.
};

//Estructura de la pila de scopes
struct scope_stack {
  int scope;         //numero del scope en el que se encuentra
  scope_stack *next; //apuntador al siguiente de la pila
};
typedef struct scope_stack scope_stack;

//Se define la pila de scopes
scope_stack *scopeStack = new scope_stack;

/*
 * Funciones inherentes a la pila. Incluye la funcion de busqueda necesaria
 * para el lookup de la tabla de simbolos.
 *
 */

// Push: Coloca el identificador del scope de primero en la pila.
scope_stack *push(int scope, scope_stack *stack) {
  scope_stack *element;
  
  element = new scope_stack;
  element->scope = scope;
  element->next = stack;

  return element;
}

// Pop: Elimina el primer elemento de la pila de scope. Esta operacion se
//      realiza cuando se sale de un alcanze determinado en el programa.
scope_stack *pop(scope_stack *stack) {
  scope_stack *element;

  element = stack->next;
  delete stack;

  return element;
}

// Top: Retorna el primer elemento de la pila, en este caso, el scope actual.
int top(scope_stack *stack) {
  return stack->scope;
}

// Search: Dado un 
