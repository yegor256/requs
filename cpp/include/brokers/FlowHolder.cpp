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
 * @version $Id: FlowHolder.h 2273 2010-07-09 18:29:48Z yegor256@yahoo.com $
 */

#include <string>
#include <boost/shared_ptr.hpp>
#include "Proxy/UseCase.h"
#include "brokers/FlowHolder.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

brokers::FlowHolder::FlowHolder() : _flow(), _id(0) { 
    /* that's it */ 
}

void brokers::FlowHolder::setFlow(const proxy::UseCase& f) { 
    _flow = new proxy::UseCase(f); 
}

bool brokers::FlowHolder::hasFlow() const { 
    return _flow; 
}

const proxy::Flow& brokers::FlowHolder::getFlow() const { 
    if (!hasFlow()) {
        throw rqdql::Exception(
            rqdql::_t("no FLOW here")
        ); 
    }
    return _flow; 
}

void brokers::FlowHolder::setId(int i) { 
    _id = i; 
}

int brokers::FlowHolder::getId() const { 
    return _id; 
}

