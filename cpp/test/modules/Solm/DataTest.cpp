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
#include "Solm/Data.h"
#include "Solm/Term.h"
using namespace solm;

BOOST_AUTO_TEST_SUITE(DataTest)

BOOST_AUTO_TEST_CASE(testWeCanResolveSimpleFactsAndRules) {
    // Data d;
    // 
    // // here we add simple prolog-style facts
    // d += Term("kid(john, mary).");
    // d += Term("kid(john, peter).");
    // 
    // // now we're asking for a list of X that satisfy this rule
    // Answer a = d.question(Term("kid(john, X)."));
    // 
    // BOOST_REQUIRE(a);
    // BOOST_REQUIRE(a.has("X"));
    // std::vector<std::string> v = a[std::string("X")];
    // BOOST_REQUIRE(std::find(v.begin(), v.end(), "mary") != v.end()); // "mary" is there
}

BOOST_AUTO_TEST_SUITE_END()
