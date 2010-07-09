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
#include <map>
#include "Solm/Formula.h"
#include "Solm/Formula/Variadic.h"

namespace proxy {
    
/** 
 * Forward declarations
 */
class Flows;
class Signature;

/** 
 * One action-flow in a list of flows
 */
class Flow {
    
public:

    /** 
     * Public constructor
     */
    Flow(const std::string& t, const Signature& s) : _text(t), _signature(s) { /* that's it */ }

    /** 
     * Add new alternative to the flow
     */
    Flows& add(const solm::Formula&);

    /** 
     * Find an alternative by an indexed char, or add it if not found
     */
    Flows& find(char);

private:

    /** 
     * List of alternatives
     */
    typedef std::map<solm::Variadic, Flows> Alternatives;

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
