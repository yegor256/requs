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
#include <string>
// #include "Proxy/Type.h"
// #include "Proxy/Signature.h"
// #include "Proxy/Signature/Place.h"

BOOST_AUTO_TEST_SUITE(PlaceTest)

BOOST_AUTO_TEST_CASE(testPlaceCanBeExplainedWithType) {
    // proxy::Signature sig("{alpha} asks {beta}");
    // proxy::signature::Place& p = sig.place("alpha");
    // p.explain(boost::shared_ptr<proxy::Type>(new proxy::Type()));
    // BOOST_CHECK(p.isExplained());
}

BOOST_AUTO_TEST_CASE(testPlaceCanBeExplained) {
    // proxy::Signature sig("{alpha} asks {beta}");
    // proxy::signature::Place& p = sig.place("alpha");
    // p.explain("binary file", "user");
    // BOOST_CHECK(p.isExplained());
    // BOOST_CHECK_EQUAL("binary file of the user", p.toString());
}

BOOST_AUTO_TEST_SUITE_END()
