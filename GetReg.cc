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
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "GetReg.hh"

using namespace std;


list<GuavaDescriptor*> RegisterAllocator::getReg_general(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    return result;
}

list<GuavaDescriptor*> RegisterAllocator::getReg_array(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    return result;
}

list<GuavaDescriptor*> RegisterAllocator::getReg_copy(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    return result;
}

list<GuavaDescriptor*> RegisterAllocator::getReg_if(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    return result;
}


list<GuavaDescriptor*> RegisterAllocator::getReg(GuavaQuads* i){
    list<GuavaDescriptor*> result;
    if (i->is_guava_exp()){
        if (i->is_general_exp()){
            result = this->getReg_general(i);
        }else{
            if (i->get_op().compare(std::string("[]"))){
                result = this->getReg_array(i);
            } else{
                result = this->getReg_copy(i);
            }
        }
    }else if(i->is_if()){
       result = this->getReg_if(i); 
    }

    return result;
}

list<GuavaDescriptor*> RegisterAllocator::getReg(GuavaQuads* i , GuavaDescTable* tabla, Generator* gen){
    RegisterAllocator tmp (tabla,gen);
    return tmp.getReg(i);
}

