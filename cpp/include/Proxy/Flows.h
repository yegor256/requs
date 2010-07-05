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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_PROXY_FLOWS_H
#define __INCLUDE_SCOPE_PROXY_FLOWS_H

#include <vector>
#include <map>
#include <typeinfo>
#include <iostream>
#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp> // join()
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
#include <boost/algorithm/string/regex.hpp> // replace_regex_copy()
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()
#include "Solm.h"
#include "Logger.h"

namespace proxy {

class Type;
class Slot;
class Signature;
class Flow;
class Flows;
class UseCase;
class Proxy;

class Flows {
public:
    Flows();
    Flows* addFlow(int i, Flow* f) { flows[i] = f; return this; }
    Flow* getFlow(int);
    const string toString() const;
    solm::Sequence* makeSequence() const;
    bool hasSequence() const { return !formula && !flows.empty(); }
    void setFlows(Flows* f) { flows = f->flows; }
    map<int, Flow*> getFlows() const { return flows; }
    void setFormula(solm::Formula*); // instead of sequence, just one formula
    bool hasFormula() const { return formula; }
    solm::Formula* getFormula() { return formula; }
private:
    map<int, Flow*> flows;
    solm::Formula* formula;
};

}

#endif
