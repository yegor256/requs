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
 * @version $Id$
 *
 * This file is included ONLY from Solm.h
 */

/**
 * Create an outcome of this formula, list of facts
 */
Outcome Formula::getOutcome() const { 
    return Outcome(); 
}

/**
 * Set formula to the absolute position in the collection,
 * if this position is busy, this method will OVERWRITE it
 */
void Formula::setFormula(Formula* f, size_t i = 0) {
    if (subs.size() < i+1) {
        subs.resize(i+1);
    }
    subs[i] = f;
}

/**
 * Get formula by index. If it is absent, this situation will be logged
 * and TRUE constant will be returned.
 */
Formula* Formula::getFormula(size_t i = 0) const {
    if (i > subs.size()-1) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Formula no.%d is absent, returning TRUE instead")) % i).str()
        );
        return new Err((boost::format(rqdql::_t("'absent formula no.%d")) % i).str());
    }
    return subs.at(i);
}

