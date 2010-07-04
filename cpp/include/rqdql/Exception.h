/**
 *

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

#ifndef __INCLUDE_RQDQL_EXCEPTION_H
#define __INCLUDE_RQDQL_EXCEPTION_H

#include <string>
#include "boost/format.hpp"

namespace rqdql {

class Exception {
public:
    Exception() : message("no details") { /* that's it */ }
    Exception(const std::string& s) : message(s) { /* that's it */ }
    Exception(const boost::format& s) : message(s.str()) { /* that's it */ }
    const std::string& getMessage() { return message; }
private:
    std::string message;
};
    
}

#endif
