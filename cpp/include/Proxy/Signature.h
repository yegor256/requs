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
 * Signature of a use case
 */
class Signature {
public:

    /**
     * Explanation of one position inside signature
     */
    class Explanation {
    public:
        Explanation() : _type(), _slot(), _object() { /* that's it */ }
        Explanation(const boost::shared_ptr<Type>& t) : _type(t), _slot(), _object() { /* that's it */ }
        Explanation(const std::string& s, const std::string& o) : _type(), _slot(s), _object(o) { /* that's it */ }
        const std::string toString() const;
    private:
        boost::shared_ptr<Type> _type;
        std::string _slot;
        std::string _object;
    };

    /**
     * Named list of explanations
     */
    typedef std::map<std::string, boost::shared_ptr<Explanation> > Explanations;

    /**
     * Public constructor
     */
    Signature() : _text(), _explanations() { /* that's it */ }

    /**
     * Public constructor
     */
    Signature(const std::string& t) : _text(t), _explanations() { /* that's it */ }

    /**
     * Set text of the signature
     */
    void setText(const std::string& t) { _text = t; }

    /**
     * Get a reference to the text inside signature
     */
    std::string& text() { return _text; }

    /**
     * Explain the position, inside the signature. If the position exists, it
     * will explained, otherwise the method will throw an exception. If this
     * position is already explained, we will have an exception also.
     *
     * @see brokers::SignatureHolder::setSignature()
     */
    void explain(const std::string&, const boost::shared_ptr<Explanation>&);

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
     * Collection of explanations
     */
    Explanations _explanations;

    /**
     * Simplify the signature before matching
     * @see operator==()
     */
    const std::string _simplified() const;

    /**
     * Get name of the element located at i-th position
     */
    std::string _getPlaceName(size_t) const;

    /**
     * This signature has any places at all?
     */
    bool _hasPlaces() const;

    /**
     * The signature has the named place?
     */
    bool _hasPlace(const std::string&) const;

    /**
     * Get full list of places
     */
    std::vector<std::string> _getPlaces() const;
};

}

#endif
