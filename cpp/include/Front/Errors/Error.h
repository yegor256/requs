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

#ifndef __INCLUDE_SCOPE_FRONT_ERRORS_ERROR_H
#define __INCLUDE_SCOPE_FRONT_ERRORS_ERROR_H

#include <string>

namespace front {

/**
 * Forward declaration
 */
class Errors;

namespace errors {
    
class Error {
public:
    int line;
    std::string message;
    Error() : line(0), message() { /* .. */ }
    bool operator< (const Error& e) const { return line < e.line; }
    bool operator== (const Error& e) const { return (line == e.line) && (message == e.message); }
private:
    friend class front::Errors;
    Error(int l, const std::string& m) : line(l), message(m) { /* .. */ }
};

}
}

#endif
