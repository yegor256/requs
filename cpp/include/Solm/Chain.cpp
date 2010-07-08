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
 * @version $Id: FactPath.cpp 2256 2010-07-08 08:30:01Z yegor256@yahoo.com $
 */

#include <string>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>
#include "Solm/Chain.h"

solm::FactPath solm::FactPath::operator+(const solm::FactPath& v) const {
    FactPath res;
    res.insert(res.end(), begin(), end());
    res.insert(res.end(), v.begin(), v.end());
    return res;
}

bool solm::FactPath::operator==(const solm::FactPath& v) const {
    return equal(begin(), end(), v.begin());
}

bool solm::FactPath::operator<(const solm::FactPath& p) const {
    return size() < p.size();
}

solm::FactPath::operator bool() const {
    for (FactPath::const_iterator f = begin(); f != end(); ++f) {
        if (!(*f)) {
            return false;
        }
    }
    return true;
}

solm::FactPath::operator std::string() const {
    using namespace std;
    vector<string> lines;
    lines.push_back(Fact::operator string());
    for (FactPath::const_iterator f = begin(); f != end(); ++f) {
        lines.push_back(
            boost::algorithm::replace_all_copy(
                (string)*f,
                "\n",
                "\t\n"
            )
        );
    }
    return boost::algorithm::join(lines, "\n");
}
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
 * @version $Id: Outcome.cpp 2256 2010-07-08 08:30:01Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Solm.h
 */
 
#include <string>
#include <vector>
#include "Solm/Outcome.h"

solm::Outcome::Outcome(const Context& ctx) : std::vector<Fact>(), _context(ctx) { 
    /* that's it */ 
}

solm::Outcome solm::Outcome::operator+(const solm::Outcome& out) const {
    // this outcome is empty - just return the given one
    if (!size()) {
        return out;
    }
    Outcome n = *this;
    if (!n) {
        throw rqdql::Exception(
            boost::format("Outcome (%d facts) is negative, we can't append next step to it") % size()
        );
    }
    n.getPositiveEnd().setOutcome(out);
    return n;
}

solm::Outcome& solm::Outcome::operator+=(const solm::Outcome& out) {
    getPositiveEnd().setOutcome(out);
    return *this;
}

solm::Outcome& solm::Outcome::operator<<(const solm::Outcome& out) {
    for (Outcome::const_iterator i = out.begin(); i != out.end(); ++i) {
        push_back(*i);
    }
    return *this;
}

solm::Outcome& solm::Outcome::operator<<(const solm::Fact& f) {
    push_back(f);
    return *this;
}

const std::vector<solm::FactPath> Outcome::paths() const {
    std::vector<FactPath> v;
    for (const_iterator i = begin(); i != end(); ++i) {
        FactPath p;
        p.push_back(*i);
        if ((*i).hasOutcome()) {
            vector<FactPath> paths = (*i).getOutcome().getPaths();
            for (vector<FactPath>::const_iterator j = paths.begin(); j != paths.end(); ++j) {
                FactPath n = p + *j;
                v.push_back(n);
            }
        } else {
            v.push_back(p);
        }
    }
    return v;
}

/**
 * This outcome has a positive end?
 */
Outcome::operator bool() const {
    try {
        const_cast<Outcome*>(this)->getPositiveEnd();
        return true;
    } catch (AbsentPositiveEndException e) {
        return false;
    }
}

/**
 * Get positive end if it exists
 */
Fact& Outcome::getPositiveEnd() {
    for (iterator i = begin(); i != end(); ++i) {
        if (!(*i).hasOutcome()) {
            if (*i) {
                return *i;
            } else {
                continue;
            }
        }
        return (*i).getOutcome().getPositiveEnd();
    }
    throw AbsentPositiveEndException();
}

