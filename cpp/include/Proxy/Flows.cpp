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

#include <vector>
#include <string>
#include <map>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include "Proxy/Flow.h"
#include "Proxy/Flows.h"
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Logger.h"

proxy::Flows::Flows() : std::map<int, proxy::Flow>() {
    flow(0);
}

// void proxy::Flows::setFormula(solm::Formula* f) { 
//     formula = f; 
// 
//     // Now we should link this NEW formula with the FLOWS
//     rqdql::get<rqdql::Logger>().addClone(this, f);
// }
// 
// solm::Variadic* proxy::Flows::makeSequence() const {
//     using namespace solm;
//     using namespace std;
//     if (!hasSequence()) {
//         throw rqdql::Exception(rqdql::_t("There is no sequence here!"));
//     }
//     Sequence* s = new Sequence();
//     for (map<int, Flow*>::const_iterator i = flows.begin(); i != flows.end(); ++i) {
//         Formula* f = (*i).second->makeFormula();
//         if (f) {
//             s->addFormula(f);
//         }
//     }
//     return s;
// }
// 
// const string proxy::Flows::toString() const {
//     using namespace std;
//     vector<string> lines;
//     for (map<int, Flow*>::const_iterator i = flows.begin(); i != flows.end(); ++i) {
//         lines.push_back((boost::format("%d. %s") % (*i).first % (*i).second->toString()).str());
//     }
//     return boost::algorithm::join(lines, "\n");
// }

