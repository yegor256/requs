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

#ifndef __INCLUDE_SOLM_PREDICATE_H
#define __INCLUDE_SOLM_PREDICATE_H

#include <string>
#include <vector>

/**
 * This function will build Term objects, and the class is its friend
 *
 * @see Term.cpp
 */
extern int termparse();

namespace solm {

/**
 * Simple term
 */
class Term {

public:

    friend int ::termparse();
    
    typedef std::vector<Term> Terms;
    
    typedef enum {
        T_ATOM,
        T_NUMBER,
        T_TEXT,
        T_VARIABLE,
        T_OBJECT,
        T_FALSE,
        T_TRUE
    } Kind;

    /**
     * Public constructor
     */
    Term(const std::string& = "");

    /**
     * Compare this term with another one.
     */
    bool operator==(const Term&) const;

    /**
     * This term is of the type?
     */
    bool is(Kind) const;
    
    /**
     * Convert this term to string
     */
    operator std::string() const;
    
    /**
     * Resolve this TERM in terms of a new term. This operation
     * is the main action we perform with the TERM. We resove it,
     * in order to predict possible future behavior of logical
     * functions and predicates.
     */
    const Term operator*(const Term&);

private:
    
    /**
     * Value of the term, as a string
     */
    std::string _value;
    
    /**
     * Collection of terms
     */
    Terms _terms;
    
    /**
     * Private constructor, that creates an object with the name and terms.
     * @see term.y
     */
    Term(const std::string&, const Terms&);
    
};

}

#endif
