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

#include <string>
#include <vector>
#include <boost/format.hpp>
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Solm.h"
#include "Solm/Term.h"

solm::Solm::Solm() : solm::Term("(and)") { 
    /* that's it */ 
}

const double solm::Solm::ambiguity() const {
    return 0.5; // just a stub
}

