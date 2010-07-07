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

#include <vector>
#include <map>
#include <typeinfo>
#include <iostream>
#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp> // join()
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
#include <boost/algorithm/string/regex.hpp> // replace_regex_copy()
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()
#include "Proxy.h"
#include "Proxy/Type.h"
#include "Proxy/UseCase.h"
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Solm.h"
#include "Logger.h"
using namespace std;

/**
 * Get reference to the list of types
 */
template<> std::map<std::string, Type*>& Proxy::getArray<Type>() {
    return types;
}

/**
 * Get reference to the list of use cases
 */
template<> std::map<std::string, UseCase*>& Proxy::getArray<UseCase>() {
    return useCases;
}

/**
 * Get reference to the list of types
 */
template<> const std::map<std::string, Type*>& Proxy::getConstArray<Type>() const {
    return types;
}

/**
 * Get reference to the list of use cases
 */
template<> const std::map<std::string, UseCase*>& Proxy::getConstArray<UseCase>() const {
    return useCases;
}

void Proxy::inject() {
    using namespace solm;
    
    /**
     * First, we inject all TYPES, converting them into definitions
     * of new functions (declaration)
     */
    for (Types::const_iterator i = _types.begin(); i != _types.end(); ++i) {
        // add this declaration to SOLM
        rqdql::get<Solm>().addFormula(
            Declaration((*i).first)
            .arg("x")
            .setFormula((*i).second->makeFormula("x"))
        );
    }

    /**
     * Now we inject all use cases
     */
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        UseCase* uc = (*i).second;
        // add this declaration to SOLM
        rqdql::get<Solm>().addFormula(
            (new Declaration((*i).first))
            ->setFormula(
                uc->hasSequence() ? uc->makeSequence() : uc->getFormula()
            )
            ->arg("x") // temporary solution
        );
    }
}

/**
 * Clear proxy and prepare default types
 */
void Proxy::clear() {
    getArray<Type>().clear();
    getArray<UseCase>().clear();
    
    get<Type>("text")->addPredicate(
        (new solm::Function(solm::Function::F_TEXT))
        ->arg("x")
    );
    get<Type>("number")->addPredicate(
        (new solm::Function(solm::Function::F_NUMBER))
        ->arg("x")
    );
    get<Type>("SUD")->addPredicate(
        new solm::Constant(true)
    );
    get<Type>("somebody")->addPredicate(new solm::Constant(true));
    get<Type>("something")->addPredicate(new solm::Constant(true));
}

/**
 * Get full list of all type names
 */
template<typename T> const vector<string> Proxy::getNames() const {
    const map<string, T*>& list = getConstArray<T>();
    vector<string> v;
    for (typename map<string, T*>::const_iterator i = list.begin(); i != list.end(); ++i) {
        v.push_back(i->first);
    }
    return v;
}

/**
 * Count elements of given type
 */
template<typename T> size_t Proxy::count() const {
    return getConstArray<T>().size();
}

/**
 * Initialize TYPE right after its created
 */
template<> void Proxy::initialize<Type>(Type* t) {
    // automatically add a predicate, that this type inherits from "actor"
    if (boost::regex_match(findName(t), boost::regex("Actor.*"))) {
        t->addPredicate(
            (new solm::Function(solm::Function::F_ACTOR))
            ->arg("x")
        );
    }
}

/**
 * Initialize UseCase right after its created
 */
template<> void Proxy::initialize<UseCase>(UseCase* t) {
    /* nothing special for now */
}

/**
 * Get Type by name OR create it if it's not found
 */
template<typename T> T* Proxy::get(const string& name) {
    map<string, T*>& list = getArray<T>();
    T* t = list[name];
    if (!t) {
        t = list[name] = new T();
        initialize(t);
    }
    return t;
}

/**
 * Validates whether the given type has a static name in 
 * the holder.
 * @see Type::hasName()
 */
template<typename T> bool Proxy::hasName(const T* t) const {
    const map<string, T*>& list = getConstArray<T>();
    for (typename map<string, T*>::const_iterator i = list.begin(); i != list.end(); ++i) {
        if (i->second == t) {
            return true;
        }
    }
    return false;
}

/**
 * Finds name of the type in the static holder. If this
 * type is attached to the holder -- the name will be found. If it
 * is not -- we should raise an exception. You should call
 * hasName() before, to validate whether this type has
 * a name or not.
 * @see Type::getName()
 */
template<typename T> const string Proxy::findName(const T* t) const {
    const map<string, T*>& list = getConstArray<T>();
    for (typename map<string, T*>::const_iterator i = list.begin(); i != list.end(); ++i) {
        if (i->second == t) {
            return i->first;
        }
    }
    throw rqdql::Exception(
        rqdql::_t("Element doesn't have a system-wide name, use hasName() first")
    );
}


