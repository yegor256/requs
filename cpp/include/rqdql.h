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
#include <exception>

using namespace std;

// boost libraries
#include "boost/format.hpp"

typedef union {
    string* name;
    int num;
    void* ptr;
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
     * To log a line
     */
    inline void log(const LogLevel lvl, const string& line) {   
        string label;
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
            cout << '[' << label << "] " << line << endl;
        }
    }

    
    inline void log(const string& line) {
        return log(L_DEBUG, line);
    }

    inline void log(const boost::format& line) {
        return log(L_DEBUG, line.str());
    }

    inline void log(const LogLevel lvl, const boost::format& line) {
        return log(lvl, line.str());
    }

    /* exception */
    class Exception {
    public:
        Exception(const string& s) : msg(s) { /* that's it */ }
        Exception(const boost::format& s) : msg(s.str()) { /* that's it */ }
        string getMessage() const { return msg; }
    private:
        string msg;
    };

    inline void yySet(string*& lhs, boost::format rhs) {
        lhs = new string(rhs.str());
    }

    inline void yySet(string*& lhs, char*& rhs) {
        lhs = new string(rhs);
    }

}

#endif
