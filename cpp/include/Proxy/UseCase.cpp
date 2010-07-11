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

#include <string>
#include "Proxy/UseCase.h"
#include "Solm/Formula/Declaration.h"

proxy::UseCase::UseCase(const Signature& s) : proxy::Flows(), _signature(s) { 
    /* that's it */ 
}

proxy::UseCase::operator solm::Declaration() const {
    return solm::Declaration("UC1");
}
