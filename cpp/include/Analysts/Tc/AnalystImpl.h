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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file has to be included ONLY from Analytics.h
 */

/**
 * Retrieve all known test cases
 * @todo we find ONLY ONE predecessor for now
 */
vector<TestCase*> Analyst::retrieve() const {
    using namespace solm;
    // retrieve all possible outcomes from all formulas
    Formula::Formulas f = rqdql::get<Solm>().getFormulas();
    vector<Outcome> outcomes;
    for (Formula::Formulas::const_iterator i = f.begin(); i != f.end(); ++i) {
        outcomes.push_back((*i)->getOutcome());
    }
    
    // Retrieve all fact paths
    vector<FactPath> paths;
    for (vector<Outcome>::const_iterator i = outcomes.begin(); i != outcomes.end(); ++i) {
        vector<FactPath> p = (*i).getPaths();
        paths.insert(paths.end(), p.begin(), p.end());
    }
    
    // Order all paths by size, shortest comes first
    // Just in order to make further searching faster
    sort(paths.begin(), paths.end());
    
    // optimize the collection of PATH-s
    // @todo do it one day...
    
    // create test cases, one by one
    vector<TestCase*> tcs;
    for (vector<FactPath>::const_iterator p = paths.begin(); p != paths.end(); ++p) {
        TestCase* tc = new TestCase(*p);

        // set unique name of the use case
        // @todo this is just a stub
        tc->setName((boost::format("TC%d") % (tcs.size() + 1)).str());
        
        // add this TC to the list
        tcs.push_back(tc);
    }
    
    // remove similar test cases
    tcs.resize(unique(tcs.begin(), tcs.end()) - tcs.begin());
    
    return tcs;
}

