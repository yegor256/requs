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

#ifndef __INCLUDE_SOLM_CLAUSES_H
#define __INCLUDE_SOLM_CLAUSES_H

#include <string>
#include <map>
#include "Solm/Chain.h"

namespace solm {

/**
 * Prolog-style set of clauses
 */
class Clauses {

public:

    /**
     * Public constructor
     */
    Clauses();

    /**
     * The context is positive?
     */
    operator bool() const { return true; }

    /**
     * Add new alternative set of clauses
     */
    Clauses& operator<<(const Clauses&);

private:
    
    /**
     * Collection of objects
     */
    std::vector<clauses::Fact> _facts;
    
    /**
     * Alternative clauses
     */
    Chain _alternatives;
    
};

}

#endif
