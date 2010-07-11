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

#ifndef __INCLUDE_RQDQL_H
#define __INCLUDE_RQDQL_H

// system libraries
#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace rqdql {

/**
 * Get LOCALIZED std::string
 */
extern const std::string _t(const std::string& s);

/**
 * Get a singleton copy of a module/class
 */
template <typename T> T& get() {
     static T* t;
     if (!t) {
         t = new T();
     }
     return *t;
}

/**
 * Cut the line nicely
 */
extern std::string cutLongLine(const std::string&, size_t);

}

#endif
