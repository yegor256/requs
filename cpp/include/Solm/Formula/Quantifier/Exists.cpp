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

/**
 * Create an outcome of this formula, list of facts
 */
Outcome Exists::getOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const { 
    // copy snapshot from the FACT provided
    Snapshot s = f.getSnapshot();
    
    // create an object that has to EXIST, with no type so far
    Snapshot::Object& obj = s.create(""); // no type
    
    // assign a name to this object
    s.assignName(obj, getVar());
    
    // maybe it's a SET, not a scalar variable?
    if (isupper(getVar().at(0))) {
        obj.setValue(vector<int>());
    }
    
    // create new fact
    Fact fact;
    fact.setFormula(this).setSnapshot(s);
    
    // create new outcome and add this fact to it
    Outcome out;
    out << fact;
    
    // add outcome from the formula beneath
    out += getFormula()->getOutcome(fact);
    
    // return this outcome created
    return out; 
}
