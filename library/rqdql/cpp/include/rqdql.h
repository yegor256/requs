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
#include <vector>

// boost libraries
#include "boost/format.hpp"

// project files
#include "scope.h"
#include "om.h"

using namespace std;
using namespace rqdql::scope;

typedef union {
    string* name;
    vector<Statement>* statements;
    Statement* statement;
    vector<Action>* actions;
    Action* action;
} YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1

template <class T, class D> void yyAdd(T*&, T*&, D*&);
template <class T, class D> void yySet(T*&, D*&);
template <class T> void yySet(T*&, T*&);
void yySet(string*&, boost::format);
void yySet(string*&, char*&);

// bison/flex file
// this INCLUDE shall go AFTER our declaration of YYSTYPE
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
    extern LogLevel level;
    
    /**
     * Simple logger, that filters messages by their types
     * @see LogLevel
     * @see rqdql.l
     */
    void log(LogLevel, const std::string&);
    void log(const std::string&);
    void log(const boost::format&);
    
}

#endif
