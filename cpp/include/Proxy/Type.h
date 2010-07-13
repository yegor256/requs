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

#ifndef __INCLUDE_SCOPE_PROXY_TYPE_H
#define __INCLUDE_SCOPE_PROXY_TYPE_H

#include <string>
#include <vector>
#include "Proxy/Entity.h"
#include "Solm/Predicate.h"

namespace proxy {

/**
 * Forward declarations
 */
// class Slot;

/**
 * One individual TYPE, like ActorUser, UserPhoto, etc.
 *
 * The Type itself doesn't have a name and all types are stored in a named
 * MAP inside Solm class. Type is a collection of slots and a collection
 * of predicates, that's it.
 */
class Type : public Entity {

public:
    
    /**
     * Public constructor
     */
    Type();
    
    /**
     * Get its name
     */
    operator std::string() const;

    /**
     * Convert this entity to declaration, but without a name yet
     */
    operator solm::Predicate() const;

private:

};

}

#endif
