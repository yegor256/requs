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
 * @version $Id: ScopeTest.cpp 1487 2010-04-01 08:45:47Z yegor256@yahoo.com $
 */

#include "AbstractTestCase.h"

using namespace front;

void testSimpleScenario() {
    rqdql::get<rqdql::Scanner>().scan(getFile("sample1.txt"));
    rqdql::get<proxy::Proxy>().inject();
    
    rqdql::get<front::Front>().require("svg:type=ActorUser,uc=UC8.1");
    rqdql::get<front::Front>().require("errors");
    rqdql::get<front::Front>().require("metrics");
    rqdql::get<front::Front>().require("tc");
    rqdql::get<front::Front>().require("uml");
    rqdql::get<front::Front>().require("links");
    
    cout << rqdql::get<front::Front>().asXml() << endl;
}

vector<testMethod> suite() {
    vector<testMethod> v;
    v.push_back(&testSimpleScenario);
    return v;
}
