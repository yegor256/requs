/**
 *

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
 * @version $Id: SignatureHolder.h 2273 2010-07-09 18:29:48Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_BROKERS_EXPLANATION_H
#define __INCLUDE_SCOPE_BROKERS_EXPLANATION_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Proxy/Type.h"

namespace brokers {

/**
 * Forward declarations
 */
// class ;

/**
 * Explanation of a place in signature
 * @see rqdql.y
 */
class Explanation {
public:
    void setType(const proxy::Type&);
    void setNames(const std::string&, const std::string&);
private:
    boost::shared_ptr<proxy::Type> _type;
    std::string _slotName;
    std::string _objectName;
};

}

#endif
