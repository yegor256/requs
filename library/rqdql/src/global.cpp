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
 * Error logger
 */
void rqdql::error(char* message)
{
    cerr << message << endl;
}

/**
 * Called when error is found in parser
 */
void yyerror(const char *error, ...)
{
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
            // yylloc.last_line,
            // yylloc.last_column,
            s
        );
        strcpy(s, s1);
    }
    rqdql::error(s);
}
    
void lyyerror(YYLTYPE t, const char *error, ...)
{
    // if (YYRECOVERING()) {
    //     return;
    // }
    va_list args;
    va_start(args, error);
    char s[500];
    vsprintf(s, error, args);
    if (t.first_line) {
        char s1[500];
        sprintf(
            s1, 
            "%d.%d error: %s",
            // t.first_line,
            // t.first_column,
            t.last_line,
            t.last_column,
            s
        );
        strcpy(s, s1);
    }
    rqdql::error(s);
}
    
int main(int argc, char** argv)
{
    cout << "rqdql v0.1\n";
    yyparse();
    return 0;
}

