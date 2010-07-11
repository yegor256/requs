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

#ifndef __INCLUDE_SOLM_FORMULA_PREDICATE_H
#define __INCLUDE_SOLM_FORMULA_PREDICATE_H

#include <vector>
#include "Solm/Formula.h"
#include "Solm/Formula/Parametrized.h"
#include "Solm/Chain.h"
#include "Solm/Context.h"

namespace solm {

/**
 * Call for a pre-defined formula
 */
class Predicate : public Formula, public Parametrized<Predicate> {

public:

    /**
     * Public constructor
     */
    Predicate(const std::string& n) : Parametrized<Predicate>(), _name(n) { /* that's it */ }

    /**
     * Convert it to the user-friendly text
     */
    operator std::string() const;

    /**
     * To resolve this formula on some context
     * and produce a new Chain of Snapshots.
     */
    virtual Chain operator+(const Context&) const;

private:
    
    /**
     * Predicate name
     */
    std::string _name;

};

}

#endif

