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

#ifndef __INCLUDE_SCOPE_PROXY_SIGNATURE_H
#define __INCLUDE_SCOPE_PROXY_SIGNATURE_H

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include "Solm/Formula.h"

namespace proxy {

/**
 * Forward declarations
 */
class Type;

/**
 * Signature of a use case, as a mask of an operation to be performed.
 * The signature shall be formatted as "{placeA} works with {placeB}", where
 * all places shall be named and enclosed with curled braces. Later we can
 * access them with explanations.
 */
class Signature {
public:

    /**
     * One place inside a signature
     */
    class Place {
    public:
        class AlreadyExplainedException : public rqdql::Exception {};
        
        /**
         * Public constructor
         */
        Place();
    
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
        boost::shared_ptr<Type> _type;
        std::string _slot;
        std::string _object;
    };

    /**
     * Named list of places inside the signature
     */
    typedef std::map<std::string, Place> Places;

    /**
     * Public constructor, text to be provided immediately
     */
    Signature(const std::string& t);

    /**
     * Find and return a position inside a signature. If the position/place
     * is absent the method will throw an exception.
     *
     * @see brokers::SignatureHolder::setSignature()
     */
    Place& place(const std::string&);

    /**
     * Get size of signature, in places. How many places this signature has
     */
    size_t size() const;

    /**
     * Convert this signature to a user-friendly string
     */
    const std::string toString() const { return _text; }

    /**
     * Compare two signatures and match them. Returns TRUE if
     * two signatures look identical or very similar.
     */
    bool operator==(const Signature&) const;

    /**
     * This signature is already a formula ready-to-go into SOLM?
     * @see Flow::getTarget()
     */
    bool isFormula() const;

    /**
     * Get the formula ready-to-go into SOLM
     */
    boost::shared_ptr<solm::Formula> makeFormula() const;

private:
    
    /**
     * Text of the signature
     */
    std::string _text;
    
    /**
     * Collection of places
     */
    Places _places;

};

}

#endif
