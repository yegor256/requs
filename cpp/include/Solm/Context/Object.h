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
 * @version $Id$
 */

#ifndef __INCLUDE_SOLM_CONTEXT_OBJECT_H
#define __INCLUDE_SOLM_CONTEXT_OBJECT_H

#include <vector>
#include <string>
#include <map>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include "Solm/Context/Value.h"
#include "Solm/Context/Rule.h"

namespace solm {
namespace context {

/**
 * An object inside a snapshot
 */
struct Object {
    int id;
    std::string name;
    std::string type;
    boost::shared_ptr<Value> value;
    std::vector<Rule> rules;
};

}
}

#endif
