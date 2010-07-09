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
#include "Solm/Formula.h"
#include "Solm/Formula/Variadic.h"

namespace proxy {

/**
 * Forward declarations
 */
class Slot;

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
     * Collection of slots inside this type, it's a strong composition. Slots
     * can't exist without type and they don't have global names (or something
     * similar).
     */
    typedef std::vector<Slot> Slots;

    /**
     * Public constructor
     */
    Type();
    
    /**
     * Find and get slot by name, or create it if it's absent. You can
     * do whatever you can with this SLOT, since it's part of the TYPE
     * (it's a strong composition design).
     */
    Slot& slot(const std::string&);

    /**
     * Get a link to the predicate, which is part of this TYPE. It's
     * a strong composition design approach.
     */
    solm::Variadic& predicate();
    
    /**
     * Add new predicate to the type
     */
    Type& operator+=(const solm::Formula&);
    
    /**
     * Convert this type to a user-friendly string
     */
    operator std::string() const;

    /**
     * Create a formula out of this type
     */
    operator solm::Formula() const;
    
private:

    /**
     * Collection of slots
     */
    Slots _slots;

    /**
     * Predicate related to this type
     */
    solm::Variadic _predicate;

};

}

#endif
