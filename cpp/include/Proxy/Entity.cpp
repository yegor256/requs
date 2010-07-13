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
 * @version $Id: Type.cpp 2281 2010-07-11 10:07:12Z yegor256@yahoo.com $
 */

#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Logger.h"
#include "Proxy.h"
#include "Proxy/Type.h"
#include "Proxy/Slot.h"
#include "Solm/Predicate.h"

proxy::Entity& proxy::Entity::operator+=(const proxy::Slot& s) {
    //stub only
    return *this;
}

proxy::Entity& proxy::Entity::operator+=(const proxy::Entity::Slots& s) {
    //stub only
    return *this;
}

proxy::Slot& proxy::Entity::slot(const std::string& s) {
    for (Slots::iterator i = _slots.begin(); i != _slots.end(); ++i) {
        if (*i == s) {
            return *i;
        }
    }
    _slots.push_back(Slot(s));
    return slot(s);
}

