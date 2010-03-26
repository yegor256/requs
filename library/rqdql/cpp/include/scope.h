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
 * @version $Id: bootstrap.php 1190 2010-02-07 07:45:29Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_H
#define __INCLUDE_SCOPE_H

#include <vector>
#include <string>
#include "scope/Statement.h"
#include "scope/Action.h"

using namespace std;

namespace rqdql {
    
    namespace scope {

        class item {
        public:    
            virtual item& operator=(item* i) {
                operator=(*i);
                delete i;
                return *this;
            }
        };

    }
};

#endif
