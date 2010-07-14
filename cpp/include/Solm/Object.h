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

#ifndef __INCLUDE_SOLM_OBJECT_H
#define __INCLUDE_SOLM_OBJECT_H

#include <string>

namespace solm {

/**
 * Prolog-style object inside a rule
 */
class Object {

public:

    /**
     * Public constructor
     */
    Object(const std::string&);

private:
    
    /**
     * String presentation of an object, in prolog-style
     */
    std::string _value;
    
};

}

#endif
