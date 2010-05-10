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

#ifndef __INCLUDE_SCOPE_SOLM_H
#define __INCLUDE_SCOPE_SOLM_H

#include <vector>
#include <typeinfo>
#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp> // join()
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
using namespace std;

namespace solm {

/* forward declaration, and class hierarchy */
template<typename T> class Parametrized;
class Formula;
    class Constant;
    template<typename T> class Unary;
        class Declaration; // extends Parametrized
        template<typename T> class Quantifier; // extends Parametrized
            class Forall;
            class Exists;
        class Braces;
    template<typename T> class Binary;
        class And;
        class Or;
    class Sequence;
    template<typename T> class Predicate; // extends Parametrized
        class Function;
        template<typename T> class Primitive;
            class In;
            template<typename T> class Informal;
                class Info;
                class Silent;
            template<typename T> class Manipulator;
                class Created;
                class Read;
                class Deleted;
            class Throw;
            class Caught;
        class Math;

class Formula {
public:
    virtual ~Formula() { /* nothing, just to make this class polymorphic */ };
    const vector<Formula*>& getFormulas() const { return subs; }
    virtual const string toString() const { return "???"; }
    Formula* getFormula(size_t i = 0) const;
    void setFormula(Formula* f, size_t i = 0);
    void addFormula(Formula* f) { subs.push_back(f); }
protected:
    vector<Formula*> subs;
};

class Constant : public Formula {
public:
    Constant(bool v = true) : Formula(), value(v) { /* that's it */ }
    virtual const string toString() const { return value ? "true" : "false"; }
private:
    bool value;
};

template <typename T> class Parametrized {
public:
    T* arg(const string& s) { vars.push_back(s); return static_cast<T*>(this); }
protected:
    vector<string> vars;
};

template <typename T> class Unary : public Formula {
public:
    T* setFormula(Formula* f) { Formula::setFormula(f); return static_cast<T*>(this); }
};

template <typename T> class Binary : public Formula {
public:
    T* setLhs(Formula* f) { Formula::setFormula(f); return static_cast<T*>(this); }
    T* setRhs(Formula* f) { Formula::setFormula(f, 1); return static_cast<T*>(this); }
protected:
    const string _toString(const string& op) const {
        if (subs.size() != 2) {
            throw "BINARY shall have exactly two formulas inside";
        }
        return getFormula(0)->toString() + " " + op + " " + getFormula(1)->toString();
    }
};

class Sequence : public Formula {
public:
    typedef enum {OP_TO, OP_AND, OP_OR} Operand;
    Sequence(Operand op = OP_TO) : Formula(), operand(op) { /* that's it */ }
    Sequence* addFormula(Formula* f) { Formula::addFormula(f); return this; }
    virtual const string toString() const;
private:
    Operand operand;
};

template <typename T> class Predicate : public Formula, public Parametrized<T> {
protected:
    const string _toString(const string& t) const {
        return t + "(" + boost::algorithm::join(Parametrized<T>::vars, ", ") + ")";
    }
};

class Declaration : public Unary<Declaration>, public Parametrized<Declaration> {
public:
    Declaration(const string& n) : Unary<Declaration>(), Parametrized<Declaration>(), name(n) { /* that's it */ }
    const string& getName() const { return name; }
    virtual const string toString() const;
private:
    string name;
};

template <typename T> class Quantifier : public Unary<T>, public Parametrized<T> {
public:
    const string _toString(const string& t) const {
        if (Unary<T>::subs.size() != 1) {
            throw "Quantifier shall have exactly one formula inside";
        }
        return t + " " + boost::algorithm::join(Parametrized<T>::vars, ", ") + "(" + Unary<T>::getFormula()->toString() + ")";
    }
};

class Forall : public Quantifier<Forall> {
public:
    virtual const string toString() const { return _toString("\\forall"); }
};

class Exists : public Quantifier<Exists> {
public:
    virtual const string toString() const { return _toString("\\exists"); }
};

class And : public Binary<And> {
public:
    virtual const string toString() const { return Binary<And>::_toString("\\vee"); }
};

class Or : public Binary<Or> {
public:
    virtual const string toString() const { return Binary<Or>::_toString("\\wedge"); }
};

class Function : public Predicate<Function> {
public:
    Function(const string& n) : Predicate<Function>(), name(n) { /* that's it */ }
    virtual const string toString() const { return _toString(name); }
private:
    string name;
};

template <typename T> class Primitive : public Predicate<T> { /* ... */ };

class In : public Primitive<In> {
public:
    virtual const string toString() const {
        if (vars.size() != 2) {
            throw "IN() shall have exactly two arguments";
        }
        return vars.at(0) + " \\in " + vars.at(1);
    }
};
class Caught : public Primitive<Caught> {
public:
    virtual const string toString() const { return _toString("caught"); }
};
class Throw : public Primitive<Throw> {
public:
    virtual const string toString() const { return _toString("throw"); }
};

template <typename T> class Informal : public Primitive<T> { /* tbd */ };

class Info : public Informal<Info> {
public:
    Info(const string& s) : Informal<Info>() {
        arg(s);
    }
    virtual const string toString() const { return _toString("info"); }
};
class Silent : public Informal<Silent> {
public:
    virtual const string toString() const { return _toString("silent"); }
};

template <typename T> class Manipulator : public Primitive<T> {
};

class Created : public Manipulator<Created> {
public:
    virtual const string toString() const { return _toString("created"); }
};
class Read : public Manipulator<Read> {
public:
    virtual const string toString() const { return _toString("read"); }
};
class Deleted : public Manipulator<Deleted> {
public:
    virtual const string toString() const { return _toString("deleted"); }
};

class Math : public Predicate<Math> {
public:
    Math(const string& op) : Predicate<Math>(), operand(op) { /* that's it */ }
    virtual const string toString() const {
        if (vars.size() != 2) {
            throw "Math() shall have exactly two arguments";
        }
        return vars.at(0) + " " + operand + " " + vars.at(1);
    }
private:
    string operand;
};

/**
 * Second-Order Logic Model (SOLM)
 * This is a collection of formulas, and some nice methods
 * to manipulate with the collection.
 */
class Solm : public Sequence {
public:
    static Solm& getInstance();
    /**
     * Remove all formulas from the collection.
     */
    void clear() { subs.clear(); }
    const double getAmbiguity() const;
    template <typename T> const int countTypes() const;
    template <typename T> const vector<T*> findTypes() const;
    const vector<string> getAllFunctions() const;
private:
    Solm() : Sequence() { /* that's it */ }
    const vector<Formula*> _retrieve(vector<Formula*> v) const;
};

#include "Solm/Solm.h"
#include "Solm/Formula.h"
#include "Solm/Declaration.h"
#include "Solm/Sequence.h"

}

#endif