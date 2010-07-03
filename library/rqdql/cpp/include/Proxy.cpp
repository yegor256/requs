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
 *
 * This file is included ONLY from Proxy.h
 */

/**
 * Get reference to the list of types
 */
template<> map<string, Type*>& Proxy::getArray<Type>() {
    return types;
}

/**
 * Get reference to the list of use cases
 */
template<> map<string, UseCase*>& Proxy::getArray<UseCase>() {
    return useCases;
}

/**
 * Get reference to the list of types
 */
template<> const map<string, Type*>& Proxy::getConstArray<Type>() const {
    return types;
}

/**
 * Get reference to the list of use cases
 */
template<> const map<string, UseCase*>& Proxy::getConstArray<UseCase>() const {
    return useCases;
}

/**
 * Inject all Types and Use Cases from PROXY into SOLM
 */
void Proxy::inject() {
    using namespace solm;
    
    // first, we inject all TYPES, converting them into definitions
    // of new functions (declaration)
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        // add this declaration to SOLM
        rqdql::get<Solm>().addFormula(
            (new Declaration((*i).first))
            ->arg("x")
            ->setFormula((*i).second->makeFormula("x"))
        );
    }

    // now we inject all use cases
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
    throw rqdql::Exception(rqdql::_t("Element doesn't have a system-wide name, use hasName() first"));
}


