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

#ifndef __INCLUDE_SCOPE_PROXY_FLOWS_H
#define __INCLUDE_SCOPE_PROXY_FLOWS_H

#include <string>
#include <vector>
#include <map>
#include "Proxy/Flow.h"

namespace proxy {

/**
 * Collection of flows
 */
class Flows : public std::map<int, Flow> {

public:

    /**
     * Public constructor
     * @see rqdql.y
     */
    Flows();

    /**
     * Get one flow by its number, if it exists. If not exists, it 
     * will be created as an empty flow.
     */
    Flow& flow(int);

private:

};

}

#endif
