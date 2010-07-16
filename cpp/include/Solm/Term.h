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
 * @version $Id: Data.h 2308 2010-07-14 12:25:35Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_TERM_H
#define __INCLUDE_SOLM_TERM_H

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
 * Prolog-style term
 */
class Term {

public:

    friend int ::termparse();
    
    typedef std::vector<Term> Terms;
    
    typedef enum {
        T_ATOM,
        T_RULE,
        T_FACT,
        T_NUMBER,
        T_TEXT,
        T_VARIABLE,
        T_OBJECT,
        T_FALSE
    } Kind;

    /**
     * Public constructor
     */
    Term(const std::string&);

    /**
     * This term is of the type?
     */
    bool is(Kind) const;
    
    /**
     * Convert this term to string
     */
    operator std::string() const;
    
    /**
     * Convert this term to boolean. TRUE means that this term contains
     * some valuable information. FALSE means that the term is just FALSE,
     * meaning "no knowledge at all".
     */
    operator bool() const;
    
    /**
     * Get full list of variables
     */
    const Terms variables() const;

    /**
     * Make a prolog-styled question, providing a simple rule
     * and get an answer.
     */
    const Term operator/(const Term&);

private:
    
    /**
     * Value of the term, as a string
     */
    std::string _value;
    
    /**
     * Collection of terms
     */
    std::vector<Term> _terms;
    
    /**
     * Private constructor, that creates an object with the name and terms.
     * @see term.y
     */
    Term(const std::string&, const Terms&);
    
};

}

#endif
