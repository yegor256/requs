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

#ifndef __INCLUDE_SOLM_SENTENCE_H
#define __INCLUDE_SOLM_SENTENCE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Solm/Formula.h"
#include "Solm/Formula/Variadic.h"

namespace solm {

/**
 * Forward declarations
 */
class Formula;

/**
 * Second order logic sentence, that contains formulas inside formulas
 * and so on.
 */
class Sentence : public Variadic {

public:

    /**
     * Public constructor, from a LISP-style sentence, for example you can
     * use it like this:
     * Sentence s("(and (eq x '14) (kind x 'ActorUser))");
     *
     * Full reference of syntax used:
     *   (true)
     *   (declare p (...)) : Declararion of predicate
     *   (and (eq x 5) (kind x "Actor"))
     *   (or (.) ...)
     *   (to (.) ...)
     *   (not (.))
     *   (forall x (.))
     *   (exists x (.))
     *   (p name x ...)
     *   (eq x 123)
     *   (in x Y)
     *   (kind x "ActorUser")
     *
     * You can find more examples in a SentenceTest.cpp.
     */
    Sentence(const string&);

private:
    
    /**
     * Pointer to a formula which is the parent one in the sentence
     */
    boost::shared_ptr<Formula> _formula;

};

}

#endif
