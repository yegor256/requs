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

#include <string>
#include <stdarg.h>
#include "rqdql.h"
#include "Scope.h"

/**
 * Called when error is found in parser
 */
void yyerror(const char *error, ...) {
    // if (YYRECOVERING()) {
    //     return;
    // }
    va_list args;
    va_start(args, error);
    char s[500];
    vsprintf(s, error, args);
    if (yylloc.first_line) {
        char s1[500];
        sprintf(
            s1, 
            "%d.%d error: %s",
            yylloc.first_line,
            yylloc.first_column,
            s
        );
        strcpy(s, s1);
    }
    std::string line = s;
    rqdql::log(rqdql::L_ERROR, line);
}
    
void lyyerror(YYLTYPE t, const char *error, ...) {
    va_list args;
    va_start(args, error);
    char s[500];
    vsprintf(s, error, args);
    if (t.first_line) {
        char s1[500];
        sprintf(
            s1, 
            "%d.%d error: %s",
            t.first_line,
            t.first_column,
            s
        );
        strcpy(s, s1);
    }
    std::string line = s;
    rqdql::log(rqdql::L_ERROR, line);
}
    
int main(int argc, char** argv) {
    // this option is set in Makefile, when building a project for tests
    #ifdef RQDQL_DEBUG
        rqdql::level = rqdql::L_DEBUG;
    #endif

    // entry log message
    rqdql::log(rqdql::L_INFO, "rqdql v0.1");

    // convert input stream into rqdql::om::Model class instance
    yyparse();
    
    // rqdql::log(boost::format("%d statements found") % rqdql::scope.size());
    // model.setScope(rqdql::scope::scope);
    // cout << model.query("") << endl;
    
    // bye-bye log message
    rqdql::log(rqdql::L_INFO, "end.");
    
    return 0;
}

