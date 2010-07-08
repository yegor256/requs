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

#ifndef __INCLUDE_SOLM_OUTCOME_H
#define __INCLUDE_SOLM_OUTCOME_H

#include <vector>

namespace solm {

/**
 * Forward declarations
 */
class FactPath;
class Fact;

/**
 * Result of any formula from SOLM. Outcome is a collection of
 * facts (where only one is positive).
 */
class Outcome : public std::vector<Fact> {

public:

    /**
     * Create new outcome, right in the context provided
     */
    Outcome(const Context&);

    /**
     * Convert this outcome to the context. The produced context is 
     * the context at the END of the outcome
     */
    operator Context() const;

    /**
     * Append one outcome to another, concatenating them vertically
     */
    Outcome operator+(const Outcome&) const;

    /**
     * Concatenate them vertically
     */
    Outcome& operator+=(const Outcome&);

    /**
     * Concatenate them horizontally
     */
    Outcome& operator<<(const Outcome&);

    /**
     * Concatenate them horizontally
     */
    Outcome& operator<<(const Fact&);

    /**
     * This outcome has a positive ending?
     */
    operator bool() const;

    /**
     * Get all possible paths
     */
    const std::vector<FactPath> paths() const;

private:

    /**
     * Context at the beginning of Outcome
     */
    Context _context;

};

}

#endif
