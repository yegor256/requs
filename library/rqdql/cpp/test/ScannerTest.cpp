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
#include <fstream>
#include "rqdql.h"
#include "Scanner.h"
#include "Proxy.h"
#include "Solm.h"
#include "Logger.h"
using namespace std;

rqdql::LogLevel rqdql::level = L_ERROR;

void setUp() {
    rqdql::Logger::getInstance().clear();
    proxy::Proxy::getInstance().clear();
    solm::Solm::getInstance().clear();
}

void tearDown() {
    if (!rqdql::Logger::getInstance().empty()) {
        cout << "Log report is not empty:" << endl << rqdql::Logger::getInstance().getReport() << endl;
    }
    cout << solm::Solm::getInstance().toString() << endl;
}

string getFile(const string& n) {
    ifstream f;
    f.open(string("test/samples/" + n).c_str());
    string buffer;
    if (!f.is_open()) {
        throw "failed to open sample file " + n;
    }
    while (!f.eof()) {
        string s;
        getline(f, s);
        buffer = buffer + s + "\n";
    }
    f.close();
    return buffer;
}

void testSimpleParsing() {
    setUp();
    rqdql::Scanner::getInstance().scan(getFile("sample1.txt"));
    proxy::Proxy::getInstance().inject();
    rqdql::Logger::getInstance().reportLinks();
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

void testCleanParsing() {
    setUp();
    rqdql::Scanner::getInstance().scan(getFile("valid.txt"));
    proxy::Proxy::getInstance().inject();
    rqdql::Logger::getInstance().reportLinks();
    BOOST_CHECK(!rqdql::Logger::getInstance().hasErrors());
    tearDown();
}

int test_main(int, char *[]) {
    // testSimpleParsing();
    // testSimpleParsingWithErrors();
    testCleanParsing();
    
    return 0;
}
