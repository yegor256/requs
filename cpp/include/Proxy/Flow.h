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

#ifndef __INCLUDE_SCOPE_PROXY_FLOW_H
#define __INCLUDE_SCOPE_PROXY_FLOW_H

#include <string>
#include <map>
#include "Proxy/Signature.h"
#include "Solm/Formula.h"
#include "Solm/Formula/True.h"
#include "Solm/Formula/Variadic.h"

namespace proxy {
    
/** 
 * Forward declarations
 */
class Flows;

/** 
 * One action-flow in a list of flows
 */
class Flow {
    
public:

    /** 
     * Public constructor
     */
    Flow(const std::string&, const Signature&);

    /** 
     * Add new formula to the alternative flow by CHAR
     */
    Flows& alt(char c, const solm::Formula& f = solm::True());

private:

    /** 
     * Alternative pair
     */
    typedef std::pair<solm::Variadic, Flows> Alternative;

    /** 
     * List of alternatives
     */
    typedef std::map<char, Alternative> Alternatives;

    /** 
     * Textual image of the flow
     */
    std::string _text;

    /** 
     * Signature of the FLOW
     */
    Signature _signature;

    /** 
     * List of named alternatives
     */
    Alternatives _alternatives;

};

}

#endif
