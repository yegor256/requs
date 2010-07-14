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
 * @version $Id: Data.h 2308 2010-07-14 12:25:35Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_RULE_H
#define __INCLUDE_SOLM_RULE_H

#include <string>
#include <vector>
#include "Solm/Object.h"

namespace solm {

/**
 * Prolog-style rule
 */
class Rule {

public:

    /**
     * Public constructor
     */
    Rule(const std::string&);

private:
    
    /**
     * Name of the rule
     */
    std::string _name;
    
    /**
     * Collection of objects
     */
    std::vector<Object> _objects;
    
};

}

#endif
