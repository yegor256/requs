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
 * @version $Id: Exception.h 2273 2010-07-09 18:29:48Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_RQDQL_EXCEPTION_H
#define __INCLUDE_RQDQL_EXCEPTION_H

#include <string>
#include <sstream>
#include <boost/format.hpp>

namespace rqdql {

/**
 * Test typer
 */
class Tt {

public:

    /**
     * Convert it to string
     */
    operator std::string() const;

private:

    /**
     * Stream to collect texts
     */
    std::stringstream _stream;

};

extern Tt tt;
    
}

#endif
