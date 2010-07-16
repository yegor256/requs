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
#include <map>
#include "Solm/Chain.h"
#include "Solm/Term.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

solm::Chain::Chain() : std::map<solm::Term, solm::Chain>() {
    /* that's it */
}

solm::Chain::operator bool() const {
    for (const_iterator s = begin(); s != end(); ++s) {
        if (!((*s).first) || !((*s).second)) {
            return false;
        }
    }
    return true;
}

solm::Chain::operator solm::Term() const {
    return Term(finalPair().first);
}

solm::Chain& solm::Chain::operator<<(const solm::Term& s) {
    if (*this && s) {
        throw rqdql::Exception(
            boost::format("Chain (%d terms) is positive, you can't add a positive TERM '%s' to it") % size() % s
        );
    }
    operator[](s); // create a new term there
    return *this;
}

solm::Chain& solm::Chain::operator+=(const solm::Term& s) {
    (Term)(*this)
    return *this;
}

pair<solm::Term, solm::Chain>& solm::Chain::finalPair() {
    if (!*this) {
        throw rqdql::Exception(
            boost::format("Chain (%d terms) is negative, we can't get finalPair()") % size()
        );
    }
    for (const_iterator s = begin(); s != end(); ++s) {
        if ((*s).first && !(*s).second.size()) {
            return *s;
        }
        if ()
    }
}
