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
#include <boost/shared_ptr.hpp>
#include "Solm/Formula/Variadic.h"
#include "Solm/Formula/True.h"
using namespace solm;

BOOST_AUTO_TEST_SUITE(VariadicTest)

BOOST_AUTO_TEST_CASE(testFormulaCanBeConstructed) {
    Variadic v;
    v += boost::shared_ptr<True>(new True());
    v += boost::shared_ptr<True>(new True());
    Chain c = v + Context();
    BOOST_CHECK((bool)c); // the chain is positive
}

BOOST_AUTO_TEST_SUITE_END()
