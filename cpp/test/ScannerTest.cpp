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
        rqdql::log("Log report is not empty:\n" + rqdql::Logger::getInstance().getReport());
    }
}

void testSimpleParsing() {
    setUp();
    rqdql::Scanner::getInstance().scan(
        "ActorUser: \"human being\"."
    );
    tearDown();
}

int test_main(int, char *[]) {
    testSimpleParsing();
    
    return 0;
}
