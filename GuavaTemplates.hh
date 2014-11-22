/*
 * =====================================================================================
 *
 *       Filename:  GuavaTemplates.hh
 *
 *    Description:  Funciones templates.
 *
 *        Version:  1.0
 *        Created:  14/11/14 21:27:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization:  USB
 *
 * =====================================================================================
 */

# ifndef GUAVA_TEMPLATES_HH
# define GUAVA_TEMPLATES_HH
# include <set>
# include "Symbol.hh"
# include "GuavaSymTable.hh"
# include "GuavaDescriptor.hh"

using namespace std;
/** 
 * Clase de donde parten todos los templates.
 */
class GuavaTemplates{
protected:
    Generator* gen;
    GuavaSymTable* table;
    GuavaDescriptor* vars;
    GuavaDescriptor* regs;
public:
    /** 
     * Constructor de la clase.
     */
    GuavaTemplates(Generator* g = 0, GuavaSymTable* tabla = 0, GuavaDescriptor* vars = 0, GuavaDescriptor* regs = 0);
    /** 
     * Destructor
     */
    ~GuavaTemplates(){}

    void set_regs(GuavaDescriptor* r);

    void set_vars(GuavaDescriptor* v);
};

/** 
 * Clase que contiene las plantillas para el lenguaje MIPS. 
 */
class MIPS: public GuavaTemplates{
public:

    /** 
     * Constructor de la clase.
     */
    MIPS(Generator* g, GuavaSymTable* t): GuavaTemplates(g,t){}

    /** 
     * Destructor
     */
    ~MIPS(){}

    void store(SimpleSymbol* var, GuavaDescriptor* reg);

    void store(GuavaDescriptor* reg);

    void push(GuavaDescriptor* reg);

    void push(SimpleSymbol* s);

};

# endif
