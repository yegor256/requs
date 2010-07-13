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
#include <vector>
#include <typeinfo>
#include <boost/format.hpp>
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Solm.h"
#include "Solm/Predicate.h"

solm::Solm::Solm() : solm::Predicate("(and)") { 
    /* that's it */ 
}

const double solm::Solm::ambiguity() const {
    // int x = count<Silent>();
    // int y = count<Created>() + count<Deleted>() + count<Read>();
    // if (x + y == 0) {
    //     return 1;
    // }
    // return (double)x / (x + y);
    return 0.5; // just a stub
}

// template <typename T> const int solm::Solm::count() const {
//     return find<T>().size();
// }
// 
// template <typename T> const std::vector<boost::shared_ptr<T> > solm::Solm::find() const {
//     using namespace std;
//     vector<boost::shared_ptr<T> > list;
//     Formulas v = _retrieve(getFormulas());
//     for (Formulas::const_iterator i = v.begin(); i != v.end(); ++i) {
//         if (typeid(**i) == typeid(T)) {
//             list.push_back(static_cast<const T*>(*i));
//         }
//     }
//     return list;
// }
// 
// const std::vector<std::string> solm::Solm::getDeclared() const {
//     using namespace std;
//     vector<string> list;
//     vector<boost::shared_ptr<Declaration> > v = find<Declaration>();
//     for (vector<boost::shared_ptr<Declaration> >::const_iterator i = v.begin(); i != v.end(); ++i) {
//         list.push_back((*i)->getName());
//     }
//     return list;
// }
// 
// bool solm::Solm::hasDeclaration(const std::string& n) const {
//     using namespace std;
//     vector<boost::shared_ptr<Declaration> > v = find<Declaration>();
//     for (vector<boost::shared_ptr<Declaration> >::const_iterator i = v.begin(); i != v.end(); ++i) {
//         if ((*i)->name() == n) {
//             return true;
//         }
//     }
//     return false;
// }
// 
// boost::shared_ptr<solm::Declaration>& solm::Solm::getDeclaration(const std::string& n) const {
//     using namespace std;
//     vector<boost::shared_ptr<Declaration> > v = find<Declaration>();
//     for (vector<boost::shared_ptr<Declaration> >::const_iterator i = v.begin(); i != v.end(); ++i) {
//         if ((*i)->name() == n) {
//             return *i;
//         }
//     }
//     throw rqdql::Exception(
//         boost::format(rqdql::_t("Declaration '%s' not found in SOLM")) % n
//     );
// }

// const solm::Formula::Formulas solm::Solm::_retrieve(Formulas v) const {
//     Formulas result;
//     for (Formulas::const_iterator i = v.begin(); i != v.end(); ++i) {
//         result.push_back(*i);
//         Formulas fs = _retrieve((*i)->getFormulas());
//         for (Formulas::const_iterator j = fs.begin(); j != fs.end(); ++j) {
//             result.push_back(*j);
//         }
//     }
//     return result;
// }

