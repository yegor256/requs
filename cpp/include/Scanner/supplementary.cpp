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
 * @version $Id: supplementary.h 2281 2010-07-11 10:07:12Z yegor256@yahoo.com $
 */

#include <stdarg.h>
#include <string>
#include <boost/format.hpp>
#include "Scanner/supplementary.h"
#include "rqdql.h"
#include "Logger.h"

LogLevel level;

void yyerror(const char *error, ...) {
    // if (YYRECOVERING()) {
    //     return;
    // }
    va_list args;
    va_start(args, error);
    char s[1000];
    vsprintf(s, error, args);
    va_end(args);
    rqdql::get<rqdql::Logger>().log((int)yylloc.first_line, s);
}
    
void lyyerror(YYLTYPE t, const char *error, ...) {
    va_list args;
    va_start(args, error);
    char s[1000];
    vsprintf(s, error, args);
    va_end(args);
    rqdql::get<rqdql::Logger>().log((int)t.first_line, s);
}

inline void protocol(YYLTYPE t, void* x) {
    rqdql::get<rqdql::Logger>().addSubject(x, t.first_line);
}

void yySet(std::string*& lhs, const boost::format& rhs) {
    lhs = new std::string(rhs.str());
}

void yySet(std::string*& lhs, char*& rhs) {
    lhs = new std::string(rhs);
}

void log(const LogLevel lvl, const std::string& line) {   
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


void log(const std::string& line) {
    return log(L_DEBUG, line);
}

void log(const boost::format& line) {
    return log(L_DEBUG, line.str());
}

void log(const LogLevel lvl, const boost::format& line) {
    return log(lvl, line.str());
}
