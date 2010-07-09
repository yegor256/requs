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
#include <boost/algorithm/string/join.hpp> // join()
#include "Solm/Formula/Predicate.h"

solm::Predicate::operator std::string() const {
    return 
    _name 
    + "(" 
    + boost::algorithm::join(Parametrized<Predicate>::getVars(), ", ") 
    + ")";
}

// Outcome Function::getOutcome(const Fact& f, const Snapshot::Mapping& m = Snapshot::NullMapping) const { 
//     // we are asserting the the arg is NUMBER
//     if (name == F_NUMBER) {
//         return numberOutcome(f, m);
//     }
//     // we are asserting the the arg is TEXT
//     if (name == F_TEXT) {
//         return textOutcome(f, m);
//     }
//     // we are asserting the the arg is ACTOR
//     if (name == F_ACTOR) {
//         return actorOutcome(f, m);
//     }
//     // we are asserting the the arg is SUD
//     if (name == F_SUD) {
//         return sudOutcome(f, m);
//     }
//     
//     if (!rqdql::get<Solm>().hasDeclaration(name)) {
//         rqdql::get<rqdql::Logger>().log(
//             this, 
//             (boost::format(rqdql::_t("Function '%s' is absent, can't calculate its outcome")) % name).str()
//         );
//         return Outcome();
//     }
//     
//     Declaration* d = rqdql::get<Solm>().getDeclaration(name);
//     if (d->countVars() != countVars()) {
//         rqdql::get<rqdql::Logger>().log(
//             this,
//             (boost::format(rqdql::_t("Function '%s' expects %d params, but %d provided")) 
//                 % d->getName()
//                 % d->countVars()
//                 % countVars()
//             ).str()
//         );
//         return Outcome();
//     }
//     
//     return d->getFormula()->getOutcome(
//         f, 
//         Snapshot::makeMapping(
//             this, 
//             rqdql::get<Solm>().getDeclaration(name)
//         )
//     );
// }
