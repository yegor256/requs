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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file has to be included ONLY from Analytics.h
 */

#ifndef __INCLUDE_SCOPE_ANALYSTS_TC_TESTCASE_H
#define __INCLUDE_SCOPE_ANALYSTS_TC_TESTCASE_H

#include <string>

namespace analysts {
namespace tc {
    
/**
 * One Test Case, as an instruction to a tester
 */
class TestCase {

public:

    /**
     * Public constructor
     */
    TestCase() { /* that's it */ }

    /**
     * Convert it to XMI
     */
    const std::string getXmi() const;

private:

    /**
     *
     */
    // solm::FactPath factPath;

};

}
}

#endif
