/*
 * =====================================================================================
 *
 *       Filename:  GetReg.hh
 *
 *    Description:  Headers de la clase para las funciones de obtención de registros.
 *
 *        Version:  1.0
 *        Created:  14/11/14 17:27:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo. 
 *   Organization:  USB
 *
 * =====================================================================================
 */
# ifndef GET_REG_HH
# define GET_REG_HH
# include "GuavaQuads.hh"
# include "GuavaDescriptor.hh"
# include <list>
# include <string>

/** 
 * Clase que contiene las funciones para obtener registros.
 */
class RegisterAllocator{
protected:
    GuavaDescTable* tabla_reg; /* Tabla de descriptores para registros. */
    Generator* gen;
    list<GuavaDescriptor*> getReg_general(GuavaQuads* i);
    list<GuavaDescriptor*> getReg_array(GuavaQuads* i);
    list<GuavaDescriptor*> getReg_copy(GuavaQuads* i);
    list<GuavaDescriptor*> getReg_if(GuavaQuads* i);
public:

    /** 
     * Constructor.
     * @param tabla_ Tabla de descriptores.
     * @param gen_ Escritor de archivos.
     */
    RegisterAllocator(GuavaDescTable* tabla_, Generator* gen_): tabla_reg(tabla_), gen(gen_){}

    ~RegisterAllocator(){}

    /**
     * Retorna una lista con registros para que la instruccion i la use.
     * @param i Instruccion
     */
    list<GuavaDescriptor*> getReg(GuavaQuads* i);

    /**
     * Funcion estatica que retornauna lista con registros para que la instruccion i la use.
     *
     * @param i Instruccion
     * @param tabla_ Tabla de descriptores.
     * @param gen_ Escritor de archivos.
     *
     * */
    static list<GuavaDescriptor*> getReg(GuavaQuads* i , GuavaDescTable* tabla, Generator* gen); 

};

#endif //GET_REG_HH
