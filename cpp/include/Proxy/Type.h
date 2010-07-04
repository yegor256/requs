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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_PROXY_TYPE_H
#define __INCLUDE_SCOPE_PROXY_TYPE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
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
class Type {
public:
    typedef std::vector< boost::shared_ptr<Slot> > Slots;

    /**
     * Public constructor
     */
    Type() : slots(), predicate() { /* that's it */ }
    
    /**
     * The class is empty and doesn't have any slots and any predicates
     * @see makeFormula()
     */
    bool isEmpty() const { return !slots.size() && !predicate; }

    /**
     * This type has name?
     */
    bool hasName() const; 
    
    /**
     * Get name of this type, if it exists in SOLM. Otherwise will throw
     * an exception (if the type has no name yet). Use hasName() first, to
     * validate the existence of the name.
     */
    const std::string& getName() const; 

    /**
     * The type has some predicate set
     * @see makeFormula()
     */
    bool hasPredicate() const { return (bool)predicate; }

    /**
     * The type has some predicate set
     * @see makeFormula()
     */
    boost::shared_ptr<solm::Variadic> getPredicate() const { return predicate; }

    /**
     * Find and get slot by name, or create it if it's absent
     */
    boost::shared_ptr<Slot> getSlot(const std::string&);
    
    /**
     * Get a list of slots
     */
    const Slots getSlots() const { return slots; }
    
    /**
     * Add new slot to the type
     */
    Type& add(const boost::shared_ptr<Slot>&);
    
    /**
     * Add new slot to the type, with just a name
     */
    Type& add(const std::string&);
    
    /**
     * Add new predicate to the type
     */
    Type& add(const boost::shared_ptr<solm::Formula>&);
    
    /**
     * Convert this type to a user-friendly string
     */
    const std::string toString() const;

    /**
     * Conver this predicate to a new SOLM formula
     */
    boost::shared_ptr<solm::Formula> makeFormula(const std::string&) const;
    
private:
    Slots slots;
    boost::shared_ptr<solm::Variadic> predicate;
};

}

#endif
