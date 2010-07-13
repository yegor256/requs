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

#ifndef __INCLUDE_SCOPE_PROXY_H
#define __INCLUDE_SCOPE_PROXY_H

#include "Proxy/Entity.h"

namespace proxy {

/**
 * Proxy between English and OOP
 *
 * The class is used in "brokers" and in Scanner, to convert English constructs
 * to object-oriented entities and then inject them into SOLM.
 */
class Proxy : public Entity {

public:
    
    /**
     * Inject PROXY objects into SOLM
     * @see rqdql.cpp
     */
    void inject();
    
    /**
     * Convert the entire holder of entities into one big declaration
     */
    operator solm::Predicate() const;
    
};

}

#endif
