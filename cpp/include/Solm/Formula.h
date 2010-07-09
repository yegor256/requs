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

#ifndef __INCLUDE_SOLM_FORMULA_H
#define __INCLUDE_SOLM_FORMULA_H

#include <string>

namespace solm {

/**
 * Forward declarations
 */
class Chain;
class Context;

/**
 * An abstract formula inside SOLM collection
 */
class Formula {

public:

    /**
     * Nothing, just to make this class polymorphic
     */
    virtual ~Formula() { /* that's it */ };

    /**
     * Abstract method, to convert this formula to a user-friendly
     * string format. The method has to be overriden in child classes.
     */
    virtual operator std::string() const = 0;

    /**
     * Abstract method, to resolve this formula on some context
     * and produce a new Chain of Snapshots.
     * The method has to be overriden in child classes.
     */
    virtual Chain operator+(const Context&) const = 0;

};

}

#endif
