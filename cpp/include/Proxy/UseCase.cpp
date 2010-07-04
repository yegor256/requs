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
 *
 * This file is included ONLY from Proxy.h
 */

const string UseCase::toString() const {
    return getName() + ": " + signature->toString() + "\n"
    + Flows::toString();
}

/**
 * Validates whether the use case has static name
 */
bool UseCase::hasName() const {
    return rqdql::get<Proxy>().hasName(this);
}

/**
 * Returns the name of USE CASE if it is in the static holder,
 * otherwise an exception will be thrown
 */
const string UseCase::getName() const {
    try {
        return rqdql::get<Proxy>().findName(this);
    } catch (rqdql::Exception e) {
        throw rqdql::Exception(rqdql::_t("Use case doesn't have a name, but getName() called"));
    }
}

