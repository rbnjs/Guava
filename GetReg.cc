/*
 * =====================================================================================
 *
 *       Filename:  GetReg.cc
 *
 *    Description:  Implementacion de algoritmo de obtencion de registros.
 *
 *        Version:  1.0
 *        Created:  14/11/14 20:21:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo. 
 *   Organization:  USB. 
 *
 * =====================================================================================
 */

#include "GetReg.hh"
#include "GuavaTemplates.hh"
#include <climits>

using namespace std;


/** 
 * Revisa la lista de registros a considerar viendo si sus elementos tienen usos posteriores. 
 * @param e Expresion 
 * @param s Simbolo a considerar 
 * @param reg Registros a considerar
 * @return GuavaDescriptor* Apuntador a registro que se puede usar.
 */
GuavaDescriptor* RegisterAllocator::subsequent_uses(list<GuavaDescriptor*> reg,GuavaQuadsExp* e, Symbol* s){
    for (list<GuavaDescriptor*>::iterator it_list = reg.begin(); it_list != reg.end(); ++it_list){
        set<SimpleSymbol*>::iterator it_set;
        for ( it_set = (*it_list)->begin() ; it_set != (*it_list)->end(); ++it_set){
            if ( s != *it_set && e->uso(*it_set) != -1) break;
        }
        if (it_set == (*it_list)->end()) return *it_list;
    }
    return 0;
}

/** 
 * Revisa la lista de registros a considerar para ver si v solo se encuentra en result. 
 *
 * @param e Expresion 
 * @param s Simbolo a considerar 
 * @param reg Registros a considerar
 * @return GuavaDescriptor* Apuntador a registro que se puede usar.
 */
GuavaDescriptor* RegisterAllocator::only_in_result(list<GuavaDescriptor*> reg,GuavaQuadsExp* e, Symbol* s){
    for (list<GuavaDescriptor*>::iterator it_list = reg.begin(); it_list != reg.end(); ++it_list){
        set<SimpleSymbol*>::iterator it_set;
        for (it_set = (*it_list)->begin() ; it_set != (*it_list)->end(); ++it_set){
            if ( s == *it_set) continue;
            if (*it_set != e->get_result()) break;
        }
        if (it_set == (*it_list)->end()) return *it_list;
    }
    return 0;
}

/** 
 * Revisa la lista de registros a considerar para ver si los valores distintos de s se encuentran en otro lugar.. 
 *
 * @param e Expresion 
 * @param s Simbolo a considerar 
 * @param reg Registros a considerar
 * @return GuavaDescriptor* Apuntador a registro que se puede usar.
 */
GuavaDescriptor* RegisterAllocator::available_in_another_location(list<GuavaDescriptor*> reg,GuavaQuadsExp* e, Symbol* s){
    for (list<GuavaDescriptor*>::iterator it_list = reg.begin(); it_list != reg.end(); ++it_list){
        for (set<SimpleSymbol*>::iterator it_set = (*it_list)->begin() ; it_set != (*it_list)->end(); ++it_set){
            if (s == *it_set) continue;
            if (tabla_reg->available_in_other_location(*it_set,*it_list) || tabla_var->available_in_other_location(*it_set,*it_list)) return *it_list;
        }
    }
    return 0;
}

/** 
 * Caso convencional de reciclaje de posibles registros.
 *
 * El descriptor de registro tiene uno o mas valores v asignados, para ellos consideramos:
 *   Si v está disponible en otra ubicación, R es seguro.
 *   Si v = x y x no es uno de los operandos, R es seguro.
 *   Si v no tiene usos posteriores, R es seguro.
 *   Si después de los pasos 1 a 3 R aún no es seguro, se emite ST v, R – se cuenta como un spill.
 *
 * @param e Expresion a considerar el reciclaje.
 * @param s Simbolo que se quiere meter en el registro.
 * @return reg Registro que ya se puede usar. 
 */
GuavaDescriptor* RegisterAllocator::recycle(GuavaQuadsExp* e,Symbol* s){
    list<GuavaDescriptor*> registros = tabla_reg->get_desc();
    GuavaDescriptor* result;
    if ((result = this->subsequent_uses(registros,e,s)) != 0) return result;
    if ((result = this->only_in_result(registros,e,s)) != 0) return result;
    if ((result = this->available_in_another_location(registros,e,s)) != 0) return result;
    // Todo falla. Voy a hacer spill.
    return this->spill();
}


/** 
 * Realiza un spill en un descriptor de registro asociado a variables globales si es posible.
 * @return GuavaDescriptor* Retorna un descriptor de registro si fue posible y 0 si no fue posible realizar el spill.
 */
GuavaDescriptor* RegisterAllocator::global_spill(){
    list<GuavaDescriptor*> tmp;
    int min = tabla_reg->min_assoc();
    int min_global = INT_MAX;
    for ( std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla_reg->begin() ; it != tabla_reg->end(); ++it){
        if (it->second->todas_globales() && it->second->size() == min) {
            templates->store(it->second); //Guardo todas las variables a guardar aqui
            return it->second;
        } else if (it->second->todas_globales()){
            if (it->second->size() < min_global) min_global = it->second->size();
            tmp.push_back(it->second);
        }
    }
    for (list<GuavaDescriptor*>::iterator it = tmp.begin(); it != tmp.end() ; ++it){
        if ((*it)->size() == min_global){
            templates->store(*it); //Guardo las variables.
            return *it;
        }
    }
    return 0;
}

/** 
 * Realiza un spill en un descriptor de registro que tiene asociado variables locales y globales si es posible.
 * @return GuavaDescriptor* Retorna un descriptor de registro si fue posible y 0 si no fue posible realizar el spill.
 */
GuavaDescriptor* RegisterAllocator::local_spill(){
    list<GuavaDescriptor*> tmp;
    int min = tabla_reg->min_assoc();
    int min_global = INT_MAX;
    for ( std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla_reg->begin() ; it != tabla_reg->end(); ++it){
        if (it->second->locales_globales() && it->second->size() == min) {
            templates->store(it->second);
            return it->second;
        } else if (it->second->locales_globales()){
            if (it->second->size() < min_global) min_global = it->second->size();
            tmp.push_back(it->second);
        }
    }
    for (list<GuavaDescriptor*>::iterator it = tmp.begin(); it != tmp.end() ; ++it){
        if ((*it)->size() == min_global){
            templates->store(*it);
            return *it;
        }
    }
    return 0;
}

/** 
 * Realiza un spill en un descriptor de registro que tenga asociado variables locales, globales y temporales.
 *
 * Para esto elige el descriptor con menor numero de temporales. Luego va aumentando la pila y metiendo variables alli. 
 *
 * @return GuavaDescriptor* Retorna un descriptor de registro.
 */
GuavaDescriptor* RegisterAllocator::temp_spill(){
    list<GuavaDescriptor*> tmp;
    int min_temp = INT_MAX;
    //Busco aquel con el menor numero de temporales a hacer spill.
    for ( std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla_reg->begin() ; it != tabla_reg->end(); ++it){
        if (it->second->count_temp() < min_temp) min_temp = it->second->count_temp();
    }

    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla_reg->begin() ; it != tabla_reg->end(); ++it){
        if (it->second->count_temp() == min_temp){
            templates->store_spill(it->second);
            return it->second;
        }
    }
    return 0;
}

/** 
 * Realiza el spill en un descriptor de registro.
 *
 * Primero considero que el descriptor solo tenga asociada variables globales, si es asi este es el mejor.
 * En el segundo caso, considero al que tenga combinaciones de variables globales y locales.
 * Peor caso es el que tenga variables locales, globales y temporales.
 * @return result Retorna un apuntador al Descriptor de arreglos.
 */
GuavaDescriptor* RegisterAllocator::spill(){
    GuavaDescriptor* result;

    if ((result = this->global_spill()) != 0){
        return result;
    }

    if ((result = this->local_spill()) != 0){
        return result;
    }

    return this->temp_spill();
}

/** 
 * Caso para expresiones generales.
 *
 * Para x := y + z
 * Si algun registro solo contiene a x, es la mejor opcion.
 * Si y no tiene usos posteriores, la mejor opcion es un registro que solo contenga a y. Lo mismo para z.
 * En caso que no pase nada de eso. Hay que obtener registros de la manera convencional.
 *
 * @param i Instruccion en codigo de tres direcciones. Este debe ser de tipo GuavaQuadsExp.
 * @return result Lista con registros disponibles para su uso.
 */
list<GuavaDescriptor*> RegisterAllocator::getReg_general(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    GuavaQuadsExp* instruccion = (GuavaQuadsExp*) i;
    GuavaDescriptor* tmp;

    list<SimpleSymbol*> args = instruccion->get_args();

    for (list<SimpleSymbol*>::iterator it = args.begin(); it != args.end() ; ++it){
        if ( instruccion->get_result() == *it && (tmp = tabla_reg->find_only_one(*it)) != 0){
            //Caso Simple. Cuando esta en un registro y es el resultado.
            result.push_back(tmp);
        } else if ( instruccion->uso(*it) != -1 && (tmp = tabla_reg->find_only_one(*it)) != 0 ){
            //Caso Simple. Cuando esta en un registro y no tiene proximos usos.
            result.push_back(tmp); 
        }else if ((tmp = tabla_reg->find_empty()) != 0){
            //Caso Simple. Hay registros disponibles.
            if (instruccion->get_result() != *it){
                templates->load(tmp,*it);
            }
            result.push_back(tmp);
        }else{
            // Reciclaje. Caso Convencional.
            tmp = this->recycle(instruccion,instruccion->get_result());
            result.push_back(tmp);
        }
    }

    return result;
}

/** 
 * Retorna una lista con registros para la copia x = y.
 *
 * Aqui se asume que getReg va a regresar un lista con el mismo registro para x y y.
 *
 * @param i Codigo de tres direcciones.
 */
list<GuavaDescriptor*> RegisterAllocator::getReg_copy(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    GuavaQuadsExp* instruccion = (GuavaQuadsExp*) i;
    list<SimpleSymbol*> args = i->get_args(); 
    GuavaDescriptor* tmp;
    if (args.size() != 2) return result;

    if ( instruccion->uso(args.back()) != -1 && (tmp = tabla_reg->find_only_one(args.back())) != 0 ){
        //Caso Simple. Cuando esta en un registro y no tiene proximos usos.
        result.push_back(tmp); 
    }else if ( (tmp = tabla_reg->find_empty()) != 0){
        //Caso Simple. Hay registros disponibles.
        templates->load(tmp,args.back());
        result.push_back(tmp);
    }else{
        // Reciclaje. Caso Convencional.
        tmp = this->recycle(instruccion,instruccion->get_result());
        result.push_back(tmp);
    }
    result.push_back(tmp);
    return result;
}

/** 
 * Algoritmo de GetReg.
 */
list<GuavaDescriptor*> RegisterAllocator::getReg(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    if (i->is_guava_exp()){
        if (i->is_general_exp()){
            result = this->getReg_general(i);
        }else if (i->get_op().compare(std::string(":=")) == 0){
                result = this->getReg_copy(i);
        }
    }
    return result;
}

/** 
 * Algoritmo de GetReg estatico.
 */
list<GuavaDescriptor*> RegisterAllocator::getReg(GuavaQuads* i , GuavaDescTable* tabla_registro,
                                                 GuavaDescTable* tabla_var, GuavaGenerator* gen, GuavaTemplates* template_){
    RegisterAllocator tmp (tabla_registro,tabla_var,gen,template_);
    return tmp.getReg(i);
}

