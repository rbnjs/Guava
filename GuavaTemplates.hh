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
    GuavaGenerator* generador;
    GuavaSymTable* table;
    GuavaDescTable* vars;
    GuavaDescTable* regs;
    GuavaDescTable* regs_float;
    int offset_actual = 0;
public:
    /** 
     * Constructor de la clase.
     * @param g GuavaGenerator para poder escribir en el archivo.
     * @param tabla Tabla de simbolos
     * @param vars_ Descriptores de variable.
     * @param regs_ Descriptores de registros.
     * @param floats Descriptores de registros para floats.
     */
    GuavaTemplates(GuavaGenerator* g, GuavaSymTable* tabla, GuavaDescTable* vars_, GuavaDescTable* regs_, GuavaDescTable* floats):
                        generador(g),table(tabla),vars(vars_),regs(regs_), regs_float(floats){}
    /** 
     * Destructor
     */
    ~GuavaTemplates(){}

    void set_regs(GuavaDescTable* r);

    void set_vars(GuavaDescTable* v);

    void set_vars(list<SimpleSymbol*> simbolos);
    
    void reset_offset();
    
    int get_offset();

    virtual void store(SimpleSymbol* var, GuavaDescriptor* reg){}

    virtual void store(GuavaDescriptor* reg){}

    virtual void store_spill(GuavaDescriptor* reg){}

    virtual void push(GuavaDescriptor* reg){}

    virtual void entry_main(){}

    virtual void go_to(Symbol* to){}

    virtual void label(string label){}

    virtual void move(GuavaDescriptor* reg, GuavaDescriptor* reg2){}

    virtual void move(GuavaDescriptor* reg, string reg_2, Symbol* result){}
    
    virtual void read(GuavaDescriptor* reg , Symbol* result){}

    virtual void print(Symbol* arg){}

    virtual void print(GuavaDescriptor* reg){}
};

/** 
 * Clase que contiene las plantillas para el lenguaje MIPS. 
 */
class MIPS: public GuavaTemplates{
public:

    /** 
     * Constructor de la clase.
     */
    MIPS(GuavaGenerator* g, GuavaSymTable* t, GuavaDescTable* vars = 0): GuavaTemplates(g,t,vars,new DescTableMIPS(), new DescTableFloatMIPS()){}

    /** 
     * Destructor
     */
    ~MIPS(){}

    void store(SimpleSymbol* var, GuavaDescriptor* reg);

    void store(GuavaDescriptor* reg);

    void store_spill(GuavaDescriptor* reg);

    void push(GuavaDescriptor* reg);

    void entry_main();

    void label(string label);

    void go_to(Symbol* to);

    void move(GuavaDescriptor* reg, GuavaDescriptor* reg2);

    void move(GuavaDescriptor* reg, string reg_2, Symbol* result);
    
    void read(GuavaDescriptor* reg , Symbol* result);

    void print(Symbol* arg);

    void print(GuavaDescriptor* reg);

};

# endif
