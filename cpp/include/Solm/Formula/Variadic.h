/**
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

#ifndef __INCLUDE_SOLM_FORMULA_VARIADIC_H
#define __INCLUDE_SOLM_FORMULA_VARIADIC_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Solm/Formula.h"
#include "Solm/Snapshot.h"

namespace solm {

/**
 * Forward declarations
 */
class Context;

/**
 * Many formulas connected in a chain with some OPERAND
 */
class Variadic : public Formula {

public:
    
    /**
     * Enumerated type of operand
     */
    typedef enum {
        OP_TO, 
        OP_AND, 
        OP_OR, 
        OP_SEMICOLON
    } Operand;
    
    /**
     * Public constructor
     */
    Variadic(Operand op = OP_AND);

    /**
     * Add new formula to the chain
     */
    Variadic& operator+=(const boost::shared_ptr<solm::Formula>&);

    /**
     * Append one variadic to another, concatenate them in other words
     */
    Variadic& operator+=(const Variadic&);

    /**
     * To resolve this formula on some context
     * and produce a new Chain of Snapshots.
     */
    virtual Chain operator+(const Context&) const;

private:

    /**
     * Type for collection of formulas
     * @see _formulas
     */
    typedef std::vector<boost::shared_ptr<Formula> > Formulas;

    /**
     * The operand between formulas
     */
    Operand _operand;
    
    /**
     * Collection of formulas, ordered
     */
    Formulas _formulas;

};

}

#endif
