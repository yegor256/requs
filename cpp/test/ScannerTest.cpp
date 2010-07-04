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
 * @version $Id: ScopeTest.cpp 1487 2010-04-01 08:45:47Z yegor256@yahoo.com $
 */

#include "AbstractTestCase.h"

void testSimpleParsing() {
    rqdql::get<rqdql::Scanner>().scan(getFile("sample1.txt"));
    rqdql::get<proxy::Proxy>().inject();
    BOOST_REQUIRE(rqdql::get<rqdql::Logger>().empty());
}

void testSimpleParsingWithErrors() {
    rqdql::get<rqdql::Scanner>().scan(
        "ActorUser is a human being with identity. Also it is our client.\n"
        "ActorUser is an ActorVisitor or something else.\n"
        "Name of InvestorApplication includes: first name and last name.\n"
    );
    rqdql::get<Proxy>().inject();

    BOOST_REQUIRE(!rqdql::get<rqdql::Logger>().empty());
}

void testCleanParsing() {
    rqdql::get<rqdql::Scanner>().scan(getFile("valid.txt"));
    rqdql::get<Proxy>().inject();

    BOOST_REQUIRE(rqdql::get<rqdql::Logger>().empty());
    BOOST_REQUIRE(rqdql::get<solm::Solm>().getAmbiguity() > 0);
}

vector<testMethod> suite() {
    vector<testMethod> v;
    v.push_back(&testSimpleParsing);
    v.push_back(&testSimpleParsingWithErrors);
    v.push_back(&testCleanParsing);
    return v;
}
