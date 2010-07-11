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
 * @version $Id: SignatureHolder.h 2273 2010-07-09 18:29:48Z yegor256@yahoo.com $
 */

#include <string>
#include "brokers/Explanation.h"
#include "Proxy/Type.h"

void brokers::Explanation::setType(const proxy::Type& t) {
    _type = boost::shared_ptr<proxy::Type>(new proxy::Type(t));
}

void brokers::Explanation::setNames(const std::string& s, const std::string& o) {
    _slotName = s;
    _objectName = o;
}

brokers::Explanation::operator std::string() const {
    return "explanation";
}
