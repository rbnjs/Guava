Compilador para el lenguaje de programacion Guava desarrollado para la cadena de lenguajes.
Actualmente tiene un lexer, parser que construye una tabla de simbolos y el arbol.
Para la compilacion de este es necesario make, gcc (4.7 en adelante), bison (2.6) y flex. 
Una vez compilado todo tan solo es necesario correr ./guava -h y obtener las instrucciones.


Para mayor informacion con respecto al
lenguaje revisar la pagina de https://github.com/RubenSerradas/DocumentoDise-oLenguaje .

¿Que hace falta?

* Documentacion (tipo doxygen).
* Generar codigo intermedio. Falta las funciones gen (para cada clase) y newtemp()
* Seria bueno automatizar el testeo (Estoy pensando en Ruby)

Bugs:

* Revisar mejor la recuperacion de errores.

Estado actual:

Se esta mejorando el codigo y realizando el codigo intermedio.
