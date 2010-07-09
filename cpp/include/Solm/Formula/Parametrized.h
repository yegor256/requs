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

#ifndef __INCLUDE_SOLM_FORMULA_PARAMETRIZED_H
#define __INCLUDE_SOLM_FORMULA_PARAMETRIZED_H

#include <vector>
#include <string>

namespace solm {

/**
 * Parametrized formula, that accepts arguments
 */
template <typename T> class Parametrized {

public:

    /**
     * Arguments accepted
     */
    typedef std::vector<std::string> Arguments;

    /**
     * Instruct the class to accept one more argument
     */
    T& arg(const std::string& s) { _arguments.push_back(s); return static_cast<T>(*this); }

    /**
     * Get one argument
     */
    const std::string& arg(size_t) const;

    /**
     * Convert arguments to a string
     */
    operator std::string() const;

private:

    /**
     * List of accepted arguments
     */
    Arguments _arguments;

};

}

#endif
