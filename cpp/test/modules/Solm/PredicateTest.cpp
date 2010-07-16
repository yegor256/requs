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
#include "Solm/Predicate.h"
using namespace solm;
using std::string;

void testPredicate(const string& p) {
    Predicate predicate = Predicate(p);
    BOOST_CHECK_EQUAL(p, (string)predicate);
    
    std::vector<string> flags;
    if (predicate.is(Predicate::T_ATOM)) {
        flags.push_back("A");
    }
    if (predicate.is(Predicate::T_TEXT)) {
        flags.push_back("T");
    }
    if (predicate.is(Predicate::T_NUMBER)) {
        flags.push_back("N");
    }
    if (predicate.is(Predicate::T_RULE)) {
        flags.push_back("R");
    }
    if (predicate.is(Predicate::T_FACT)) {
        flags.push_back("F");
    }
    if (predicate.is(Predicate::T_VARIABLE)) {
        flags.push_back("V");
    }
    if (predicate.is(Predicate::T_OBJECT)) {
        flags.push_back("O");
    }
    BOOST_TEST_MESSAGE(
        t + " --> " + (std::string)predicate 
        + " [" + boost::algorithm::join(flags, ",") + "]"
    );
}

BOOST_AUTO_TEST_SUITE(PredicateTest)

BOOST_AUTO_TEST_CASE(testEmptyPredicateWorksFine) {
    Predicate t;
    BOOST_REQUIRE((bool)t); // it's TRUE by default
}

BOOST_AUTO_TEST_CASE(testInvalidFormatsRaiseExceptions) {
    BOOST_CHECK_THROW(testPredicate("true"), std::exception); // DOT missed
    BOOST_CHECK_THROW(testPredicate("123true."), std::exception); // invalid name of the object
    BOOST_CHECK_THROW(testPredicate("-Aksel."), std::exception); // invalid name

    // now let's make sure that we can successfuly parse predicates
    // after the problems happened before
    testPredicate("like(klaus, beer)."); 
}

BOOST_AUTO_TEST_CASE(testDifferentFormatsAreOK) {
    // simple objects and atoms
    testPredicate("true.", "true");
    testPredicate("mary.", "mary");
    testPredicate("victor, peter, 44, 'works?'.", "victor, peter, 44, 'works?'");
    testPredicate("45.890.");
    testPredicate("'this is text'.");
    
    // simple facts
    testPredicate("father_of(john, mary).");
    testPredicate("age_of(smith, 45), true.", "age_of(smith, 45)");
    testPredicate("child_of(emily, parents(alex, alice)).");
    testPredicate("mistique_character(king, 'Persia'), king('Arthur').");
    testPredicate("in_class(john, mary_smith, peter, alex_Wilson_3rd).");
    testPredicate("a = 1, b = 2."/*, "a = 1, b = 2"*/);
    testPredicate("a(b < 4, c =\\= 'test', mary(1, 2))."/*, "a(b < 4, c =\\= 'test', mary(1, 2))"*/);
    
    // specific formatting
    testPredicate("child(X, Y) :- parent(Y, X)."); // rule definition
    testPredicate("P < 67."); // number of P is less than 67
    testPredicate("P is 67."); // P should be equal to 67
    testPredicate("X = Y."); // X is the same as Y
    testPredicate("X =:= Y.", "X =:= Y"); // X and Y stand for the same number/value
    testPredicate("X =\\= Y."); // X and Y stand for the different values/numbers
    
    // simple questions
    testPredicate("parent(X, mary).", "parent(X, mary)"); // who is a parent of mary?
    testPredicate("prince(X), X =\\= 'Arthur'."); // who is a prince and is not "Arthur"?
}

BOOST_AUTO_TEST_CASE(testDoubleTrueIsIgnored) {
    // this trailing TRUE should be ignored
    Predicate t("king(john), true.");
    BOOST_CHECK_EQUAL("king(john)", (string)t);

    // leading and trailing true will be ignored
    t = Predicate("true, true, woman(alex), true.");
    BOOST_CHECK_EQUAL("woman(alex)", (string)t);
}

BOOST_AUTO_TEST_CASE(testWeCanResolveSimpleFactsAndRules) {
    // here we add simple prolog-style facts
    Predicate t("kid(john, mary).");
    
    // now we're asking for a list of X that satisfy this rule
    Predicate a = t / Predicate("kid(john, X).");
    
    BOOST_REQUIRE((bool)a); // the predicate should be positive
    // BOOST_REQUIRE_EQUAL("X = mary", (string)a);
}

BOOST_AUTO_TEST_CASE(testWeCanResolveMoreComplexRules) {
    // here we add simple prolog-style facts
    Predicate t("kid(john, mary), kid(john, peter).");
    
    // now we're asking for a list of X that satisfy this rule
    Predicate a = t / Predicate("kid(john, X).");
    
    BOOST_REQUIRE((bool)a); // the predicate should be positive
    // BOOST_REQUIRE_EQUAL("X = mary", (string)a);
}

BOOST_AUTO_TEST_SUITE_END()
