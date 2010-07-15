/**
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
 * @version $Id: Data.h 2309 2010-07-14 13:13:45Z yegor256@yahoo.com $
 */

#include <string>
#include <vector>
#include "Solm/Answer.h"

bool solm::Answer::has(const std::string& v) {
    for (Values::const_iterator i = _values.begin(); i != _values.end(); ++i) {
        if ((*i).first == v) {
            return true;
        }
    }
    return false;
}

const std::vector<std::string> solm::Answer::operator[](const std::string& v) {
    std::vector<std::string> vals;
    for (Values::const_iterator i = _values.begin(); i != _values.end(); ++i) {
        if ((*i).first == v) {
            vals.push_back((*i).second);
        }
    }
    return vals;
}
