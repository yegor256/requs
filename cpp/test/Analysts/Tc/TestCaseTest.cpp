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

#include "../../AbstractTestCase.h"

void testXmiIsProducedOutOfFactPath() {
    using namespace analysts::tc;
    
    solm::FactPath fp;
    fp.push_back(solm::Fact());
    fp.push_back(solm::Fact());
    TestCase tc(fp);
    
    // cout << tc.getXmi();
    // BOOST_REQUIRE(tc == tc2);
}

vector<testMethod> suite() {
    vector<testMethod> v;
    v.push_back(&testXmiIsProducedOutOfFactPath);
    return v;
}
