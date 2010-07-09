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

#ifndef __INCLUDE_SCOPE_BROKERS_SIGELEMENT_H
#define __INCLUDE_SCOPE_BROKERS_SIGELEMENT_H

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

namespace brokers {

class SigElement {
public:
    SigElement() : de(0), informal(""), verb("") { /* that's it */ }
    void setInformal(const string& s) { informal = s; }
    bool hasInformal() const { return !informal.empty(); }
    const string getInformal() const { if (!hasInformal()) throw rqdql::Exception(rqdql::_t("no INFORMAL here")); return informal; }
    void setDe(De* d) { de = d; }
    De* getDe() const { if (!hasDe()) throw rqdql::Exception(rqdql::_t("no DE here")); return de; }
    bool hasDe() const { return de; }
    void setVerb(const string& v) { verb = v; }
    const string getVerb() const { if (!hasVerb()) throw rqdql::Exception(rqdql::_t("no VERB here")); return verb; }
    bool hasVerb() const { return !verb.empty(); }
    const string toFormalString() const; // like "${user}"
    const string toInformalString() const; // like "\"some\" ActorUser (the user)"
private:
    De* de;
    string informal;    
    string verb;
};

typedef vector<SigElement*> SigElements;

}

#endif
