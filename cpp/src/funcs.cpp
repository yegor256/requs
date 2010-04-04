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
 * @version $Id: global.cpp 1491 2010-04-02 16:48:51Z yegor256@yahoo.com $
 */

#include <string>
#include <vector>
#include "funcs.h"
using namespace std;

/**
 * Use it like this:
 *
 * <code>
 * vector<string> exp;
 * explode("/", "files/at/directory", exp); // exp will receive THREE strings
 * </code>
 *
 * @see http://www.infernodevelopment.com/perfect-c-string-explode-split
 */
void explode(const string& separator, const string& str, vector<string>& results) {
    int found;
    string temp = str;
    found = temp.find_first_of(separator);
    while (found != string::npos){
        if (found > 0) {
            results.push_back(str.substr(0, found));
        }
        temp = temp.substr(found + 1);
        found = temp.find_first_of(separator);
    }
    if (temp.length() > 0) {
        results.push_back(temp);
    }
}

/**
 * Remove leading and trailing spaces
 * @see http://codereflect.com/2007/01/31/how-to-trim-leading-or-trailing-spaces-of-string-in-c/
 */
std::string& trim(std::string& str) {
     // Find the first character position after excluding leading blank spaces
    size_t start = str.find_first_not_of(" \t\n\r");
     // Find the first character position from reverse af
    size_t end = str.find_last_not_of(" \t\n\r");
    if ((string::npos == start) || (string::npos == end)) {
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
    return str;
}
