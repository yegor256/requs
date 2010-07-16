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
 * @version $Id$
 */

#include <boost/test/unit_test.hpp>
#include <string>
#include "Solm/Predicate.h"
#include "Solm/Chain.h"
#include "Solm/Term.h"
using namespace solm;

BOOST_AUTO_TEST_SUITE(PredicateTest)

BOOST_AUTO_TEST_CASE(testSimplePredicateCanBeResolved) {
    Predicate p("(exists x (eq x 5))");
    
    // resolve the predicate on an empty Database
    Chain c = p + Term("true.");
    Term t = (Term)c;
    
    // here we assume that Data has the following rules/facts:
    // value_of(x, 5)
    Term a = t / Term("value_of(x, V).");
    
    // the value of V should be 5!
    BOOST_REQUIRE((bool)a);
    BOOST_REQUIRE((std::string)a == "V = 5");
}

BOOST_AUTO_TEST_SUITE_END()
