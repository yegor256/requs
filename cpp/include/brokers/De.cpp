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
 * @version $Id: De.h 2273 2010-07-09 18:29:48Z yegor256@yahoo.com $
 */
 
#include <string>
#include <boost/shared_ptr.hpp>
#include "brokers/De.h"
#include "brokers/Explanation.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

brokers::De::De() : _name(), _explanation() { 
    /* that's it */ 
}

void brokers::De::setName(const std::string& n) { 
    _name = n; 
}

const std::string& brokers::De::getName() const { 
    if (!hasName()) {
        throw rqdql::Exception(
            rqdql::_t("no NAME in this DE")
        ); 
    }
    return _name; 
}

bool brokers::De::hasName() const { 
    return !_name.empty(); 
}

void brokers::De::setExplanation(const brokers::Explanation& e) { 
    _explanation = boost::shared_ptr<brokers::Explanation>(new brokers::Explanation(e)); 
}

const brokers::Explanation& brokers::De::getExplanation() const { 
    if (!hasExplanation()) {
        throw rqdql::Exception(
            rqdql::_t("no EXPLANATION here")
        ); 
    }
    return *_explanation; 
}

bool brokers::De::hasExplanation() const { 
    return _explanation; 
}

