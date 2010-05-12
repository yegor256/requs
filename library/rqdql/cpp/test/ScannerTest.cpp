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

#include <boost/test/minimal.hpp>
#include <string>
#include <iostream>
#include "rqdql.h"
#include "Scanner.h"
#include "Proxy.h"
#include "Solm.h"
#include "Logger.h"
using namespace std;

rqdql::LogLevel rqdql::level = L_DEBUG;

void setUp() {
    rqdql::Logger::getInstance().clear();
    proxy::Proxy::getInstance().clear();
    solm::Solm::getInstance().clear();
}

void tearDown() {
    if (!rqdql::Logger::getInstance().empty()) {
        cout << "Log report is not empty:" << endl << rqdql::Logger::getInstance().getReport();
    }
}

void testSimpleParsing() {
    setUp();
    rqdql::Scanner::getInstance().scan(
        "ActorUser is a \"human being with identity. Also it is our client.\".\n"
        "ActorUser is an ActorVisitor.\n"
        "InvestorApplication includes:\n"
            "ticket: OnlineTicket \"where this application is discussed and approved\"; \n"
            "email, \n"
            "agent: ActorAgent; \n"
            "phone: \"a telephone number\"; and \n"
            "name; \n"
            "introduction email: \"text message when account is registered\".\n"
        "Name of InvestorApplication includes: first name and last name.\n"
        "UC8.3 where we invest into InvestmentProject: \"something for the future\".\n"
        "UC8.1 where somebody speculates:\n"
            "1. We get from ActorLegacy.\n"
            "2. We invest into InvestmentProject (the project).\n"
            "3. Somebody turns into ActorUser (the user).\n"
            "4. The user \"buys specific units in\" the project.\n"
            "5. \"We do something strange\".\n"
            "6. ActorOperator pays to us \"when necessary\".\n"
            "7. \"Every week\" we payearnings to the user.\n"
            "8. The user transfersunits to ActorUser.\n"
        "UC8.1 alternative flow:\n"
            "4a) If \"ticket is rejected\":\n"
                "1. SUD sends rejection email of the application.\n"
                "2. Failure \"application rejected\".\n"
            "4a1a) If \"email of the application is empty\":\n"
                "1. Failure \"anonymous application rejected\".\n"
    );
    proxy::Proxy::getInstance().inject();
    BOOST_CHECK(rqdql::Logger::getInstance().empty());
    tearDown();
}

void testSimpleParsingWithErrors() {
    setUp();
    rqdql::Scanner::getInstance().scan(
        "ActorUser is a human being with identity. Also it is our client.\n"
        "ActorUser is an ActorVisitor or something else.\n"
        "Name of InvestorApplication includes: first name and last name.\n"
    );
    proxy::Proxy::getInstance().inject();
    BOOST_CHECK(!rqdql::Logger::getInstance().empty());
    tearDown();
}

int test_main(int, char *[]) {
    testSimpleParsing();
    testSimpleParsingWithErrors();
    
    return 0;
}
