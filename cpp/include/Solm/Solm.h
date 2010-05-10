/**
 *
 * FaZend.com, Fully Automated Zend Framework
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * FaZend.com. located at www.fazend.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

/**
 * This is a singleton pattern. In order to get an instance
 * of this class you should call getInstance()
 */
Solm& Solm::getInstance() {
    static Solm* solm;
    if (!solm) {
        solm = new Solm();
    }
    return *solm;
}

/**
 * To calculate ambiguity of the SOLM, as a relation between
 * total number of silent elements and data manipulators, which
 * include CREATED(), DELETED() and READ(). This list of manipulators
 * is fixed and won't be changed ever.
 */
const double Solm::getAmbiguity() const {
    int x = countTypes<Silent>();
    int y = countTypes<Created>() + countTypes<Deleted>() + countTypes<Read>();
    if (!y) {
        return 0;
    }
    return (double)x / y;
}

/**
 * To calculate how many formulas of a given type
 * we have in the collection. For example:
 * Solm::getInstance().countTypes<Function>() will return integer
 */
template <typename T> const int Solm::countTypes() const {
    return findTypes<T>().size();
}

/**
 * Find formulas with given type
 */
template <typename T> const vector<T*> Solm::findTypes() const {
    vector<T*> list;
    vector<Formula*> v = _retrieve(subs);
    for (vector<Formula*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        if (typeid(**i) == typeid(T)) {
            list.push_back(static_cast<T*>(*i));
        }
    }
    return list;
}

/**
 * Get names of all declared functions, which are inside
 * declarations.
 */
const vector<string> Solm::getAllFunctions() const {
    vector<string> list;
    vector<Declaration*> v = findTypes<Declaration>();
    for (vector<Declaration*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        list.push_back((*i)->getName());
    }
    return list;
}

/**
 * Recursively collects all formulas in the collection into
 * a flat vector
 */
const vector<Formula*> Solm::_retrieve(vector<Formula*> v) const {
    vector<Formula*> result;
    for (vector<Formula*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        result.push_back(*i);
        vector<Formula*> fs = _retrieve((*i)->getFormulas());
        for (vector<Formula*>::const_iterator j = fs.begin(); j != fs.end(); ++j) {
            result.push_back(*j);
        }
    }
    return result;
}
