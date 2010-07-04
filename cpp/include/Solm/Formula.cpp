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
 * @version $Id$
 *
 * This file is included ONLY from Solm.h
 */

#include "Solm/Formula.h"
#include "rqdql.h"
#include "Logger.h"

#include <boost/format.hpp>

/**
 * Set formula to the absolute position in the collection,
 * if this position is busy, this method will OVERWRITE it
 */
void solm::Formula::setFormula(solm::Formula* f, size_t i = 0) {
    if (subs.size() < i+1) {
        subs.resize(i+1);
    }
    subs[i] = f;
}

/**
 * Get formula by index. If it is absent, this situation will be logged
 * and TRUE constant will be returned.
 */
solm::Formula* solm::Formula::getFormula(size_t i = 0) const {
    if (i > subs.size()-1) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Formula no.%d is absent, returning TRUE instead")) % i).str()
        );
        return new Err((boost::format(rqdql::_t("'absent formula no.%d")) % i).str());
    }
    return subs.at(i);
}

/**
 * Generate an outcome
 */
solm::Outcome solm::Formula::getOutcome(const solm::Fact& f, 
    const solm::Snapshot::Mapping& m = solm::Snapshot::NullMapping) const {
    return Outcome(); 
}

/**
 * Generate an outcome
 */
solm::Outcome solm::Formula::getOutcome() const { 
    return getOutcome(Fact()); 
}
