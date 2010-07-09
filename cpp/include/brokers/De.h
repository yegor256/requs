/**
 *

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

#ifndef __INCLUDE_SCOPE_BROKERS_DE_H
#define __INCLUDE_SCOPE_BROKERS_DE_H

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

namespace brokers {

class De { // data element
public:
    De() : name(""), explanation(0) { /* that's it */ }
    void setName(const string& n) { name = n; }
    const string getName() const { if (!hasName()) throw rqdql::Exception(rqdql::_t("no NAME in this DE")); return name; }
    bool hasName() const { return !name.empty(); }
    void setExplanation(proxy::Signature::Explanation* e) { explanation = e; }
    proxy::Signature::Explanation* getExplanation() const { if (!hasExplanation()) throw rqdql::Exception(rqdql::_t("no EXPLANATION here")); return explanation; }
    bool hasExplanation() const { return explanation; }
private:
    string name;
    proxy::Signature::Explanation* explanation;
};

}

#endif
