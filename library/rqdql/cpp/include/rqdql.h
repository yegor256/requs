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

#include "../rqdql.tab.h"
#include "Scope.h"

#include <iostream>
    using namespace std;

extern int yyparse();
void yyerror(const char *error, ...);
void lyyerror(YYLTYPE t, const char *error, ...);
extern int yylex(void);
extern int yylineno;

/**
 * Kind of global registry, in order to avoid global vars and funcs
 *
 * @package
 */
class rqdql
{
public:
    
    /**
     * Different levels of logging
     */
    typedef enum {
        debug = 1,
        verbose = 2,
        info = 3,
        warning = 4,
        error = 5
    } LogLevel;
    
    /**
     * Constructor
     */
    rqdql(LogLevel level) : _verboseLevel(level)
    {
        // ..
    };
    
    /**
     * Set log level to use
     *
     * @param Level of messaging to use, see LogLevel type
     * @see LogLevel
     * @see rqdql.l
     */
    void setVerboseLevel(LogLevel level);
    
    /**
     * More convenient way to manage strings, mostly used inside YACC code
     *
     * @param Mask to be passed to C-func sprintf()
     * @param Some params to sprintf(), if required
     * @return New string, in heap
     * @see rqdql.y
     */
    char* sprintf(const char*, ...);
    
    /**
     * Simple logger, that filters messages by their types
     *
     * @param Level of messaging to use, see LogLevel type
     * @param Mask to pass to sprintf()
     * @param More params if required
     * @see LogLevel
     * @see rqdql.l
     */
    void log(LogLevel, const char*, ...);
    
    /**
     * Get the general scope object
     */
    Scope& scope()
    {
        return _scope;
    };

private:

    /**
     * Messages with this level we will log
     */
    int _verboseLevel;    
    
    // Scope instance
    Scope _scope;
    
};

extern rqdql rq;

#endif
