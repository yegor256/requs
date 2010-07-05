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
 *
 * This file is included ONLY from Proxy.h
 */

#include <string>
#include "rqdql/Exception.h"
#include "Proxy/Type.h"
#include "Proxy/Signature.h"

const std::string proxy::Signature::Explanation::toString() const {
    // this is a type, like "ActorUser" or "PhotoFile"
    if (_type) {
        if (_type->hasName()) {
            return _type->name();
        } else {
            throw rqdql::Exception(
                "Nameless type inside signature, how come?"
            );
        }
    }
    // this is a slot of an object, like "Name of ActorUser"
    if (!_slot.empty() && !_object.empty()) {
        return _slot + " (the " + _object + ")"; 
    }
    // there is nothing, just ITSELF
    return "itself"; 
}

