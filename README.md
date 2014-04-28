Compilador para el lenguaje de programacion Guava desarrollado para la cadena de lenguajes.
Actualmente tiene un lexer, parser que construye una tabla de simbolos y todo lo necesario para realizar un arbol (aunque aun no lo hace).
Para la compilacion de este es necesario make, gcc (4.7 en adelante), bison (2.6) y flex. Una vez compilado todo tan solo es necesario correr ./guava [nombredelprograma]


Para mayor informacion con respecto al
lenguaje revisar la pagina de https://github.com/RubenSerradas/DocumentoDise-oLenguaje .

¿Que hace falta?

* Verificacion de tipos
* AST
* Contar el offset de todos los tipos
* Documentacion (falta documentar mediante al estilo doxygen)
* Mejoras en la impresion de errores.

Bugs:


Estado actual:

Estamos realizando el codigo para el AST, verificador de tipos y contador de offsets.
Cada variable va a tener un apuntador al tipo correspondiente que se encuentra en la tabla de simbolos,
como los tipos basicos y los definidos por el usuario son unicos entonces se tiene una manera muy sencilla
de compararlos (tan solo es necesario verificar que las direcciones sean las mismas). El que seria distinto es el
de los arreglos pues tendria que verificarse su Tipo + El tamaño y dimensiones de este.

