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
#include "Solm/Term.h"
using namespace solm;
using std::string;

void testTerm(const string& t) {
    Term term = Term(t);
    BOOST_TEST_MESSAGE(t + " --> " + (std::string)term);
    // BOOST_CHECK(term.is(Term::T_ATOM) && !t.is(Term::T_NUMBER));
}

BOOST_AUTO_TEST_SUITE(TermTest)

BOOST_AUTO_TEST_CASE(testDifferentFormatsAreOK) {
    // simple objects and atoms
    testTerm("mary.");
    testTerm("45.890.");
    testTerm("'this is text'.");
    
    // simple facts
    testTerm("father_of(john, mary).");
    testTerm("age_of(smith, 45).");
    testTerm("child_of(emily, parents(alex, alice)).");
    testTerm("mistique_character(king, 'Persia'), king('Arthur').");
    testTerm("in_class(john, mary_smith, peter, alex_Wilson_3rd).");
    
    // specific formatting
    testTerm("child(X, Y) :- parent(Y, X)."); // rule definition
    testTerm("P < 67."); // number of P is less than 67
    testTerm("P is 67."); // P should be equal to 67
    testTerm("X = Y."); // X is the same as Y
    testTerm("X =:= Y."); // X and Y stand for the same number/value
    testTerm("X =\\= Y."); // X and Y stand for the different values/numbers
    
    // simple questions
    testTerm("parent(X, mary)."); // who is a parent of mary?
    testTerm("prince(X), X =\\= 'Arthur'."); // who is a prince and is not "Arthur"?
}

BOOST_AUTO_TEST_SUITE_END()
