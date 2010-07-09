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

#ifndef __INCLUDE_SOLM_H
#define __INCLUDE_SOLM_H

#include <vector>
#include <string>
#include "Solm/Formula/Variadic.h"

namespace solm {
    
/**
 * Forward declaration
 */
class Declaration;

/**
 * Second-Order Logic Model (SOLM)
 * This is a collection of formulas, and some nice methods
 * to manipulate with the collection.
 */
class Solm : public Variadic {
    
public:

    /**
     * Public constructor
     */
    Solm() : Variadic(Variadic::OP_SEMICOLON) { /* that's it */ }

    /**
     * To calculate ambiguity of the SOLM, as a relation between
     * total number of silent elements and data manipulators, which
     * include CREATED(), DELETED() and READ(). This list of manipulators
     * is fixed and won't be changed ever.
     */
    const double ambiguity() const;

    /**
     * To calculate how many formulas of a given type
     * we have in the collection. For example:
     * Solm::getInstance().countTypes<Function>() will return integer
     */
    template <typename T> const int count() const;

    /**
     * Return full list of formulas of given type
     */
    template <typename T> const std::vector<boost::shared_ptr<T> > find() const;

    /**
     * Get names of all declared functions, which are inside
     * declarations.
     */
    const std::vector<std::string> getDeclared() const;

    /**
     * Do we have this particular declaration
     */
    bool hasDeclaration(const string&) const;

    /**
     * Get the particular formula (declaration)
     */
    boost::shared_ptr<Declaration>& getDeclaration(const string&) const;

private:

    /**
     * Recursively collects all formulas in the collection into
     * a flat vector
     */
    const Formulas _retrieve(Formulas) const;

};

}

#endif
