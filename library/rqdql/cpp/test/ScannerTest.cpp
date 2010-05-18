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

void testSimpleParsing() {
    setUp();
    rqdql::Scanner::getInstance().scan(getFile("sample1.txt"));
    proxy::Proxy::getInstance().inject();
    rqdql::Logger::getInstance().reportLinks();
    tearDown();

    // no errors there!
    BOOST_REQUIRE(!rqdql::Logger::getInstance().hasErrors());
    
    // but the log should NOT be empty
    BOOST_REQUIRE(!rqdql::Logger::getInstance().empty());
}

void testSimpleParsingWithErrors() {
    setUp();
    rqdql::Scanner::getInstance().scan(
        "ActorUser is a human being with identity. Also it is our client.\n"
        "ActorUser is an ActorVisitor or something else.\n"
        "Name of InvestorApplication includes: first name and last name.\n"
    );
    proxy::Proxy::getInstance().inject();
    tearDown();

    BOOST_REQUIRE(!rqdql::Logger::getInstance().empty());
}

void testCleanParsing() {
    setUp();
    rqdql::Scanner::getInstance().scan(getFile("valid.txt"));
    proxy::Proxy::getInstance().inject();
    rqdql::Logger::getInstance().reportLinks();
    tearDown();

    BOOST_REQUIRE(!rqdql::Logger::getInstance().hasErrors());
    BOOST_REQUIRE(solm::Solm::getInstance().getAmbiguity() > 0);
}

int test_main(int, char *[]) {
    testSimpleParsing();
    testSimpleParsingWithErrors();
    testCleanParsing();
    
    return 0;
}
