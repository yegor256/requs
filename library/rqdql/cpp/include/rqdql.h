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
#include <string>

// boost libraries
#include "boost/format.hpp"

// template <class T> void yyConcat(std::vector<T*>*&, std::vector<T*>*&, T*);
// template <class T> void yyAppend(std::vector<T*>*&, T*);
// template <class T> void yySave(T*&, T*);
void yySet(std::string*&, boost::format);
void yySet(std::string*&, char*&);

// project files
#include "Scope.h"

typedef union {
    std::string* name;
    int num;
    rqdql::UseCase* uc;
    rqdql::Classe* classe;
} YYSTYPE;

// bison/flex file
// this define will protect us against BISON default YYSTYPE
#define YYSTYPE_IS_DECLARED 1
#define YYSTYPE_IS_TRIVIAL 1
#include "symbols.h"

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
    void log(LogLevel, const boost::format&);
    void log(const std::string&);
    void log(const boost::format&);
    
}

#endif
