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

#include "rqdql.h"
#include <stdarg.h>

// global object
rqdql rq(rqdql::error);

/**
 * to set verbose level
 */
void rqdql::setVerboseLevel(LogLevel level)
{
    _verboseLevel = level;
}

/**
 * To make sprintf() work simply, as in PHP
 */
char* rqdql::sprintf(const char* mask, ...)
{
    va_list args;
    va_start(args, mask);

    char s[500];
    vsprintf(s, mask, args);
    return strdup(s);
}

/**
 * To log a line
 */
void rqdql::log(LogLevel level, const char* mask, ...)
{   
    string label;
    switch (level) {
        case debug:
            label = "DEBUG";
            break;
        case verbose:
            label = "VERB";
            break;
        case info:
            label = "INFO";
            break;
        case warning:
            label = "WARN";
            break;
        case error:
            label = "ERR";
            break;
    }
    if (level >= _verboseLevel) {
        va_list args;
        va_start(args, mask);
        cout << '[' << label << "] ";
        vprintf(mask, args);
        cout << endl;
    }
}

