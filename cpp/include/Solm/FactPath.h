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
 * @version $Id: Formula.h 2070 2010-05-24 14:19:35Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Solm.h
 */

/**
 * Concatenator of fact vectors
 */
FactPath FactPath::operator+(const FactPath& v) const {
    FactPath res;
    res.insert(res.end(), begin(), end());
    res.insert(res.end(), v.begin(), v.end());
    return res;
}

/**
 * Compare two vectors of facts
 */
bool FactPath::operator==(const FactPath& v) const {
    return equal(begin(), end(), v.begin());
}

/**
 * Compare lengths
 */
bool FactPath::operator<(const FactPath& p) const {
    return size() < p.size();
}

/**
 * Convert to string
 */
const string FactPath::toString() const {
    vector<string> lines;
    lines.push_back(Fact::toString());
    for (FactPath::const_iterator f = begin(); f != end(); ++f) {
        lines.push_back(
            boost::algorithm::replace_all_copy(
                (*f).toString(),
                "\n",
                "\t\n"
            )
        );
    }
    return boost::algorithm::join(lines, "\n");
}
