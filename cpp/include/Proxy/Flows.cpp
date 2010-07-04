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
 *
 */

#include "Proxy/Flow.h"
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Logger.h"

#include <vector>
#include <string>
#include <map>
#include <boost/format.hpp>

proxy::Flows::Flows() : flows(), formula(0) {
    addFlow(0, new Flow());
}

/**
 * Get a flow by its number, if it exists
 */
proxy::Flow* proxy::Flows::getFlow(int i) { 
    if (flows.find(i) == flows.end()) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Flow no.%d not found")) % i).str()
        );
        addFlow(i, new Flow(rqdql::_t("some action...")));
    }
    return flows[i]; 
}

const string proxy::Flows::toString() const {
    using namespace std;
    vector<string> lines;
    for (map<int, Flow*>::const_iterator i = flows.begin(); i != flows.end(); ++i) {
        lines.push_back((boost::format("%d. %s") % (*i).first % (*i).second->toString()).str());
    }
    return boost::algorithm::join(lines, "\n");
}

/**
 * Instead of a sequence there is just a simple formula
 */
void proxy::Flows::setFormula(solm::Formula* f) { 
    formula = f; 

    // Now we should link this NEW formula with the FLOWS
    rqdql::get<rqdql::Logger>().addClone(this, f);
}

/**
 * Convert a list of Flows into a sequence of Formulas
 * @see Proxy::inject()
 */
solm::Variadic* proxy::Flows::makeSequence() const {
    using namespace solm;
    using namespace std;
    if (!hasSequence()) {
        throw rqdql::Exception(rqdql::_t("There is no sequence here!"));
    }
    Sequence* s = new Sequence();
    for (map<int, Flow*>::const_iterator i = flows.begin(); i != flows.end(); ++i) {
        Formula* f = (*i).second->makeFormula();
        if (f) {
            s->addFormula(f);
        }
    }
    return s;
}

