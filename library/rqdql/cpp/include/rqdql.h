/**
 *
 * FaZend.com, Fully Automated Zend Framework
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * FaZend.com. located at www.fazend.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

#ifndef __INCLUDE_RQDQL_H
#define __INCLUDE_RQDQL_H

// system libraries
#include <iostream>
#include <string>
using namespace std;

// boost libraries
#include "boost/format.hpp"

// logger
#include "Logger.h"

namespace rqdql {
    
    class Exception {
    public:
        Exception(const string& s) : message(s) { /* that's it */ }
        const string& getMessage() { return message; }
    private:
        string message;
    };

    /**
     * Different levels of logging
     */
    enum LogLevel {
        L_DEBUG   = 1,
        L_VERBOSE = 2,
        L_INFO    = 3,
        L_WARNING = 4,
        L_ERROR   = 5
    };
    extern LogLevel level;
    
    /**
     * To log a line
     */
    inline void log(const LogLevel lvl, const string& line) {   
        string label;
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
            rqdql::Logger::getInstance().log(0, "[" + label + "] " + line);
        }
    }

    
    inline void log(const string& line) {
        return log(L_DEBUG, line);
    }

    inline void log(const boost::format& line) {
        return log(L_DEBUG, line.str());
    }

    inline void log(const LogLevel lvl, const boost::format& line) {
        return log(lvl, line.str());
    }

    inline void yySet(string*& lhs, boost::format rhs) {
        lhs = new string(rhs.str());
    }

    inline void yySet(string*& lhs, char*& rhs) {
        lhs = new string(rhs);
    }

}

#endif
