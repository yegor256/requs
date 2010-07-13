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

#ifndef __INCLUDE_SOLM_CONTEXT_OBJECT_RULE_H
#define __INCLUDE_SOLM_CONTEXT_OBJECT_RULE_H

#include <vector>
#include <string>
#include <map>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace solm {
namespace context {

/**
 * Access control rule for an object
 */
class Rule {

public:
    
    /**
     * Possible ACL operations
     */
    typedef enum {
        CREATE, 
        READ, 
        UPDATE, 
        DELETE
    } Operation;
    
    /**
     * Public constructor
     */
    Rule(Operation op, int i) : _operation(op), _id(i) { /* that's it */ }

    /**
     * Convert it to a user-friendly string
     */
    operator std::string() const;

private:

    /**
     * Operation
     */
    Operation _operation;

    /**
     * Author of the operation (object ID)
     */
    int _id;

};

}
}

#endif
