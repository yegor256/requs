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
#include <boost/algorithm/string/join.hpp> // join()
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
#include <boost/algorithm/string/regex.hpp> // replace_regex_copy()
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()
#include "Solm.h"
#include "Logger.h"
using namespace std;

namespace proxy {

class Type;
class Slot;
class Signature;
class Flow;
class Flows;
class UseCase;
class Proxy;

/**
 * One individual TYPE, like ActorUser, UserPhoto, etc.
 */
class Type {
public:
    typedef vector<Slot*> Slots;
    Type() : slots(), predicate(0) { /* that's it */ }
    bool isEmpty() const { return !slots.size() && !predicate; }
    bool hasPredicate() const { return predicate; }
    solm::Sequence* getPredicate() const { return predicate; }
    Slot* getSlot(const string&); // get slot of CREATE it, if absent
    Slots getSlots() const { return slots; }
    Type* addSlot(Slot*);
    Type* addSlot(const string&);
    Type* addPredicate(solm::Formula*);
    const string toString() const;
    const string getName() const; 
    bool hasName() const; 
    solm::Formula* makeFormula(const string&) const;
private:
    Slots slots;
    solm::Sequence* predicate;
};

/**
 * Slot that interconnects one TYPE with another TYPE, 
 * using cardinality and predicates.
 */
class Slot : public Type {
public:
    class Cardinality {
    public:
        Cardinality(const string& s) : mnemo(s) { /* later */ }
        Cardinality(const char* s) : mnemo(s) { /* later */ }
        const string toString() const { return mnemo; }
    private:
        string mnemo;
    };
    Slot(const string&, const Cardinality&, solm::Formula*, Type*);
    Slot(const string&);
    const string& getName() const { return name; }
    bool hasName() const { return true; } 
    Type* getType() const { return type; }
    solm::Formula* getFormula() const { return formula; }
    const Cardinality& getCardinality() const { return cardinality; }
private:
    string name;
    Cardinality cardinality;
    solm::Formula* formula;
    Type* type;
};

class Signature {
public:
    class Explanation {
    public:
        Explanation() : type(0), slot(""), object("") { /* that's it */ }
        Explanation(Type* t) : type(t), slot(""), object("") { /* that's it */ }
        Explanation(const string& s, const string& o) : type(0), slot(s), object(o) { /* that's it */ }
        const string toString() const;
    private:
        Type* type;
        string slot;
        string object;
    };
    typedef map<string, Explanation*> Explanations;
    Signature() : text(""), explanations() { /* that's it */ }
    Signature(const string& t) : text(t), explanations() { /* that's it */ }
    void setText(const string& t) { text = t; }
    string getText() const { return text; }
    Signature* explain(const string&, Explanation*);
    const string toString() const { return text; }
    bool match(const Signature*) const;
    bool isFormula() const;
    solm::Formula* makeFormula() const;
private:
    string text;
    Explanations explanations;
    const string simplify(const string&) const;
    string getPlaceName(size_t) const;
    bool hasPlaces() const;
    bool hasPlace(const string&) const;
    vector<string> getPlaces() const;
};

class Flow {
public:
    Flow(const string& t, Signature* s) : text(t), signature(s) { /* that's it */ }
    Flow(const string& t) : text(t), signature(0) { /* that's it */ }
    Flow() : text(), signature(0) { /* that's it */ }
    Flows* addAlternative(solm::Formula*);
    Flows* findAlternative(char); // find alternative by letter or add it if not found
    const string toString() const;
    solm::Formula* makeFormula() const;
private:
    typedef map<solm::Formula*, Flows*> Alternatives;
    string text;
    Signature* signature;
    Alternatives alternatives;
    solm::Formula* getTarget() const; // get Formula which is called by this signature
};

class Flows {
public:
    Flows();
    Flows* addFlow(int i, Flow* f) { flows[i] = f; return this; }
    Flow* getFlow(int);
    const string toString() const;
    solm::Sequence* makeSequence() const;
    bool hasSequence() const { return !formula && !flows.empty(); }
    void setFlows(Flows* f) { flows = f->flows; }
    map<int, Flow*> getFlows() const { return flows; }
    void setFormula(solm::Formula* f) { formula = f; } // instead of sequence, just one formula
    bool hasFormula() const { return formula; }
    solm::Formula* getFormula() { return formula; }
private:
    map<int, Flow*> flows;
    solm::Formula* formula;
};

class UseCase : public Flows {
public:
    UseCase() : Flows(), signature(0) { /* that's it */ }
    UseCase* setSignature(Signature* s) { signature = s; return this; }
    const string toString() const;
    const string getName() const;
    bool hasName() const; 
    Signature* getSignature() const { return signature; }
private:
    Signature* signature;
};

class Proxy {
public:
    Proxy() : types(), useCases() { clear(); }
    void inject();
    void clear();
    template<typename T> size_t count() const; 
    template<typename T> const vector<string> getNames() const;
    template<typename T> T* get(const string&);
    template<typename T> bool hasName(const T*) const;
    template<typename T> const string findName(const T*) const;
private:
    typedef map<string, Type*> Types;
    typedef map<string, UseCase*> UseCases;
    Types types;
    UseCases useCases;
    template<typename T> map<string, T*>& getArray();
    template<typename T> const map<string, T*>& getConstArray() const;
    template<typename T> void initialize(T* t);
};


#include "Proxy/ProxyImpl.h"
#include "Proxy/Type.h"
#include "Proxy/Flow.h"
#include "Proxy/Slot.h"
#include "Proxy/Flows.h"
#include "Proxy/UseCase.h"
#include "Proxy/Signature.h"

}

#endif
