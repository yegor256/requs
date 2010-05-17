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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Proxy.h
 */

/**
 * This is a singleton pattern. In order to get an instance
 * of this class you should call getInstance()
 */
Proxy& Proxy::getInstance() {
    static Proxy* proxy;
    if (!proxy) {
        proxy = new Proxy();
    }
    return *proxy;
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
        Solm::getInstance().addFormula(
            (new Declaration((*i).first))
            ->arg("x")
            ->setFormula((*i).second->makeFormula("x"))
        );
    }

    // now we inject all use cases
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        UseCase* uc = (*i).second;
        // add this declaration to SOLM
        Solm::getInstance().addFormula(
            (new Declaration((*i).first))
            ->setFormula(
                uc->hasSequence() ? uc->makeSequence() : uc->getFormula()
            )
        );
    }
}

/**
 * Clear proxy and prepare default types
 */
void Proxy::clear() {
    types.clear();
    useCases.clear();
    
    getType("text")->addPredicate((new solm::Function("string"))->arg("x"));
    getType("number")->addPredicate((new solm::Function("integer"))->arg("x"));
    getType("SUD")->addPredicate(new solm::Constant(true));
    getType("somebody")->addPredicate(new solm::Constant(true));
    getType("something")->addPredicate(new solm::Constant(true));
}

/**
 * Get full list of all type names
 */
const vector<string> Proxy::getTypeNames() const {
    vector<string> v;
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        v.push_back(i->first);
    }
    return v;
}

/**
 * Get full list of use case names (strings)
 */
const vector<string> Proxy::getAllUseCaseNames() const {
    vector<string> v;
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        v.push_back(i->first);
    }
    return v;
}
/**
 * Get Type by name OR create it if it's not found
 */
Type* Proxy::getType(const string& name) {
    Type* t = types[name];
    if (!t) {
        t = types[name] = new Type();
    }
    return t;
}

/**
 * Get Use Case by name OR create it if it's not found
 */
UseCase* Proxy::getUseCase(const string& name) {
    UseCase* uc = useCases[name];
    if (!uc) {
        uc = useCases[name] = new UseCase();
    }
    return uc;
}

/**
 * Validates whether the given type has a static name in 
 * the holder.
 * @see Type::hasName()
 */
bool Proxy::hasName(const Type* t) const {
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        if (i->second == t) {
            return true;
        }
    }
    return false;
}

/**
 * Validates whether the given use case has a static name in 
 * the holder.
 */
bool Proxy::hasName(const UseCase* uc) const {
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        if (i->second == uc) {
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
const string Proxy::findName(const Type* t) const {
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        if (i->second == t) {
            return i->first;
        }
    }
    throw "this type doesn't have a name";
}

/**
 * Finds name of the use case in the static holder. If this
 * use case is attached to the holder -- the name will be found. If it
 * is not -- we should raise an exception. You should call
 * hasName() before, to validate whether this type has
 * a name or not.
 */
const string Proxy::findName(const UseCase* uc) const {
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        if (i->second == uc) {
            return i->first;
        }
    }
    throw "this UseCase doesn't have a name";
}

