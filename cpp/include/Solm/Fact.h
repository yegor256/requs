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

#ifndef __INCLUDE_SOLM_FACT_H
#define __INCLUDE_SOLM_FACT_H

#include <vector>
#include <string>

#include "Solm/Snapshot.h"
#include "Solm/Outcome.h"

namespace solm {

/**
 * Forward declarations
 */
class Formula;

/**
 * One fact, positive or negative, with a text explanation.
 */
class Fact {
public:
    virtual operator bool() const;
    virtual const std::string toString() const { return snapshot.toString(); }
    bool operator==(const Fact&) const;
    Fact& setFormula(const Formula* f) { formula = f; return *this; }
    Fact& setException(const std::string& e) { exception = e; return *this; }
    Fact& setOutcome(const Outcome& o) { outcome = o; return *this; }
    bool hasOutcome() const { return outcome.size(); }
    Outcome& getOutcome() { return outcome; }
    const Outcome& getOutcome() const { return outcome; }
    const Formula* getFormula() const { return formula; }
    Snapshot getSnapshot() const { return snapshot; }
    Fact& setSnapshot(const Snapshot& s) { snapshot = s; return *this; }
private:
    std::string exception;
    Outcome outcome;
    const Formula* formula;
    Snapshot snapshot;
};

}

#endif
