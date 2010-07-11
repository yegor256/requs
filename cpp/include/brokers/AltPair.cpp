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
 * @version $Id: AltPair.h 2273 2010-07-09 18:29:48Z yegor256@yahoo.com $
 */

#include "brokers/AltPair.h"

brokers::AltPair::AltPair(int i, char l) : _num(i), _letter(l) { 
    /* that's it */ 
}

void brokers::AltPair::setNum(int i) { 
    _num = i; 
}

int brokers::AltPair::getNum() const { 
    return _num; 
}

void brokers::AltPair::setLetter(char l) { 
    _letter = l; 
}

char brokers::AltPair::getLetter() { 
    return _letter; 
}
