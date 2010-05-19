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
#include "Front.h"

rqdql::LogLevel rqdql::level = L_ERROR;

/**
 * Main method in the product
 */
int main(int argc, char** argv) {
    using namespace std;

    char c;
    while ((c = getopt(argc, argv, "v?")) != -1) {
        switch (c) {
            case 'v':
                cout << RQDQL_VERSION << endl;
                return 0;
            case '?':
                cout << 
                "usage: rqdql [-?v] [reports...]" << endl <<
                "Options:" << endl <<
                "  -?\tShows this help message" << endl <<
                "  -v\tReturns current version of the product" << endl <<
                "This program built for " << __VERSION__ << endl <<
                "Report bugs to <bugs@rqdql.com>" << endl
                ;
                return 0;
        }
    }
    
    string text;
    while (!cin.eof()) {
        string s;
        getline(cin, s);
        text = text + s + "\n";
    }
    
    try {
        rqdql::Scanner::getInstance().scan(text);
        proxy::Proxy::getInstance().inject();
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] != '-') {
                front::Front::getInstance().require(argv[i]);
            }
        }
        cout << front::Front::getInstance().asXml() << endl;
    } catch (char* e) {
        cerr << "Internal error: \"" << e << "\"" << endl;
        return -1;
    } catch (...) {
        cerr << "Unknown internal error, email us your text to <team@rqdql.com>" << endl;
        return -1;
    }
    return 0;
}

