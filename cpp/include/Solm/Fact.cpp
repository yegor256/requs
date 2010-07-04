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

#include "Solm/Fact.h"

/**
 * Two facts are equal?
 */
bool solm::Fact::operator==(const Fact& f) const {
    if (!(snapshot == f.snapshot)) {
        return false;
    }
    if ((bool)*this != (bool)f) {
        return false;
    }
    return true;
}

/**
 * The fact is positive?
 */
solm::Fact::operator bool() const { 
    return exception.empty() && (!hasOutcome() || getOutcome()); 
}
