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

#ifndef __INCLUDE_SCOPE_LOGGER_MESSAGE_H
#define __INCLUDE_SCOPE_LOGGER_MESSAGE_H

#include <vector>
#include <string>

namespace rqdql {
namespace logger {

class Message {
public:
    Message(const std::vector<int>& v, const std::string& m) : lines(v), message(m) { /* that's it */ }
    const std::vector<int>& getLines() const { return lines; }
    const std::string& getMessage() const { return message; }
private:
    std::vector<int> lines;
    std::string message;
};
    
}
}

#endif
