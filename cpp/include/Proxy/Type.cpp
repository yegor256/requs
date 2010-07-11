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
 * This file is included ONLY from Proxy.h
 */

#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Logger.h"
#include "Proxy.h"
#include "Proxy/Type.h"
#include "Proxy/Slot.h"
#include "Solm/Formula.h"

proxy::Type::Type() { 
    /* that's it */ 
}

proxy::Type::operator solm::Declaration() const { 
    return solm::Declaration("TYPE"); 
}

proxy::Type::operator std::string() const {
    return "stub_type";
}

// const std::string proxy::Type::toString() const {
//     if (_slots.empty()) {
//         return "{}";
//     }
//     
//     string s = "{\n";
//     for (Slots::const_iterator i = _slots.begin(); i != _slots.end(); ++i) {
//         if (i != _slots.begin()) {
//             s = s + ";\n";
//         }
//         s = s + "\t" + (*i)->name() + "[" + (*i)->getCardinality().toString() + "]: ";
//         if ((*i)->type()->hasName()) {
//             s = s + (*i)->type()->name();
//         } else {
//             s = s + boost::algorithm::replace_all_copy(
//                 (*i)->type()->toString(), 
//                 "\n", 
//                 "\n\t"
//             );
//         }
//     }
//     return s + "\n}";
// }

// boost::shred_ptr<solm::Formula> proxy::Type::makeFormula(const std::string& x) const {
//     using namespace solm;
//     // This TYPE is empty and it's definitely an error
//     // in text, but we anyway should work with this type. Thus,
//     // we report about a problem here and continue.
//     if (isEmpty() && hasName()) {
//         rqdql::get<rqdql::Logger>().log(
//             this, 
//             (boost::format(rqdql::_t("Entity '%s' is empty, probably its name is misspelled")) % getName()).str()
//         );
//         return new Err(rqdql::_t("'entity is empty"));
//     }
//     
//     // This is a new declaration of a type. Again, if the TYPE doesn't
//     // have a predicated, we don't skip it, but work with it.
//     Sequence* sequence;
//     if (hasPredicate()) {
//         sequence = getPredicate();
//     } else {
//         if (hasName()) {
//             rqdql::get<rqdql::Logger>().log(
//                 this, 
//                 (boost::format(rqdql::_t("Entity '%s' doesn't have any textual explanation")) % getName()).str()
//             );
//         }
//         sequence = new Sequence();
//     }
//     
//     // Here we should add slots to the TYPE
//     int propertyCounter = 1;
//     for (Slots::const_iterator j = slots.begin(); j != slots.end(); ++j) {
//         Slot* slot = *j;
//         string propertyName = (boost::format("P%d") % propertyCounter).str();
//         
//         Sequence* sq = new Sequence(Sequence::OP_AND);
//         if (slot->getType()->hasName()) {
//             sq->addFormula((new Function(slot->getType()->getName()))->arg("p"));
//         } else {
//             sq->addFormula(slot->getType()->makeFormula("p"));
//         }
//         sq->addFormula((new Function("composition"))->arg(x)->arg("p"));
//         sq->addFormula(slot->getFormula());
//         
//         Exists* e = (new Exists())
//             ->arg(propertyName)
//             ->setFormula(
//                 (new And())
//                 ->setLhs(
//                     (new Math("="))
//                     ->arg("|" + propertyName + "|")
//                     ->arg("1")
//                 )
//                 ->setRhs(
//                     (new Forall())
//                     ->arg("p")
//                     ->setFormula(
//                         (new Sequence())
//                         ->addFormula(
//                             (new In())
//                             ->arg("p")
//                             ->arg(propertyName)
//                         )
//                         ->addFormula(sq)
//                     )
//                 )
//             );
//         sequence->addFormula(e);
//         propertyCounter++;
//     }
//     
//     return sequence;
// }
