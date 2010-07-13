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
 * @version $Id: ChainTest.cpp 2278 2010-07-09 19:17:28Z yegor256@yahoo.com $
 */

#include <boost/test/unit_test.hpp>
#include "Solm/Predicate.h"
#include "Solm/Chain.h"
#include "Solm/Snapshot.h"
using namespace solm;

BOOST_AUTO_TEST_SUITE(PredicateTest)

BOOST_AUTO_TEST_CASE(testSimpleSentence) {
    Predicate p("(and true (eq x 5) (kind x \"ActorUser\"))");
    // BOOST_CHECK((bool)p);
}

BOOST_AUTO_TEST_SUITE_END()
