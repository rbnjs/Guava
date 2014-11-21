Compilador para el lenguaje de programacion Guava desarrollado para la cadena de lenguajes.
Actualmente tiene un lexer, parser que construye una tabla de simbolos y el arbol.
Para la compilacion de este es necesario make, gcc (4.7 en adelante), bison (2.6) y flex. 
Una vez compilado todo tan solo es necesario correr ./guava -h y obtener las instrucciones.

Para mayor informacion con respecto al
lenguaje revisar la pagina de https://github.com/RubenSerradas/DocumentoDise-oLenguaje .

Para obtener la documentación del lenguaje es necesario doxygen. Realizar make doc, el archivo
de documentacion se encuentrará en la carpeta html dentro de Documentacion.

¿Que hace falta?

* Plantillas de todas las instrucciones del codigo intermedio.
* Finalizar spill.
* Automatizar el testeo.
* Programas de ejemplo.

Bugs:

* Revisar bugs de errores en el codigo intermedio.

Estado actual:

Se esta mejorando el codigo y realizando el codigo intermedio.
