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
 * Append one outcome to another
 */
Outcome Outcome::operator+(const Outcome& out) const {
    // this outcome is empty - just return the given one
    if (!size()) {
        return out;
    }
    Outcome n = *this;
    if (!n.hasPositiveEnd()) {
        throw rqdql::Exception(
            boost::format("Outcome (%d facts) is negative, we can't append next step to it") % size()
        );
    }
    n.getPositiveEnd().setOutcome(out);
    return n;
}

/**
 * Get all possible paths
 */
vector<FactPath> Outcome::getPaths() const {
    vector<FactPath> v;
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
bool Outcome::hasPositiveEnd() const {
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

