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

#ifndef __INCLUDE_SOLM_FORMULA_TRUE_H
#define __INCLUDE_SOLM_FORMULA_TRUE_H

#include <string>
#include "Solm/Formula.h"
#include "Solm/Chain.h"
#include "Solm/Context.h"

namespace solm {

/**
 * Always TRUE
 */
class True : public Formula {

public:

    /**
     * Public constructor
     */
    True() : Formula() { /* that's it */ }

    /**
     * To resolve this formula on some context
     * and produce a new Chain of Snapshots.
     */
    Chain operator+(const Context&) const { return Chain(); }

};

/**
 * Convert the formula to string and output it to the
 * test typer, in order to use in unit tests
 */
rqdql::Tt& operator<<(const rqdql::Tt&, const True&);

}

#endif
