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

void Proxy::inject() {
    using namespace solm;
    
    // first, we inject all TYPES, converting them into definitions
    // of new functions (declaration)
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        // This TYPE is empty and it's definitely an error
        // in text, but we anyway should work with this type. Thus,
        // we report about a problem here and continue.
        if ((*i).second->isEmpty()) {
            rqdql::Logger::getInstance().log(
                i->second, 
                (boost::format("Entity '%s' is empty") % i->first).str()
            );
        }
        
        // This is a new declaration of a type. Again, if the TYPE doesn't
        // have a predicated, we don't skip it, but work with it.
        Declaration* d = new Declaration((*i).first);
        if ((*i).second->hasPredicate()) {
            d->arg("x");
            d->setFormula((*i).second->getPredicate());
        } else {
            rqdql::Logger::getInstance().log(
                i->second, 
                (boost::format("Entity '%s' doesn't have a predicate") % i->first).str()
            );
            d->setFormula(new Err("'missed predicate"));
        }
        
        // Here we should add slots to the TYPE
        
        
        // add this declaration to SOLM
        Solm::getInstance().addFormula(d);
    }

    // now we inject all use cases
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        Declaration* d = new Declaration((*i).first);
        d->setFormula((*i).second->makeSequence());

        // add this declaration to SOLM
        Solm::getInstance().addFormula(d);
    }
}

void Proxy::clear() {
    types.clear();
    useCases.clear();
    getType("text")->addPredicate((new solm::Function("string"))->arg("x"));
    getType("number")->addPredicate((new solm::Function("integer"))->arg("x"));
    getType("SUD")->addPredicate(new solm::Constant(true));
}

const vector<string> Proxy::getTypeNames() const {
    vector<string> v;
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        v.push_back(i->first);
    }
    return v;
}

Type* Proxy::getType(const string& name) {
    Type* t = types[name];
    if (!t) {
        t = types[name] = new Type();
    }
    return t;
}

UseCase* Proxy::getUseCase(const string& name) {
    UseCase* uc = useCases[name];
    if (!uc) {
        uc = useCases[name] = new UseCase();
    }
    return uc;
}

const string Proxy::findTypeName(const Type* t) const {
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        if (i->second == t) {
            return i->first;
        }
    }
    return "undefined";
}

const string Proxy::findUseCaseName(const UseCase* uc) const {
    for (UseCases::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        if (i->second == uc) {
            return i->first;
        }
    }
    return "undefined";
}