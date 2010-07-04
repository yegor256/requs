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

#include <boost/format.hpp>
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Solm.h"
#include "Solm/Formula/Declaration.h"

using namespace std;

/**
 * To calculate ambiguity of the SOLM, as a relation between
 * total number of silent elements and data manipulators, which
 * include CREATED(), DELETED() and READ(). This list of manipulators
 * is fixed and won't be changed ever.
 */
const double solm::Solm::getAmbiguity() const {
    // int x = count<Silent>();
    // int y = count<Created>() + count<Deleted>() + count<Read>();
    // if (x + y == 0) {
    //     return 1;
    // }
    // return (double)x / (x + y);
    return 0.5; // just a stub
}

/**
 * To calculate how many formulas of a given type
 * we have in the collection. For example:
 * Solm::getInstance().countTypes<Function>() will return integer
 */
template <typename T> const int solm::Solm::count() const {
    return find<T>().size();
}

/**
 * Find formulas with given type
 */
template <typename T> const vector<T*> solm::Solm::find() const {
    vector<T*> list;
    Formulas v = _retrieve(getFormulas());
    for (Formulas::const_iterator i = v.begin(); i != v.end(); ++i) {
        if (typeid(**i) == typeid(T)) {
            list.push_back(static_cast<const T*>(*i));
        }
    }
    return list;
}

/**
 * Get names of all declared functions, which are inside
 * declarations.
 */
const vector<string> solm::Solm::getFunctions() const {
    vector<string> list;
    vector<Declaration*> v = find<Declaration>();
    for (vector<Declaration*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        list.push_back((*i)->getName());
    }
    return list;
}

/**
 * Recursively collects all formulas in the collection into
 * a flat vector
 */
const solm::Formula::Formulas solm::Solm::_retrieve(Formulas v) const {
    Formulas result;
    for (Formulas::const_iterator i = v.begin(); i != v.end(); ++i) {
        result.push_back(*i);
        Formulas fs = _retrieve((*i)->getFormulas());
        for (Formulas::const_iterator j = fs.begin(); j != fs.end(); ++j) {
            result.push_back(*j);
        }
    }
    return result;
}

/**
 * Do we have this particular declaration?
 */
bool solm::Solm::hasDeclaration(const string& n) const {
    vector<Declaration*> v = find<Declaration>();
    for (vector<Declaration*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        if ((*i)->getName() == n) {
            return true;
        }
    }
    return false;
}

/**
 * Find and return this particular declaration, if it exists
 */
solm::Declaration* solm::Solm::getDeclaration(const string& n) const {
    vector<Declaration*> v = find<Declaration>();
    for (vector<Declaration*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        if ((*i)->getName() == n) {
            return *i;
        }
    }
    throw rqdql::Exception(
        boost::format(rqdql::_t("Declaration '%s' not found in SOLM")) % n
    );
}

