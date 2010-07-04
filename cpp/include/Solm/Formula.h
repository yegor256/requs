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
 */

#ifndef __INCLUDE_SOLM_FORMULA_H
#define __INCLUDE_SOLM_FORMULA_H

#include <vector>
#include <string>

#include "Solm/Snapshot.h"

namespace solm {

/**
 * Forward declarations
 */
class Outcome;
class Fact;

/**
 * ...
 */
class Formula {
public:
    typedef std::vector<Formula*> Formulas;
    virtual ~Formula() { /* nothing, just to make this class polymorphic */ };
    virtual const std::string toString() const = 0;
    void clear() { subs.clear(); } // remove everything from the collection
    Formula* getFormula(size_t) const; // get formula by index
    void setFormula(Formula*, size_t);
    void addFormula(Formula* f) { subs.push_back(f); }
    const Formulas& getFormulas() const { return subs; }
    Outcome getOutcome() const;
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
private:
    Formulas subs;
};

}

#endif
