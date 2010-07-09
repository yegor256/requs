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
#include <boost/format.hpp>
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Proxy/Type.h"
#include "Proxy/Signature.h"
#include "Proxy/Signature/Place.h"

proxy::signature::Place::Place() : _type(), _slot(), _object() { 
    /* that's it */ 
}

bool proxy::signature::Place::isExplained() const { 
    if (_type) {
        return true;
    }
    if (!_slot.empty() || _object.empty()) {
        return true;
    }
    return false;
}

void proxy::signature::Place::explain(const boost::shared_ptr<Type>& t) { 
    if (isExplained()) {
        throw rqdql::Exception(
            rqdql::_t("Place is already explained")
        );
    }
    _type = t;
}

void proxy::signature::Place::explain(const std::string& s, const std::string& o) { 
    if (isExplained()) {
        throw rqdql::Exception(
            rqdql::_t("Place is already explained")
        );
    }
    _slot = s; 
    _object = o; 
}

proxy::signature::Place::operator std::string() const {
    // this is a type, like "ActorUser" or "PhotoFile"
    if (_type) {
        return "{type}";
    }
    // this is a slot of an object, like "Name of ActorUser"
    if (!_slot.empty() && !_object.empty()) {
        return _slot + " (the " + _object + ")"; 
    }
    // there is nothing, just ITSELF
    return "itself"; 
}

