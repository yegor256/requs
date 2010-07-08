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
#include "Solm/FactPath.h"

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
