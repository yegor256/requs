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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_PROXY_FLOWS_H
#define __INCLUDE_SCOPE_PROXY_FLOWS_H

#include <string>
#include <vector>
#include <map>
#include "Solm/Formula.h"

namespace proxy {

/**
 * Collection of flows
 */
class Flows {

public:

    /**
     * Public constructor
     * @see rqdql.y
     */
    Flows();

    /**
     * Add new flow by it's number
     * @see rqdql.y
     */
    void add(int, const Flow&);

    /**
     * Get one flow by its number, if it exists
     */
    Flow& flow(int);

    /**
     * Convert a list of Flows into a formula
     * @see Proxy::inject()
     */
    operator solm::Formula() const;

    /**
     * This collection of flows has VARIADIC formula ready?
     */
    bool hasVariadic() const { return !formula && !flows.empty(); }

    /**
     *
     */
    void operator=(boost::shared_ptr<Flows>& f) { flows = f->flows; }

    /**
     * Get a reference to the collection of flows
     */
    std::map<int, boost::shared_ptr<Flow> >& flows(); { return flows; }

    /**
     * Instead of a sequence there is just a simple formula
     */
    void set(boost::shared_ptr<solm::Formula>&);

    /**
     *
     */
    bool hasFormula() const { return formula; }

    /**
     *
     */
    boost::shared_ptr<solm::Formula>& formula() { return formula; }

    /**
     *
     */
    const std::string toString() const;

private:

    /**
     *
     */
    std::map<int, boost::shared_ptr<Flow> > flows;

    /**
     *
     */
    boost::shared_ptr<solm::Formula> formula;

};

}

#endif
