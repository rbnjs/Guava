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
# include "GuavaTemplates.hh"
# include <unordered_map>
# include <list>

/** 
 * Clase que contiene las funciones para obtener registros.
 */
class RegisterAllocator{
protected:
    GuavaDescTable* tabla_reg; /* Tabla de descriptores para registros. */
    GuavaDescTable* tabla_var; /* Tambien necesito una tabla de descriptores para variables */
    Generator* gen;            /* Clase que escribe en el archivo final */
    list<GuavaDescriptor*> getReg_general(GuavaQuads* i);
    list<GuavaDescriptor*> getReg_array(GuavaQuads* i);
    list<GuavaDescriptor*> getReg_copy(GuavaQuads* i);
    list<GuavaDescriptor*> getReg_if(GuavaQuads* i);
    GuavaDescriptor* recycle(GuavaQuadsExp* e,Symbol* s);
    GuavaDescriptor* subsequent_uses(list<GuavaDescriptor*> reg,GuavaQuadsExp* e, Symbol* s);
    GuavaDescriptor* only_in_result(list<GuavaDescriptor*> reg,GuavaQuadsExp* e, Symbol* s);
    GuavaDescriptor* available_in_another_location(list<GuavaDescriptor*> reg,GuavaQuadsExp* e, Symbol* s);
    GuavaDescriptor* spill();
    GuavaDescriptor* global_spill();
    GuavaDescriptor* local_spill();
    GuavaDescriptor* temp_spill();
public:

    /** 
     * Constructor.
     * @param tabla_ Tabla de descriptores.
     * @param gen_ Escritor de archivos.
     */
    RegisterAllocator(GuavaDescTable* tabla_reg_,GuavaDescTable* tabla_var_, Generator* gen_): tabla_reg(tabla_reg_), gen(gen_), tabla_var(tabla_var_){}

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
    static list<GuavaDescriptor*> getReg(GuavaQuads* i , GuavaDescTable* tabla_reg,GuavaDescTable* tabla_var, Generator* gen); 

};

#endif //GET_REG_HH
