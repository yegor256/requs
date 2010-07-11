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

#ifndef __INCLUDE_SCOPE_BROKERS_DE_H
#define __INCLUDE_SCOPE_BROKERS_DE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "brokers/Explanation.h"

namespace brokers {

/**
 * Data Element (DE)
 * @see rqdql.y
 */
class De {
public:
    De();
    void setName(const std::string& n);
    const std::string& getName() const;
    bool hasName() const;
    void setExplanation(const Explanation& e);
    const Explanation& getExplanation() const;
    bool hasExplanation() const;
private:
    std::string _name;
    boost::shared_ptr<Explanation> _explanation;
};

}

#endif
