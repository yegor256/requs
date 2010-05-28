/**
 *
 * FaZend.com, Fully Automated Zend Framework
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * FaZend.com. located at www.fazend.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id: Formula.h 2070 2010-05-24 14:19:35Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Solm.h
 */

/**
 * Two facts are equal?
 */
bool Fact::operator==(const Fact& f) const {
    if (getText() != f.getText()) {
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
Fact::operator bool() const { 
    return positive && (!hasOutcome() || getOutcome()); 
}
