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
#include "Solm/Chain.h"
#include "Solm/Data.h"
using namespace solm;

BOOST_AUTO_TEST_SUITE(ChainTest)

BOOST_AUTO_TEST_CASE(testEmptyChainIsPositive) {
    Chain c;
    BOOST_CHECK((bool)c);
}

BOOST_AUTO_TEST_CASE(testVerticalChainingWorks) {
    Chain c;
    c += Data();
    c += Data();
    BOOST_CHECK_EQUAL(2, c.size());
    BOOST_CHECK((bool)c); // still positive
}

BOOST_AUTO_TEST_CASE(testHorizontalChainingWorks) {
    Chain c;
    c += Data();
    c << Data();
    BOOST_CHECK_EQUAL(1, c.size());
    BOOST_CHECK((bool)c); // still positive
}

BOOST_AUTO_TEST_SUITE_END()
