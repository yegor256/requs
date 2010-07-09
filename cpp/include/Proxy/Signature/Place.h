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
 *
 * This file is included from Signature.h
 */

#ifndef __INCLUDE_SCOPE_PROXY_SIGNATURE_PLACE_H
#define __INCLUDE_SCOPE_PROXY_SIGNATURE_PLACE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Proxy/Type.h"
#include "rqdql/Exception.h"

namespace proxy {
namespace signature {

/**
 * One place inside a signature
 */
class Place {
public:
    
    /**
     * The exception to be thrown
     */
    class exPlaceIsAlreadyExplained : public rqdql::Exception {};
    
    /**
     * This place is already explained
     */
    bool isExplained() const;

    /**
     * Explain it with a link to a TYPE
     */
    void explain(const boost::shared_ptr<Type>& t);
    
    /**
     * Explain it with slot/object pair
     */
    void explain(const std::string& s, const std::string& o);
    
    /**
     * Convert this place to a user-friendly format
     */
    const std::string toString() const;
    
private:

    /**
     * Class signature is a friend to us
     */
    friend class Signature;

    /**
     * Link to a type
     */
    boost::shared_ptr<Type> _type;

    /**
     * Name of a slot
     */
    std::string _slot;

    /**
     * Name of an object
     */
    std::string _object;

    /**
     * Private constructor, visible only to class Signature
     */
    Place();

};

}
}

#endif
