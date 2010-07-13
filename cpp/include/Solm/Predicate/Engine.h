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
 * @version $Id: Forall.h 2299 2010-07-13 10:01:56Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_PREDICATE_ENGINE_H
#define __INCLUDE_SOLM_PREDICATE_ENGINE_H

#include <string>
#include <vector>
#include "Solm/Predicate.h"

namespace solm {
namespace predicate {

/**
 * Engine to calculate predicate outcome
 */
class Engine {

public:
    
    /**
     * Construct this engine and prepare for calculations
     */
    Engine(const Context&, const std::vector<boost::shared_ptr<Argument> >&) { }
    
    /**
     * To resolve the predicate and return new Chain of Contexts
     */
    Chain operator+(const Context&) const { return Chain(); }

private:
    
    /**
     * Collection of arguments
     */
    std::vector<boost::shared_ptr<Argument> > _arguments;

};

}
}

#endif
