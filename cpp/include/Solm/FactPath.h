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
 * Distance between two fact pathes, from BIGGER to SMALLER
 * THIS: {A, B, C}    P: {A, B}   RESULT: {C}
 * THIS: {A, B, C}    P: {C, D}   RESULT: {A, B, C}
 * THIS: {A, B}       P: {A, B}   RESULT: {}
 */
FactPath FactPath::distance(const FactPath& p) const {
    if (p.size() > size()) {
        throw rqdql::Exception("distance() argument is LARGER than subject");
    }
    pair<FactPath::const_iterator, FactPath::const_iterator> found 
        = mismatch(p.begin(), p.end(), begin());

    // copy everything that we have in THIS serie, after the first mismatch
    FactPath path;
    path.insert(path.end(), found.second, end());
    return path;
}

/**
 * Convert to string
 */
string FactPath::toString() const {
    vector<string> lines;
    for (FactPath::const_iterator f = begin(); f != end(); ++f) {
        lines.push_back((*f).getText());
    }
    return boost::algorithm::join(lines, "\n");
}
