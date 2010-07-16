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
 * @version $Id: DataTest.cpp 2314 2010-07-15 09:21:38Z yegor256@yahoo.com $
 */

#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Solm/Term.h"
using namespace solm;
using std::string;

void testTerm(const string& t) {
    Term term = Term(t);
    BOOST_CHECK_EQUAL(t, (string)term);
    
    std::vector<string> flags;
    if (term.is(Term::T_ATOM)) {
        flags.push_back("A");
    }
    if (term.is(Term::T_TEXT)) {
        flags.push_back("T");
    }
    if (term.is(Term::T_NUMBER)) {
        flags.push_back("N");
    }
    if (term.is(Term::T_VARIABLE)) {
        flags.push_back("V");
    }
    if (term.is(Term::T_OBJECT)) {
        flags.push_back("O");
    }
    BOOST_TEST_MESSAGE(
        t + " --> " + (std::string)term 
        + " [" + boost::algorithm::join(flags, ",") + "]"
    );
}

BOOST_AUTO_TEST_SUITE(TermTest)

BOOST_AUTO_TEST_CASE(testInvalidFormatsRaiseExceptions) {
    BOOST_CHECK_THROW(testTerm("123true"), std::exception); // invalid name of the object
    BOOST_CHECK_THROW(testTerm("-Aksel"), std::exception); // invalid name

    // now let's make sure that we can successfuly parse terms
    // after the problems happened before
    testTerm("(like Klaus beer)"); 
}

BOOST_AUTO_TEST_CASE(testDifferentFormatsAreOK) {
    // simple objects and atoms
    testTerm("true");
    testTerm("mary");
    testTerm("(list victor peter 44 \"works?\")");
    testTerm("45.890");
    testTerm("\"this is text\"");
    
    // simple facts
    testTerm("(fatherOf john mary)");
    testTerm("(ageOf smith 45)");
    testTerm("(childOf emily (parents alex alice))");
    testTerm("(and (mistiqueCharacter king \"Persia\") (king \"Arthur\"))");
    testTerm("(inClass john marySmith peter AlexWilson)");
    testTerm("(and (eq a 1) (eq b 2))");
}

BOOST_AUTO_TEST_SUITE_END()
