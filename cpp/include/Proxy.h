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
class Type;
class UseCase;

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
    Proxy() : types(), useCases() { clear(); }

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
     * How many elements of type T we have in PROXY?
     * <code>
     * int typesTotalCount = rqdql::get<proxy::Proxy>().count<proxy::Type>();
     * </code>
     */
    template<typename T> size_t count() const; 
    
    /**
     * Get an array of all names in PROXY with certain type
     * <code>
     * vector<string> typeNames = rqdql::get<proxy::Proxy>().getNames<proxy::Type>();
     * </code>
     */
    template<typename T> const std::vector<std::string> getNames() const;
    
    /**
     * Get an object by name
     * <code>
     * boost::shared_ptr<proxy::Type> t = rqdql::get<proxy::Proxy>().get<proxy::Type>("ActorUser");
     * </code>
     */
    template<typename T> boost::shared_ptr<T>& get(const std::string&);
    
    /**
     * Given object has a name in PROXY?
     * <code>
     * boost::shared_ptr<proxy::Type> t;
     * bool has = rqdql::get<proxy::Proxy>().hasName(t);
     * </code>
     */
    template<typename T> bool hasName(const boost::shared_ptr<T>&) const;
    
    /**
     * Find and return a name of the object, if such a name exists. Otherwise
     * the method will throw an exception.
     */
    template<typename T> std::string& name(const boost::shared_ptr<T>&);
    
private:

    /**
     * Named list of types
     */
    typedef std::map<std::string, Type> Types;

    /**
     * Named list of use cases
     */
    typedef std::map<std::string, UseCase> UseCases;

    /**
     * 
     */
    Types types;

    /**
     *
     */
    UseCases useCases;
    
    /**
     *
     */
    template<typename T> std::map<std::string, T>& getArray();
    
    /**
     *
     */
    template<typename T> const std::map<std::string, T>& getConstArray() const;
    
    /**
     *
     */
    template<typename T> void initialize(const T&);
};

}

#endif
