Lenguaje de programacion Guava. Por ahora solo tiene lexer, un parser primitivo y ciertas funciones auxiliares.
Para la compilacion de este es necesario make, gcc, bison y flex. Para mayor informacion con respecto al
lenguaje revisar la pagina de https://github.com/RubenSerradas/DocumentoDise-oLenguaje .

¿Que hace falta para la primera entrega? 

-Realizar los nodos del arbol en GuavaTree.hh como clases (por ahora solo hice BloquePrincipal).

-Agregar GuavaSymTable.hh y GuavaTree.hh en el makefile para que pueda ser usado.

-Reglas para insertar los simbolos en la tabla.

-Reglas para hacer el ast.

-Poner al lado de cada token el nombre de esta manera ASSIGN ":=" para que salga mejor en los mensajes de errores o encontrar
una manera de cambiar un TOKEN por un mensaje token chevere.

-Revisar el error reduce/shift que nos aparece cuando compilamos.

-Mayor cantidad de programas de ejemplos para probar (seria bueno uno que usara records o uniones).

¿Que hace alguien buena onda?

-Compilar antes de hacer push para ver si las cosas van bien.

-Darse cuenta que el nombre GuavaTree.hh es gracioso porque es como un arbol de guayabas.

-Comentar de esta manera

  /**
   * Se ve cool y con doxygen se puede sacar la documentacion mejor.
   */

No parece tan dificil lo que nos falta pero es largo y se necesitan varias pruebas.
