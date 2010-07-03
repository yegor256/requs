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
 * @version $Id: Silent.h 2098 2010-05-28 09:50:32Z yegor256@yahoo.com $
 */

/**
 * Create an outcome of this formula, list of facts
 */
Outcome Deleted::getOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const { 
    Fact fact;
    fact.setFormula(this);
    Snapshot s = f.getSnapshot();

    string var = getVar();
    if (!s.hasName(var)) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Can't DELETE '%s' since it's absent yet")) % var).str()
        );
        return Outcome();
    }
    Snapshot::Object& obj = s.getByName(var);
    s.deassignId(obj);
    obj.addRule(Snapshot::Object::AclRule(Snapshot::Object::AclRule::DELETE, findActor(s)));

    fact.setSnapshot(s);
    return Outcome() << fact; 
}
