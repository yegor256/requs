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

#include "rqdql.h"
#include <stdarg.h>
#include <iostream>
#include <vector>

using namespace std;

rqdql::LogLevel rqdql::level = L_ERROR;

// explicit instantiation, see Stroustrup C.13.10
// using rqdql::scope::Action;
// template void yyConcat<Action>(vector<Action*>*&, vector<Action*>*&, Action*);
// template void yyAppend<Action>(vector<Action*>*&, Action*);
// template void yySave<Action>(Action*&, Action*);

// explicit instantiation, see Stroustrup C.13.10
// using rqdql::scope::Statement;
// template void yyConcat<Statement>(vector<Statement*>*&, vector<Statement*>*&, Statement*);
// template void yyAppend<Statement>(vector<Statement*>*&, Statement*);
// template void yySave<Statement>(Statement*&, Statement*);

// explicit instantiation, see Stroustrup C.13.10
// template void yySave<Statement::LeftName>(Statement::LeftName*&, Statement::LeftName*);

// explicit instantiation, see Stroustrup C.13.10
// using rqdql::scope::Object;
// template void yyConcat<Object>(vector<Object*>*&, vector<Object*>*&, Object*);
// template void yyAppend<Object>(vector<Object*>*&, Object*);
// template void yySave<Object>(Object*&, Object*);

// template <class T> void yyConcat(vector<T*>*& array, vector<T*>*& current, T* item) {
//     if (current) {
//         array = new vector<T*>(*current);
//     } else {
//         array = new vector<T*>;
//     }
//     array->push_back(item);
// }
// 
// template <class T> void yyAppend(vector<T*>*& array, T* item) {
//     array = new vector<T*>;
//     array->push_back(item);
// }
// 
// template <class T> void yySave(T*& lhs, T* rhs) {
//     lhs = rhs;
// }
// 
void yySet(string*& lhs, boost::format rhs) {
    lhs = new string(rhs.str());
}

void yySet(string*& lhs, char*& rhs) {
    lhs = new string(rhs);
}

void rqdql::log(const std::string& line) {
    return log(L_DEBUG, line);
}

void rqdql::log(const boost::format& line) {
    return log(L_DEBUG, line.str());
}

void rqdql::log(const rqdql::LogLevel lvl, const boost::format& line) {
    return log(lvl, line.str());
}

/**
 * To log a line
 */
void rqdql::log(const rqdql::LogLevel lvl, const std::string& line) {   
    std::string label;
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
    if (lvl >= rqdql::level) {
        cout << '[' << label << "] " << line << endl;
    }
}

