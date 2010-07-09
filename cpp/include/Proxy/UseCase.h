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

#ifndef __INCLUDE_SCOPE_PROXY_USECASE_H
#define __INCLUDE_SCOPE_PROXY_USECASE_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Proxy/Flows.h"

namespace proxy {

/**
 * Forward declarations
 */
class Signature;

/**
 *
 */
class UseCase : public Entity, public Flows {

public:

    /**
     *
     */
    UseCase() : Flows(), _signature() { /* that's it */ }

    /**
     *
     */
    void setSignature(const boost::shared_ptr<Signature>& s) { _signature = s; }

    /**
     *
     */
    const std::string toString() const;

    /**
     *
     */
    std::string& name();

    /**
     *
     */
    bool hasName() const; 

    /**
     *
     */
    boost::shared_ptr<Signature>& signature() { return _signature; }
    
private:

    /**
     *
     */
    boost::shared_ptr<Signature> _signature;

};

}

#endif
