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

#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include "rqdql.h"
#include "Logger.h"

const std::string rqdql::_t(const std::string& s) {
    return s;
}

template <typename T> T& rqdql::get() {
    static T* t;
    if (!t) {
        t = new T();
    }
    return *t;
}

void rqdql::log(const LogLevel lvl, const std::string& line) {   
    std::string label;
    switch (lvl) {
        case L_DEBUG:
            label = "DEBUG";
            break;
        case L_VERBOSE:
            label = "VERB";
            break;
        case L_INFO:
            label = "INFO";
            break;
        case L_WARNING:
            label = "WARN";
            break;
        case L_ERROR:
            label = "ERR";
            break;
    }
    if (lvl >= level) {
        rqdql::get<rqdql::Logger>().log(0, "[" + label + "] " + line);
    }
}


void rqdql::log(const std::string& line) {
    return log(L_DEBUG, line);
}

void rqdql::log(const boost::format& line) {
    return log(L_DEBUG, line.str());
}

void rqdql::log(const LogLevel lvl, const boost::format& line) {
    return log(lvl, line.str());
}

std::string rqdql::cutLongLine(const std::string& s, size_t len = 50) {
    if (s.length() < len) {
        return s;
    }
    return s.substr(0, len - 3) + "..."; 
}
