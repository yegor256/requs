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

#ifndef __INCLUDE_SCOPE_USECASE_H
#define __INCLUDE_SCOPE_USECASE_H

#include <string>
#include <map>
#include <algorithm>
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"
#include "boost/lambda/casts.hpp"
#include "boost/ref.hpp"
#include "rqdql.h"
#include "Classe.h"
#include "Predicate.h"
using namespace std;
using namespace boost;
using namespace boost::lambda;

/**
 * Signature of a use case or a call to use case
 */
class rqdql::Signature {
public:
    /**
     * Attach an alement to signature
     */
    Signature& operator<<(const string& v) { verbs[getNextPos()] = v; return *this; };
    Signature& operator<<(rqdql::Classe& c) { classes[getNextPos()] = &c; return *this; };
    int pos() const { return getNextPos(); }
    string str() const { return getString(); }
    
private:
    typedef map<const int, string> VerbsType;
    VerbsType verbs;
    typedef map<const int, rqdql::Classe*> ClassesType;
    ClassesType classes;
    
    template <typename T> class Compare {
    public:
        bool operator() (const pair<const int, T>& p1, const pair<const int, T>& p2) const {
            return p1.first < p2.first;
        }
    };
    int getNextPos() const {
        return max(
            max_element(verbs.begin(), verbs.end(), Compare<string>())->first,
            max_element(classes.begin(), classes.end(), Compare<rqdql::Classe*>())->first
        ) + 1;
    }

    string getString() const {
        map<int, string> stack;
        
        for_each(
            verbs.begin(), 
            verbs.end(), 
            (_1 ->* &VerbsType::value_type::first)
        );
        
        string str;
        return str;
    }
};

/**
 * Collection of flows, this is a base class for UseCase
 * @see rqdql::UseCase
 */
class rqdql::Flows {
public:
    /**
     * One individual flow in a collection
     */
    class Flow {
    public:
        Flow() : spelling(""), call() { /* that's it */ };
        Flow(const string& t) : spelling(t), call() { /* that's it */ };
        Flow(const string& t, const rqdql::Signature& s) : spelling(t), call(s) { /* that's it */ };
        
        Flows& operator[](const rqdql::Predicate& p) { return catchers[p]; };
        
    private:
        string spelling;
        rqdql::Signature call;
        map<rqdql::Predicate, Flows> catchers;
    };
    
    /**
     * Simple setting/getting of a new flow to the collection
     */
    Flow& operator[](int i) { return flows[i]; };

private:
    /**
     * Associative array of flows, like "1" => Flow
     * It's important, that we don't save here letter, just numbers
     */
    map<int, Flow> flows;
};

/**
 * One use case
 */
class rqdql::UseCase : public rqdql::Flows {
public:
    UseCase(rqdql::Signature s) : Flows(), signature(s) { /* that's it */ };
    
private:
    UseCase(); /* you can't call it this way */
    rqdql::Signature signature;
};

#endif
