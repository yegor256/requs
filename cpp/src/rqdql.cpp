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

using namespace std;
using namespace rqdql;

rqdql::LogLevel rqdql::level = L_ERROR;

// explicit instantiation, see Stroustrup C.13.10
template void yyAdd<vector<Action>, Action>(vector<Action>*&, vector<Action>*&, Action*&);
template void yySet<vector<Action>, Action>(vector<Action>*&, Action*&);

template <class T, class D> void yyAdd(T*& array, T*& current, D*& item) {
    array = new T(*current);
    array->push_back(*item);
}

template <class T, class D> void yySet(T*& array, D*& item) {
    array = new T;
    array->push_back(*item);
}

template <class T> void yySet(T*& lhs, T*& rhs) {
    lhs = new T(*rhs);
}

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

/**
 * To log a line
 */
void rqdql::log(const LogLevel lvl, const std::string& line) {   
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

