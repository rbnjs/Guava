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
class RegisterAllocation{
protected:
    GuavaDescTable* tabla_reg; /* Tabla de descriptores para registros. */
public:

    /** 
     * Le asocio la tabla de descriptores.
     */
    RegisterAllocation(GuavaDescTable* tabla_): tabla_reg(tabla_){}

    ~RegisterAllocation(){}

    list<string> getReg(GuavaQuads* i);

};

#endif //GET_REG_HH
