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

#ifndef __INCLUDE_SCOPE_PROXY_H
#define __INCLUDE_SCOPE_PROXY_H

#include <vector>
#include <map>
#include <typeinfo>
#include <iostream>
#include <boost/format.hpp>
#include "Solm.h"
using namespace std;

namespace proxy {

class Type;
class Slot;
class Signature;
class Flow;
class Flows;
class UseCase;
class Proxy;

class Type {
public:
    Type() : slots(), predicate(0) { /* that's it */ }
    bool isEmpty() const { return !slots.size() && !predicate; }
    Type* getSlot(const string& s);
    Type* addSlot(Slot* s) { slots.push_back(s); return this; }
    Type* addSlot(const string& s); // see end of this file
    Type* addPredicate(solm::Formula* f);
    const string toString() const;
    const string getName() const; // see end of this file
private:
    vector<Slot*> slots;
    solm::Sequence* predicate;
};

class Slot : public Type {
public:
    class Cardinality {
    public:
        Cardinality(const string& s) : mnemo(s) { /* later */ }
        Cardinality(const char* s) : mnemo(s) { /* later */ }
    private:
        string mnemo;
    };
    Slot(const string& n, const Cardinality& c, solm::Formula* f, Type* t);
    Slot(const string& n); // see end of file
    const string& getName() const { return name; }
    Type* getType() const { return type; }
private:
    string name;
    Cardinality cardinality;
    solm::Formula* formula;
    Type* type;
};

class Signature {
public:
    class Explanation { /* empty */ };
    class ExpType : public Explanation {
    public:
        ExpType(Type* t) : type(t) { /* that's it */ }
    private:
        Type* type;
    };
    class ExpObject : public Explanation {
    public:
        ExpObject(const string& s, const string& o) : slot(s), object(o) { /* that's it */ }
    private:
        string slot;
        string object;
    };
    Signature(const string& t) : text(t) { /* that's it */ }
    Signature* explain(const string& n, Explanation* e) { explanations[n] = e; return this; }
private:
    string text;
    map<string, Explanation*> explanations;
};

class Flow {
public:
    Flow(const string& t, Signature* s) : text(t), signature(s) { /* that's it */ }
    Flow(const string& t) : text(t), signature(0) { /* that's it */ }
    Flows* addAlternative(solm::Formula* f);
private:
    string text;
    Signature* signature;
    map<solm::Formula*, Flows*> alternatives;
};

class Flows {
public:
    Flows();
    Flows* addFlow(int i, Flow* f) { flows[i] = f; return this; }
    Flow* getFlow(int i);
private:
    map<int, Flow*> flows;
};

class UseCase : public Flows {
public:
    UseCase() : Flows(), signature(0) { /* that's it */ }
    UseCase* setSignature(Signature* s) { signature = s; return this; }
private:
    Signature* signature;
};

class Proxy {
public:
    static Proxy& getInstance();
    void clear();
    int countTypes() const { return types.size(); } 
    const vector<string> getTypeNames() const;
    Type* getType(const string& name);
    UseCase* getUseCase(const string& name);
    const vector<string> validate() const;
    const string findTypeName(const Type* t) const;
private:
    typedef map<string, Type*> Types;
    typedef map<string, UseCase*> UseCases;
    Types types;
    UseCases useCases;
    Proxy() : types(), useCases() { clear(); }
};

/**
 *
 * Type
 *
 */

const string Type::getName() const {
    return Proxy::getInstance().findTypeName(this);
}

Type* Type::getSlot(const string& s) {
    for (vector<Slot*>::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if ((*i)->getName() == s) {
            return (*i);
        }
    }
    return addSlot(s);
}

Type* Type::addPredicate(solm::Formula* f) {
    if (!predicate) {
        predicate = new solm::Sequence(solm::Sequence::OP_AND);
    }
    predicate->addFormula(f);
    return this;
}

Type* Type::addSlot(const string& s) {
    return addSlot(new Slot(s));
}

/**
 * To convert type into string detailed presentation
 */
const string Type::toString() const {
    string s = "{";
    for (vector<Slot*>::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if (i != slots.begin()) {
            s += "; ";
        }
        // be aware of possible end-less recursion !!
        s += (*i)->getName() + ": " + (*i)->getType()->getName();
    }
    return s + "}";
}

/**
 *
 * Slot
 *
 */

Slot::Slot(const string& n, const Cardinality& c, solm::Formula* f, Type* t) :
    name(n), cardinality(c), formula(f), type(t) {
    /* nothing for now */
}

Slot::Slot(const string& n) :
    name(n), cardinality("1..n -> 1"), formula(new solm::Constant(true)), type(Proxy::getInstance().getType("text")) {
    /* nothing for now */
}

/**
 *
 * Flows
 *
 */

Flows::Flows() : flows() {
    addFlow(0, new Flow("start"));
}

/**
 * Get a flow by its number, if it exists
 */
Flow* Flows::getFlow(int i) { 
    if (flows.find(i) == flows.end()) {
        throw (boost::format("Flow no.%d not found") % i).str();
    }
    return flows[i]; 
}

/**
 *
 * Proxy
 *
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

const vector<string> Proxy::validate() const {
    vector<string> errors;
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        if (i->second->isEmpty()) {
            errors.push_back((boost::format("Entity '%s' is empty") % i->first).str());
        }
    }
    return errors;
}

const string Proxy::findTypeName(const Type* t) const {
    for (Types::const_iterator i = types.begin(); i != types.end(); ++i) {
        if (i->second == t) {
            return i->first;
        }
    }
    return "undefined";
}

Flows* Flow::addAlternative(solm::Formula* f) { 
    return alternatives[f] = new Flows; 
}

}

#endif