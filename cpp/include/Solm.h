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

/**
 * @see solm::Variadic
 */
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
    Solm() : Variadic(Variadic::OP_SEMICOLON) { /* that's it */ }
    const double getAmbiguity() const; // calculate scope ambiguity
    template <typename T> const int count() const; // count objects of given type
    template <typename T> const vector<T*> find() const; // find all objects of given type
    const vector<string> getFunctions() const; // get list of all declared functions
    bool hasDeclaration(const string&) const; // do we have this particular declaration?
    Declaration* getDeclaration(const string&) const; // get this particular declaration
private:
    const Formulas _retrieve(Formulas) const; // get all formulas, including sub-formulas
};

}

#endif
