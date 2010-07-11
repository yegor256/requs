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

#ifndef __INCLUDE_SCOPE_PROXY_ENTITY_H
#define __INCLUDE_SCOPE_PROXY_ENTITY_H

#include <vector>
#include "Proxy/Slot.h"
#include "Solm/Formula/Declaration.h"

namespace proxy {

/**
 * Forward declarations
 */
// class Slot;

/**
 * One entity in PROXY
 * @see proxy::Type
 * @see proxy::UseCase
 */
class Entity {

public:    
    
    /**
     * Collection of slots
     */
    typedef std::vector<Slot> Slots;
    
    /**
     * Add one slot to this type
     */
    Entity& operator+=(const Slot&);
    
    /**
     * Add a collection of slots to this type
     */
    Entity& operator+=(const Slots&);
    
    /**
     * Get an access to particular slot, by name
     */
    Slot& slot(const std::string&);

    /**
     * Get an access to slots
     */
    Slots& slots() { return _slots; }

    /**
     * Get an access to predicate
     */
    solm::Variadic& invariant() { return _invariant; }

    /**
     * Convert this entity to declaration, but without a name yet
     */
    virtual operator solm::Declaration() const = 0;

private:
    
    /**
     * Collection of slots
     */
    std::vector<Slot> _slots;

    /**
     * Logical formula that is always true for this entity
     */
    solm::Variadic _invariant;
         
};

}

#endif
