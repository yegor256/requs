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
 * @version $Id: bootstrap.php 1190 2010-02-07 07:45:29Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_RQDQL_H
#define __INCLUDE_RQDQL_H

#include <iostream>
#include "scope.h"

// for rqdql.tab.h, see below
#include <vector>
using std::vector;
using namespace rqdql::scope;
#include "../rqdql.tab.h"

extern int yyparse();
extern void yyerror(const char *error, ...);
void lyyerror(YYLTYPE t, const char *error, ...);
extern int yylex(void);
extern int yylineno;

namespace rqdql {
    
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
    LogLevel level;
    
    /**
     * Simple logger, that filters messages by their types
     * @see LogLevel
     * @see rqdql.l
     */
    void log(LogLevel, std::string);
    void log(std::string line) {
        return log(L_DEBUG, line);
    }
    
}

#endif
