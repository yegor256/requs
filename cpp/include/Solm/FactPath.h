/**
 * * RQDQL.com, Requirements Definition and Query Language
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

#ifndef __INCLUDE_SOLM_FACTPATH_H
#define __INCLUDE_SOLM_FACTPATH_H

#include <vector>
#include <string>

#include "Solm/Fact.h"

namespace solm {

/**
 * Serie of facts, ordered
 */
class FactPath : public Fact, public std::vector<Fact> {
public:
    operator bool() const; // the path ends positively?
    FactPath operator+(const FactPath&) const; // concatenate two paths
    bool operator==(const FactPath&) const; // these two paths are equivalent?
    bool operator<(const FactPath&) const; // one path is shorter than the other?
    const std::string toString() const; // convert this path to a user-friendly string
private:
};

}

#endif
