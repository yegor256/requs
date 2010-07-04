/**
 * * RQDQL.com, Requirements Definition and Query Language
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
 *
 * This file is included ONLY from Solm.h
 */

/**
 * Get value
 */
const boost::shared_ptr<const Snapshot::Object::Value>& Snapshot::Object::getValue() const { 
    if (!hasValue()) {
        throw rqdql::Exception(
            "Object doesn't have a value, use hasValue() first"
        );
    }
    return value; 
}

/**
 * Set value, wrapper
 */
void Snapshot::Object::setValue(const string& s) {
    setValue(boost::shared_ptr<Snapshot::Object::Value>(new Snapshot::Object::ValueString(s)));
}

/**
 * Set value, wrapper
 */
void Snapshot::Object::setValue(const vector<int>& v) {
    setValue(boost::shared_ptr<Snapshot::Object::Value>(new Snapshot::Object::ValueSet(v)));
}

/**
 * Get type
 */
const string& Snapshot::Object::getType() const { 
    if (!hasType()) {
        throw rqdql::Exception(
            "Object doesn't have a type, use hasType() first"
        );
    }
    return type; 
}

/**
 * Try to set a type, if not set before
 */
void Snapshot::Object::setType(const string& t) {
    if (hasType()) {
        throw rqdql::Exception(
            boost::format("Object already has a type: '%s', use hasType() first") % getType()
        );
    }
    type = t; 
}

/**
 * Get name
 */
const string& Snapshot::Object::getName() const { 
    if (!hasName()) {
        throw rqdql::Exception(
            "Object doesn't have a name, use hasName() first"
        );
    }
    return name; 
}

/**
 * The object has ID set?
 */
bool Snapshot::Object::hasId() const { 
    return id > 0; 
}

/**
 * Get ID
 */
int Snapshot::Object::getId() const { 
    if (!hasId()) {
        throw rqdql::Exception(
            "Object doesn't have an ID, use hasID() first"
        );
    }
    return id; 
}

/**
 * Remove ID from this object
 * @see Snapshot::deassignId()
 */
void Snapshot::Object::removeId() { 
    if (!hasId()) {
        throw rqdql::Exception(
            "Object doesn't have an ID and we can't removeId(), use hasID() first"
        );
    }
    id = -id; 
}

/**
 * Compute next available ID after this object
 * @see Snapshot::computeNextId()
 */
int Snapshot::Object::computeNextId() const { 
    return abs(id) + 1;
}

/**
 * Convert ACL rule to a user-friendly text
 */
const string Snapshot::Object::AclRule::toString() const {
    string s;
    switch (operation) {
        case CREATE:
            s = "CREATE";
            break;
        case UPDATE:
            s = "UPDATE";
            break;
        case READ:
            s = "READ";
            break;
        case DELETE:
            s = "DELETE";
            break;
    }
    return (boost::format("%s:%d") % s % id).str();
}

#include "Solm/Snapshot/Object/Value.h"
