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
#include "Solm/Rule.h"
using namespace solm;

BOOST_AUTO_TEST_SUITE(RuleTest)

BOOST_AUTO_TEST_CASE(testDifferentFormatsAreOK) {
    Rule r;
    
    // simple facts
    r = Rule("father_of(john, mary).");
    BOOST_CHECK(r.isFact());
    r = Rule("age_of(smith, 45).");
    BOOST_CHECK(r.isFact());
    r = Rule("child_of(emily, parents(alex, alice)).");
    BOOST_CHECK(r.isFact());
    r = Rule("mistique_character(king, 'Persia'), king('Arthur').");
    BOOST_CHECK(r.isFact());
    r = Rule("in_class(john, mary_smith, peter, alex_Wilson_3rd).");
    BOOST_CHECK(r.isFact());

    // specific formatting
    r = Rule("child(X, Y) :- parent(Y, X)."); // rule definition
    BOOST_CHECK(!r.isFact());
    r = Rule("P < 67."); // number of P is less than 67
    BOOST_CHECK(!r.isFact());
    r = Rule("P is 67."); // P should be equal to 67
    BOOST_CHECK(!r.isFact());
    r = Rule("X = Y."); // X is the same as Y
    BOOST_CHECK(!r.isFact());
    r = Rule("X =:= Y."); // X and Y stand for the same number/value
    BOOST_CHECK(!r.isFact());
    r = Rule("X =\\= Y."); // X and Y stand for the different values/numbers
    BOOST_CHECK(!r.isFact());

    // simple questions
    r = Rule("parent(X, mary)."); // who is a parent of mary?
    BOOST_CHECK(!r.isFact());
    r = Rule("price(X), X =\\= 'Arthur'."); // who is a prince and is not "Arthur"?
    BOOST_CHECK(!r.isFact());
}

BOOST_AUTO_TEST_SUITE_END()
