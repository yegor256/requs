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

#ifndef __INCLUDE_SOLM_FACT_H
#define __INCLUDE_SOLM_FACT_H

#include <vector>
#include <string>
#include "Solm/Snapshot.h"
#include "Solm/Outcome.h"

namespace solm {

/**
 * Forward declarations
 */
class Formula;

/**
 * One fact, positive or negative, with a text explanation.
 */
class Fact {

public:

    /**
     * Public constructor
     */
    Fact();

    /**
     * The fact is positive? To be overriden in FactPath
     * @see FactPath::bool()
     */
    virtual operator bool() const;

    /**
     * Conver it to a user-friendly string
     */
    virtual operator std::string() const;

    /**
     * Two paths are equal?
     */
    bool operator==(const Fact&) const;

    /**
     * Outgoing context to retrieve
     */
    operator Context() const;

    /**
     * Set outcome to this path
     */
    void set(const Outcome& o) { _outcome = o; }

private:

    /**
     * Sub-Outcome
     */
    Outcome _outcome;

};

}

#endif
