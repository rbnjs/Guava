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
# include "Generator.hh"
using namespace std;
/** 
 * Clase de donde parten todos los templates.
 */
class GuavaTemplates{
protected:
    GuavaGenerator* gen;
    GuavaSymTable* table;
    GuavaDescTable* vars;
    GuavaDescTable* regs;
    int offset_actual = 0;
public:
    /** 
     * Constructor de la clase.
     */
    GuavaTemplates(GuavaGenerator* g = 0, GuavaSymTable* tabla = 0, GuavaDescTable* vars = 0, GuavaDescTable* regs = 0);
    /** 
     * Destructor
     */
    ~GuavaTemplates(){}

    void set_regs(GuavaDescTable* r);

    void set_vars(GuavaDescTable* v);

    void reset_offset();
    
    int get_offset();
};

/** 
 * Clase que contiene las plantillas para el lenguaje MIPS. 
 */
class MIPS: public GuavaTemplates{
public:

    /** 
     * Constructor de la clase.
     */
    MIPS(GuavaGenerator* g = 0, GuavaSymTable* t = 0, GuavaDescTable* vars = 0, GuavaDescTable* regs = 0): GuavaTemplates(g,t,vars,regs){}

    /** 
     * Destructor
     */
    ~MIPS(){}

    void store(SimpleSymbol* var, GuavaDescriptor* reg);

    void store(GuavaDescriptor* reg);

    void store_spill(GuavaDescriptor* reg);

    void push(GuavaDescriptor* reg);

};

# endif
