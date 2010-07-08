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

solm::Chain solm::Chain::Chain() : std::vector<Snapshot>() {
    /* that's it */
}

bool solm::Chain::operator==(const solm::Chain& c) const {
    return equal(begin(), end(), c.begin());
}

bool solm::Chain::operator<(const solm::Chain& c) const {
    return size() < p.size();
}

solm::Chain::operator bool() const {
    for (const_iterator s = begin(); s != end(); ++s) {
        if (!(*s)) {
            return false;
        }
    }
    return true;
}

solm::Chain::operator std::string() const {
    using namespace std;
    vector<string> lines;
    for (const_iterator s = begin(); s != end(); ++s) {
        lines.push_back(
            boost::algorithm::replace_all_copy(
                (string)*s,
                "\n",
                "\t\n"
            )
        );
    }
    return boost::algorithm::join(lines, "\n");
}

solm::Chain solm::Chain::operator+(const solm::Chain& c) const {
    // this outcome is empty - just return the given one
    if (!size()) {
        return c;
    }
    Outcome n = *this;
    if (!n) {
        throw rqdql::Exception(
            boost::format("Outcome (%d facts) is negative, we can't append next step to it") % size()
        );
    }
    ((Snapshot)n).set(c);
    return n;
}

solm::Chain& solm::Chain::operator+=(const solm::Chain& c) {
    ((Snapshot)*this).setOutcome(out);
    return *this;
}

solm::Chain& solm::Chain::operator<<(const solm::Chain& c) {
    for (const_iterator s = c.begin(); s != c.end(); ++s) {
        push_back(*s);
    }
    return *this;
}

solm::Chain& solm::Chain::operator<<(const solm::Snapshot& s) {
    push_back(s);
    return *this;
}

