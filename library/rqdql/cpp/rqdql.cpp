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
 * @version $Id: rqdql.cpp 1746 2010-05-04 11:47:08Z yegor256@yahoo.com $
 */

#include <stdarg.h>
#include <unistd.h>
#include <iostream>
#include "rqdql.h"
#include "Scanner.h"
#include "Logger.h"

rqdql::LogLevel rqdql::level = L_ERROR;

/**
 * Main method in the product
 */
int main(int argc, char** argv) {
    using namespace std;

    char c;
    while ((c = getopt(argc, argv, "v")) != -1) {
        switch (c) {
            case 'v':
                cout << RQDQL_VERSION << endl;
                return 0;
            case '?':
                cout << 
                "usage: rqdql [-?v]" << endl <<
                "Options:" << endl <<
                "  -?\tShows this help message" << endl <<
                "  -v\tReturns current version of the product" << endl <<
                "Report bugs to <team@rqdql.com>" << endl
                ;
                return 0;
            default:
                cout << "unknown option" << endl;
                return -1;
        }
    }
    
    string text;
    while (!cin.eof()) {
        string s;
        getline(cin, s);
        text = text + s + "\n";
    }
    rqdql::Scanner::getInstance().scan(text);
    proxy::Proxy::getInstance().inject();

    // everything OK?
    if (rqdql::Logger::getInstance().empty()) {
        return 0;
    }
    
    // no, we should display all errors found
    cout << rqdql::Logger::getInstance().getReport() << endl;
    return -1;
}

