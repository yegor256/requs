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

#ifndef __INCLUDE_SCOPE_PROXY_SLOT_H
#define __INCLUDE_SCOPE_PROXY_SLOT_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Proxy/Type.h"
#include "Solm/Formula.h"

namespace proxy {

/**
 * Slot that interconnects one TYPE with another TYPE, 
 * using cardinality and predicates.
 */
class Slot : public Type {
public:

    /**
     * Supplementary class to represent cardinality between two 
     * entities. This class is to be re-factored later.
     */
    class Cardinality {
    public:
        Cardinality(const std::string& s) : mnemo(s) { /* later */ }
        Cardinality(const char* s) : mnemo(s) { /* later */ }
        const std::string toString() const { return mnemo; }
    private:
        std::string mnemo;
    };

    /**
     * Public constructor
     */
    Slot(
        const std::string&, 
        const Cardinality&, 
        const boost::shared_ptr<solm::Formula>&, 
        const boost::shared_ptr<Type>&
    );

    /**
     * Public constructor
     */
    Slot(const std::string&);

    /**
     * Get name of this SLOT
     */
    const std::string& getName() const { return _name; }
    
    /**
     * The slot has name?
     */
    bool hasName() const { return true; } 
    
    /**
     * The slot has name?
     */
    boost::shared_ptr<Type>& type() { return _type; }
    
    /**
     * Get formula attached
     */
    boost::shared_ptr<solm::Formula>& formula() { return _formula; }
    
    /**
     * Get slot cardinality
     */
    const Cardinality& getCardinality() const { return _cardinality; }
    
private:
    std::string _name;
    Cardinality _cardinality;
    
    boost::shared_ptr<solm::Formula> _formula;
    boost::shared_ptr<Type> _type;
};

}

#endif
