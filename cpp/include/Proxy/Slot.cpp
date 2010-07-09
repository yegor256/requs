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
#include <boost/shared_ptr.hpp>
#include "Proxy/Slot.h"
#include "Solm/Formula/True.h"

proxy::Slot::Slot(
    const std::string& n, 
    const proxy::Slot::Cardinality& c, 
    const boost::shared_ptr<proxy::Type>& t) :
    _name(n), _cardinality(c), _type(t) {
    /* nothing for now */
}

proxy::Slot::Slot(const std::string& n) :
    _name(n), 
    _cardinality("1..n -> 1"), 
    _type(new proxy::Type()) {
    /* nothing for now */
}

