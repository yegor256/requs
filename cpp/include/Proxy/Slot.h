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

#ifndef __INCLUDE_SCOPE_PROXY_SLOT_H
#define __INCLUDE_SCOPE_PROXY_SLOT_H

#include <string>
#include <boost/shared_ptr.hpp>

namespace proxy {

/**
 * Slot that interconnects one TYPE with another TYPE, 
 * using cardinality and predicates.
 */
class Slot {
    
public:

    /**
     * Supplementary class to represent cardinality between two 
     * entities. This class is to be re-factored later.
     */
    class Cardinality {
    public:
        Cardinality(const std::string& s) : _mnemo(s) { /* later */ }
        Cardinality(const char* s) : _mnemo(s) { /* later */ }
        operator std::string() const { return _mnemo; }
    private:
        std::string _mnemo;
    };

    /**
     * Public constructor
     */
    Slot(const std::string&, const Cardinality& c = "1..n -> 1");

    /**
     * Get a reference to the type
     */
    const boost::shared_ptr<Entity>& entity() const { return _entity; }
    
    /**
     * Change a reference
     */
    void entity(const boost::shared_ptr<Entity>& e) { _entity = e; }
    
    /**
     * Compare this slot with string (NAME) 
     */
    bool operator==(const std::string& n) { return _name == n; }
    
private:
    
    /**
     * Unique name of the slot inside a type
     */
    std::string _name;

    /**
     * Slot cardinality
     */
    Cardinality _cardinality;
    
    /**
     * Entity attached to this slot
     */
    boost::shared_ptr<Entity> _entity;

};

}

#endif
