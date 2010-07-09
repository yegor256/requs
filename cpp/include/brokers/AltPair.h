/**
 *

 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

#ifndef __INCLUDE_SCOPE_BROKERS_ALTPAIR_H
#define __INCLUDE_SCOPE_BROKERS_ALTPAIR_H

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

namespace brokers {

class AltPair {
public:
    AltPair(int i, char l) : num(i), letter(l) { /* that's it */ }
    void setNum(int i) { num = i; }
    int getNum() const { return num; }
    void setLetter(char l) { letter = l; }
    char getLetter() { return letter; }
private:
    int num; // -1 means STAR
    char letter;
};

typedef vector<AltPair*> AltPairs;

}

#endif
