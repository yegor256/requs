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

#ifndef __INCLUDE_SCOPE_BROKERS_FLOWHOLDER_H
#define __INCLUDE_SCOPE_BROKERS_FLOWHOLDER_H

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

namespace brokers {

class FlowHolder {
public:
    FlowHolder() : flow(0), id(0) { /* that's it */ }
    void setFlow(proxy::Flow* f) { flow = f; }
    bool hasFlow() const { return flow; }
    proxy::Flow* getFlow() const { if (!hasFlow()) throw rqdql::Exception(rqdql::_t("no FLOW here")); return flow; }
    void setId(int i) { id = i; }
    int getId() const { return id; }
private:
    proxy::Flow* flow;
    int id;
};

}

#endif
