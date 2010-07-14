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

#ifndef __INCLUDE_SOLM_PREDICATE_H
#define __INCLUDE_SOLM_PREDICATE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Solm/Argument.h"
#include "Solm/Chain.h"
#include "Solm/Data.h"

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
    Predicate(const std::string& p = "(true)");

    /**
     * Get an access to the argument of predicate
     * 
     * The method will change the argument, if some string is
     * provided. In any case the method will return the current
     * value of the argument (after change, of course).
     *
     * @param i Index of the argument to access to
     * @param v The value to set, if provided
     */
    const boost::shared_ptr<Argument>& arg(size_t, const std::string& v = "");

    /**
     * To add new argument to the list of arguments, to the end
     * of the list
     */
    Predicate& operator+=(const Argument&);

    /**
     * To resolve this argument on some set of Prolog-like clauses
     * and produce a new Chain of clauses.
     */
    Chain operator+(const Data&) const;
    
    /**
     * Convert the predicate to string
     */
    operator std::string() const;

private:
    
    /**
     * List of arguments
     */
    typedef std::vector<boost::shared_ptr<Argument> > Arguments;
    
    /**
     * Name of the predicate
     */
    std::string _name;
    
    /**
     * Collection of arguments
     */
    Arguments _arguments;

};

}

#endif
