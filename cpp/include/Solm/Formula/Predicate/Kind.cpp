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
 * @version $Id: Silent.h 2098 2010-05-28 09:50:32Z yegor256@yahoo.com $
 */

/**
 * Create an outcome of this formula, list of facts
 *
 * arg#0: what is created
 * arg#1: who just did it, actor
 *
 * @see Analyst::retrieve()
 */
Outcome Created::getOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const { 
    // copy an existing snapshot from the FACT just passed
    Snapshot s = f.getSnapshot();

    // get the first argument of CREATED() formula
    string var = getVar();
    
    // this variable already exists in the scope or we should create it?
    Snapshot::Object& obj = s.hasName(var) ? s.getByName(var) : s.create(var);
    
    // no matter what we should set an ID to the variable
    // since it's instantiated now
    s.assignId(obj);
    
    // mark this object with an ACL RULE that tells us who
    // had an ability to create this object
    obj.addRule(
        Snapshot::Object::AclRule(
            Snapshot::Object::AclRule::CREATE, // type of ACL rule
            findActor(s) // method from Manipulator class
        )
    );

    // this is the FACT we are producing by this formula
    return Outcome() << Fact().setFormula(this).setSnapshot(s); 
}
