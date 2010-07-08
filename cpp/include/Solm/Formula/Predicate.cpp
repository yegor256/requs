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
 * @version $Id: Silent.h 2095 2010-05-28 07:26:19Z yegor256@yahoo.com $
 */

#include <boost/algorithm/string/join.hpp> // join()
#include "Solm/Formula/Predicate.h"

const string Predicate::_toString() const {
    return name + "(" + boost::algorithm::join(Parametrized<Predicate>::getVars(), ", ") + ")";
}

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
 * @version $Id: Function.h 2196 2010-07-02 06:34:19Z yegor256@yahoo.com $
 */

/**
 * Create an outcome of this formula, list of facts
 */
Outcome Function::getOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const { 
    // we are asserting the the arg is NUMBER
    if (name == F_NUMBER) {
        return numberOutcome(f, m);
    }
    // we are asserting the the arg is TEXT
    if (name == F_TEXT) {
        return textOutcome(f, m);
    }
    // we are asserting the the arg is ACTOR
    if (name == F_ACTOR) {
        return actorOutcome(f, m);
    }
    // we are asserting the the arg is SUD
    if (name == F_SUD) {
        return sudOutcome(f, m);
    }
    
    if (!rqdql::get<Solm>().hasDeclaration(name)) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Function '%s' is absent, can't calculate its outcome")) % name).str()
        );
        return Outcome();
    }
    
    Declaration* d = rqdql::get<Solm>().getDeclaration(name);
    if (d->countVars() != countVars()) {
        rqdql::get<rqdql::Logger>().log(
            this,
            (boost::format(rqdql::_t("Function '%s' expects %d params, but %d provided")) 
                % d->getName()
                % d->countVars()
                % countVars()
            ).str()
        );
        return Outcome();
    }
    
    return d->getFormula()->getOutcome(
        f, 
        Snapshot::makeMapping(
            this, 
            rqdql::get<Solm>().getDeclaration(name)
        )
    );
}

/**
 * Create an outcome of this formula, list of facts
 * @see getOutcome()
 */
Outcome Function::numberOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const {
    if (countVars() != 1) {
        throw rqdql::Exception(
            boost::format("Exactly one arg expected by %s(), but %d provided") % name % countVars()
        );
    }
    Snapshot s = f.getSnapshot();
    string var = m.map(getVar());
    if (!s.hasName(var)) {
        throw rqdql::Exception(
            boost::format("Variable '%s' (globally '%s') is not found in snapshot (%s)") 
                % getVar() 
                % var
                % (s.getNames().size() ? boost::algorithm::join(s.getNames(), ", ") : "empty")
        );
    }
    
    // everything goes fine and the variable is set to NUMBER
    Fact positive;
    positive.setFormula(this);
    Snapshot positiveSnapshot = s;
    positiveSnapshot.getByName(var).setValue((boost::format("%d") % (rand() % 100 + 1)).str());
    positiveSnapshot.getByName(var).setType(F_NUMBER);
    positive.setSnapshot(positiveSnapshot);
    
    // invalid value trying to save into NUMBER
    Fact negative;
    negative.setFormula(this);
    negative.setException(rqdql::_t("Invalid value for NUMBER"));
    Snapshot negativeSnapshot = s;
    negativeSnapshot.getByName(var).setValue("\"test\"");
    negative.setSnapshot(negativeSnapshot);
    
    return Outcome() << positive;
}

/**
 * Create an outcome of this formula, list of facts
 * @see getOutcome()
 */
Outcome Function::textOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const {
    return Outcome();
}

/**
 * Create an outcome of this formula, list of facts
 * @see getOutcome()
 */
Outcome Function::actorOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const {
    return Outcome();
}

/**
 * Create an outcome of this formula, list of facts
 * @see getOutcome()
 */
Outcome Function::sudOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const {
    return Outcome();
}
