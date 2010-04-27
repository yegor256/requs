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

#ifndef __INCLUDE_SCOPE_H
#define __INCLUDE_SCOPE_H

#include <vector>
#include "rqdql.h"
#include "Classe.h"
#include "UseCase.h"
#include "Predicate.h"

/**
 * Holder of the entire scope
 */
class rqdql::Scope {
public:
    static Scope& getScope();
    
    /**
     * Add one class
     */
    Scope& operator+=(const rqdql::Classe& c) { classes.push_back(c); return *this; }

    /**
     * Add one use case
     */
    Scope& operator+=(const rqdql::UseCase& uc) { useCases.push_back(uc); return *this; };
    
    /**
     * Add one single predicate, that becomes an invariant on the scope
     */
    Scope& operator+=(const rqdql::Predicate& p) { predicates.push_back(p); return *this; };
    
private:
    std::vector<Classe> classes;
    std::vector<UseCase> useCases;
    std::vector<Predicate> predicates;
};

#endif
