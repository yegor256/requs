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
#include "Proxy/Entity.h"
#include "Proxy/Signature.h"
#include "Solm/Term.h"

namespace proxy {

/**
 * Use case entity, collection of flows with a signature
 */
class UseCase : public Entity {

public:

    /**
     * Public constructor
     */
    UseCase(const Signature&);

    /**
     * Get an access to the signature of this use case, the composition
     * relation with the class.
     */
    Signature& signature() { return _signature; }
    
    /**
     * Convert a use case into a declaration, but without a name yet.
     * @see Proxy::inject()
     */
    operator solm::Term() const;

private:

    /**
     * Signature of a use case
     */
    Signature _signature;

};

}

#endif
