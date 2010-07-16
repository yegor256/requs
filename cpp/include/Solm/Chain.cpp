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

#include <string>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>
#include "Solm/Chain.h"
#include "Solm/Term.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

solm::Chain::Chain() : std::map<solm::Term, solm::Chain>() {
    /* that's it */
}

solm::Chain::operator solm::Term() const {
    // stub
    return solm::Term();
}

bool solm::Chain::operator==(const solm::Chain& c) const {
    return equal(begin(), end(), c.begin());
}

bool solm::Chain::operator<(const solm::Chain& c) const {
    return size() < c.size();
}

solm::Chain solm::Chain::operator+(const solm::Chain& c) const {
    if (!*this) {
        throw rqdql::Exception(
            boost::format("Chain (%d snapshots) is negative, we can't PLUS to it") % size()
        );
    }
    Chain n = *this;
    for (const_iterator s = c.begin(); s != c.end(); ++s) {
        n += *s;
    }
    return n;
}

solm::Chain solm::Chain::operator+(const solm::Term& s) const {
    if (!*this) {
        throw rqdql::Exception(
            boost::format("Chain (%d snapshots) is negative, we can't PLUS to it") % size()
        );
    }
    Chain n = *this;
    n.push_back(s);
    return n;
}

solm::Chain& solm::Chain::operator<<(const solm::Term& s) {
    if (!*this) {
        throw rqdql::Exception(
            boost::format("Chain (%d snapshots) is negative, we can't << to it") % size()
        );
    }
    *(end() - 1) << s;
    return *this;
}

solm::Chain::operator bool() const {
    for (const_iterator s = begin(); s != end(); ++s) {
        if (!(*s)) {
            return false;
        }
    }
    return true;
}

// solm::Chain::operator std::string() const {
//     using namespace std;
//     vector<string> lines;
//     for (const_iterator s = begin(); s != end(); ++s) {
//         lines.push_back(
//             boost::algorithm::replace_all_copy(
//                 (string)*s,
//                 "\n",
//                 "\t\n"
//             )
//         );
//     }
//     return boost::algorithm::join(lines, "\n");
// }

