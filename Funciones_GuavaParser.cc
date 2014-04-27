/*Comportamientos recurrentes observados*/

//Insertar en una lista (Simple)

/* Lo que varia en este procedimiento son los argumentos $x */
std::list<Identificador> l = $4->get_list();
std::list<Identificador>::iterator it = l.begin();
int scop = driver.tablaSimbolos.currentScope();
for(it; it != l.end(); ++it) {
    Symbol *tmp = driver.tablaSimbolos.simple_lookup(it->identificador);
    if(tmp != 0) {
        std::stringstream linea, columna;
        std::string msg ("variable name '");
        msg += it->identificador;
        msg += "' already used in line: ";
        linea << tmp->line;
        msg += linea.str();
        msg += " column: ";
        columna << tmp->column;
        msg += columna.str();
        driver.error(yylloc,msg);
        error_state = 1;
        continue;
    }
    int line = it->line;
    int column = it->column;
    driver.tablaSimbolos.insert(it->identificador, std::string("reference"),scop,$2->tipo,line,column);
}

//Insertar en una lista (Arreglos)

/* Lo que varia en este procedimineto son los argumentos $x */
std::list<std::pair<Identificador, LCorchetes>> l = $3->get_list();
std::list<std::pair<Identificador, LCorchetes>>::iterator it = l.begin();
int scop = driver.tablaSimbolos.currentScope();
for(it; it != l.end(); ++it) {
    std::pair<Identificador, LCorchetes> par (*it);
    Symbol *tmp = driver.tablaSimbolos.simple_lookup(par.first.identificador);
    if(tmp != 0) {
        std::stringstream linea, columna;
        std::string msg("variable name'");
        msg += par.first.identificador;
        msg += "' already used in line: ";
        linea << tmp->line;
        msg += linea.str();
        msg += " column: ";
        columna << tmp->column;
        msg += columna.str();
        driver.error(yylloc,msg);
        error_state = 1;
        continue;
    }
    int size (par.second.lista.size());
    int *arreglo = new int[par.second.lista.size()];
    std::list<Integer>::iterator itInt (par.second.lista.begin());
    for(int i=0; i!=size; i++) {
        arreglo[i] = itInt->getValor();
        ++itInt;
    }
    int line = par.first.line;
    int column = par.first.column;
    driver.tablaSimbolos.insert(par.first.identificador,std::string("array"),scop,$1->tipo,line,column,arreglo,size);
}


