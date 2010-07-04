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

#include <stdarg.h>
#include "Logger.h"

/**
 * Called when error is found in parser
 */
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

/**
 * Protocol the appearance of an object in input stream
 * @see rqdql.y
 */
inline void protocol(YYLTYPE t, void* x) {
    rqdql::get<rqdql::Logger>().addSubject(x, t.first_line);
}
