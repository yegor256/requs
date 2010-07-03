/**
 *
 * FaZend.com, Fully Automated Zend Framework
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * FaZend.com. located at www.fazend.com. If you received this 
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

#include "rqdql/Exception.h"

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
    Outcome() : std::vector<Fact>() { /* that's it */ }
    Outcome operator+(const Outcome&) const;
    Outcome& operator+=(const Outcome&);
    Outcome& operator<<(const Outcome&);
    Outcome& operator<<(const Fact&);
    operator bool() const;
    std::vector<FactPath> getPaths() const;
    Fact& getPositiveEnd();
private:
    class AbsentPositiveEndException : public rqdql::Exception {};
};

}

#endif
