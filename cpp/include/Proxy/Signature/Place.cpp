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
 * @version $Id: Signature.cpp 2240 2010-07-04 09:20:34Z yegor256@yahoo.com $
 */

#include <string>
#include <boost/format.hpp>
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Proxy/Type.h"
#include "Proxy/Signature.h"

proxy::signature::Place() : _type(), _slot(), _object() { 
    /* that's it */ 
}

void proxy::signature::Place::isExplained() { 
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
        throw AlreadyExplainedException(
            rqdql::_t("Place is already explained")
        );
    }
    _type = t;
}

void proxy::signature::Place::explain(const std::string& s, const std::string& o) { 
    if (isExplained()) {
        throw AlreadyExplainedException(
            rqdql::_t("Place is already explained")
        );
    }
    _slot = s; 
    _object = o; 
}

const std::string proxy::signature::Place::toString() const {
    // this is a type, like "ActorUser" or "PhotoFile"
    if (_type) {
        if (!_type->hasName()) {
            throw rqdql::Exception(
                rqdql::_t("Nameless type inside signature, how come?")
            );
        }
        return _type->name();
    }
    // this is a slot of an object, like "Name of ActorUser"
    if (!_slot.empty() && !_object.empty()) {
        return _slot + " (the " + _object + ")"; 
    }
    // there is nothing, just ITSELF
    return "itself"; 
}

