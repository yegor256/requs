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

#ifndef __INCLUDE_SCOPE_ANALYSTS_TC_H
#define __INCLUDE_SCOPE_ANALYSTS_TC_H

#include <vector>
#include "Analysts/Tc/TestCase.h"

namespace analysts {

/**
 * Builder of Test Cases
 */
class Tc {

public:

    /**
     * Retrieve full list of test cases, found in scope
     */
    std::vector<tc::TestCase> retrieve() const;

private:

};

}

#endif
