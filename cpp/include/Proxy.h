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

#include <vector>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

namespace proxy {

/**
 * Forward declarations
 */
class Entity;

/**
 * Proxy between English and OOP
 *
 * The class is used in "brokers" and in Scanner, to convert English constructs
 * to object-oriented entities and then inject them into SOLM.
 */
class Proxy {

public:
    
    /**
     * Public constructor
     */
    Proxy();

    /**
     * Inject PROXY objects into SOLM
     * @see rqdql.cpp
     */
    void inject();

    /**
     * Remove all objects from the PROXY scope, used mostly for 
     * unit testing in order to refresh the structure and start
     * a new test.
     */
    void clear();
    
    /**
     * Get an array of all names in PROXY with certain type
     * <code>
     * vector<string> typeNames = rqdql::get<proxy::Proxy>().names<proxy::Type>();
     * </code>
     */
    template<typename T> const std::vector<std::string> names() const;
    
    /**
     * Get a reference to an entity by name
     */
    boost::shared_ptr<Entity>& entity(const std::string&);
    
    /**
     * Find and return a name of the object, if such a name exists. Otherwise
     * the method will throw an exception.
     */
    const std::string& find(const boost::shared_ptr<Entity>&) const;
    
private:

    /**
     * Named list of entities
     */
    typedef std::map<std::string, boost::shared_ptr<Entity> > Entities;

    /**
     * Name list of entities
     */
    Entities _entities;

};

}

#endif
