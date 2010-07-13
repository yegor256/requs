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

#ifndef __INCLUDE_SOLM_CONTEXT_H
#define __INCLUDE_SOLM_CONTEXT_H

#include <string>
#include <map>
#include "Solm/Context/Object.h"
#include "Solm/Chain.h"

namespace solm {

/**
 * Context in which any predicate can be resolved
 */
class Context {

public:

    /**
     * An object inside a context
     */
    struct Object {
        int id;
        std::string variable;
        std::string value;
    };

    /**
     * Public constructor
     */
    Context();

    /**
     * The context is positive?
     */
    operator bool() const { return true; }

    /**
     * Add new alternative context
     */
    Context& operator<<(const Context&);

private:
    
    /**
     * Collection of objects
     */
    std::vector<context::Object> _objects;
    
    /**
     * Alternative contexts
     */
    Chain _alternatives;
    
};

}

#endif
