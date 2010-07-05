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
 * @version $Id: Solm.h 2246 2010-07-05 15:55:40Z yegor256@yahoo.com $
 */

#define BOOST_TEST_MODULE rqdql
#include <boost/test/included/unit_test.hpp>

/**
 * All test suites/cases are in *Test.cpp files, which will
 * be LINKED together with this one, in order to create one
 * single test module. That's why we're using "included/unit_test.hpp"
 * here instead of "unit_test.hpp"
 *
 * For more information read: http://www.boost.org/doc/libs/1_42_0/libs/test/doc/html/index.html
 */