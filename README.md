Compilador para el lenguaje de programacion Guava desarrollado para la cadena de lenguajes.
Actualmente tiene un lexer, parser que construye una tabla de simbolos y todo lo necesario para realizar un arbol (aunque aun no lo hace).
Para la compilacion de este es necesario make, gcc, bison (2.6) y flex. Una vez compilado todo tan solo es necesario correr ./guava [nombredelprograma]


Para mayor informacion con respecto al
lenguaje revisar la pagina de https://github.com/RubenSerradas/DocumentoDise-oLenguaje .

¿Que hace falta?

* Documentacion (falta documentar mediante al estilo doxygen)
* AST
* Mejoras en la impresion de errores.
* Verificacion de tipos, generacion de codigo intermedio y todo lo demas que nos van a enseñar.

Bugs:

* Segmentation fault en expresiones muy complicadas. Esto es porque tenemos un arbol incompleto haciendose.

Estado actual: Funcional exceptuando los bugs