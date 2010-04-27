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
 */

#ifndef __INCLUDE_SCOPE_BROKERS_H
#define __INCLUDE_SCOPE_BROKERS_H

#include <vector>
#include <string>
#include "rqdql.h"
#include "Scope.h"
using namespace rqdql;

inline void addClasse(void* c) {
    Scope::getScope() += *static_cast<Classe*>(c);
    delete static_cast<Classe*>(c);
}

void addUseCase(void* uc) {
    Scope::getScope() += *static_cast<UseCase*>(uc);
    delete static_cast<UseCase*>(uc);
}

void addPredicate(void* p) {
    Scope::getScope() += *static_cast<Predicate*>(p);
    delete static_cast<Predicate*>(p);
}

/* make a new class from the name */
Classe* makeClasse(const std::string* s) {
    Classe* c = new Classe(*s);
    delete s;
    return c;
}

/* make new class injecting a list of slots into it */
Classe* makeClasse(const std::string* s, void* sl) {
    Classe* c = makeClasse(s);
    std::vector<Classe>* slots = static_cast<std::vector<Classe>* >(sl);
    for (std::vector<Classe>::iterator i=slots->begin(); i!=slots->end(); i++) {
        *c += *i;
    }
    delete slots;
    return c;
}

/* append object to class */
void appendObject(void* c, const std::string* s) {
    static_cast<Classe*>(c)->setObject(*s);
    delete s;
}

Predicate* makePredicate(std::string* s) {
    Predicate* p = new Predicate(*s);
    delete s;
    return p;
}

#endif