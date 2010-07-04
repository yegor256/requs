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
 * @version $Id: ScopeTest.cpp 1487 2010-04-01 08:45:47Z yegor256@yahoo.com $
 */

#include "../AbstractTestCase.h"

void testSimpleOperationsWithTestCases() {
    using namespace analysts::tc;
    
    // solm::FactPath fp;
    // fp.push_back(solm::Fact(new solm::Silent("'test"), true));
    // fp.push_back(solm::Fact(new solm::Silent("'test"), true));
    // TestCase tc(fp);
    // TestCase tc2 = tc;
    // BOOST_REQUIRE(tc == tc2);
}

void testFactsRetrievalWorks() {
    using namespace analysts::tc;
    rqdql::get<rqdql::Scanner>().scan(getFile("sample1.txt"));
    rqdql::get<proxy::Proxy>().inject();
    vector<TestCase*> v;
    v = rqdql::get<Analyst>().retrieve();
    
    BOOST_REQUIRE(v.size() > 0);
    cout << v.size() << " test cases found" << endl;
    for (vector<TestCase*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        cout << (*i)->getName() << ":\n" /*<< (*i)->toString() << endl*/ << endl;
    }
}

vector<testMethod> suite() {
    vector<testMethod> v;
    v.push_back(&testSimpleOperationsWithTestCases);
    v.push_back(&testFactsRetrievalWorks);
    return v;
}
