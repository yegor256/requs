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
 * \author Yegor Bugayenko <egor@tpc2.com>
 * \date 2009-2010
 * \version $Id: Data.h 2309 2010-07-14 13:13:45Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_ANSWER_H
#define __INCLUDE_SOLM_ANSWER_H

#include <string>
#include <vector>

namespace solm {

/**
 * An answer to the question asked to Data. For example:
 * <pre>
 * X = 123
 * Y = mary
 * Y = "some text"
 * </pre>
 * Pay attention that variables may appear in the answer more than once,
 * every time bearing new value with itself.
 */
class Answer {

public:

    /**
     * Was the question successfully resolved and produced some results?
     */
    operator bool() const { return !_values.empty(); }

    /**
     * The answer has this variable? 
     *
     * If the variable was found in the Data
     * block and this variable has some object that can be attached to it,
     * you will have it here.
     */
    bool has(const std::string&);

    /**
     * Retrieve a full list of instances of the variable
     * \param string The name of the variable
     * \return Full list of instances, as string
     */
    const std::vector<std::string> operator[](const std::string&);

private:

    friend class Data;

    /**
     * List of values found in Data
     */
    typedef std::vector<std::pair<std::string, std::string> > Values;
    
    /**
     * List of values
     */
    Values _values;

    /**
     * Private constructor, so that only Data class can instantiate this
     * class.
     */
    Answer() : _values() { /* that's it */ }

};

}

#endif
