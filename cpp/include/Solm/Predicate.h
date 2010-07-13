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
 * @version $Id: Sentence.h 2298 2010-07-13 08:08:15Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_PREDICATE_H
#define __INCLUDE_SOLM_PREDICATE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Solm/Argument.h"
#include "Solm/Chain.h"
#include "Solm/Context.h"

namespace solm {

/**
 * Second order logic predicate
 */
class Predicate : public Argument {

public:
    
    /**
     * Construct a new predicate from a string
     *
     * @param p Predicate in LISP-style
     * @see PredicateTest.cpp
     */
    Predicate(const std::string& p = "true") : _arguments() { /* that's it for now */ }

    /**
     * To resolve this argument on some context
     * and produce a new Chain of Snapshots.
     */
    Chain operator+(const Context&) const { return Chain(); }

private:
    
    /**
     * Collection of arguments
     */
    std::vector<boost::shared_ptr<Argument> > _arguments;

};

}

#endif
