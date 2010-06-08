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
 */

/**
 * Create an outcome of this formula, list of facts
 */
Outcome Function::getOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const { 
    // we are asserting the the arg is NUMBER
    if (name == F_NUMBER) {
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
        positiveSnapshot.getByName(var).setValue("123");
        positive.setSnapshot(positiveSnapshot);
        
        // invalid value trying to save into NUMBER
        Fact negative;
        negative.setFormula(this);
        negative.setException("Invalid value for NUMBER");
        Snapshot negativeSnapshot = s;
        negativeSnapshot.getByName(var).setValue("\"test\"");
        negative.setSnapshot(negativeSnapshot);
        
        return Outcome() << positive;
    }
    
    if (!rqdql::get<Solm>().hasDeclaration(name)) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Function '%s' is absent, can't calculate its outcome")) % name).str()
        );
        return Outcome();
    }
    
    return rqdql::get<Solm>().getDeclaration(name)->getFormula()->getOutcome(
        f, 
        Snapshot::makeMapping(
            this, 
            rqdql::get<Solm>().getDeclaration(name)
        )
    );
}
