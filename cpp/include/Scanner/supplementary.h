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

#ifndef __INCLUDE_SCANNER_SUPPLEMENTARY_H
#define __INCLUDE_SCANNER_SUPPLEMENTARY_H

#include <string>
#include <boost/format.hpp>
#include "Scanner/symbols.h"

extern void yyerror(const char*, ...);
extern void lyyerror(YYLTYPE, const char*, ...);

/**
 * Protocol the appearance of an object in input stream
 * @see rqdql.y
 */
extern void protocol(YYLTYPE, void*);

/**
 * Set left-hand value
 * @see rqdql.l
 */
extern void yySet(std::string*&, const boost::format&);
extern void yySet(std::string*&, char*&);

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

/**
 * Simple logging
 * @see rqdql.l
 */
extern void log(const LogLevel, const std::string&);
extern void log(const std::string&);
extern void log(const boost::format&);
extern void log(const LogLevel, const boost::format&);

#endif
