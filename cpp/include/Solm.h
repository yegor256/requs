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
#include <boost/format.hpp> // boost::format()
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join()
#include <boost/algorithm/string/replace.hpp> // boost::algorithm::replace_all_copy()
#include "Logger.h"
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
                class Err;
            template<typename T> class Manipulator;
                class Created;
                class Read;
                class Deleted;
                class Updated;
            class Throw;
            class Caught;
        class Math;

class Formula {
public:
    typedef vector<Formula*> Formulas;
    virtual ~Formula() { /* nothing, just to make this class polymorphic */ };
    virtual const string toString() const;
    void clear() { subs.clear(); } // remove everything from the collection
    Formula* getFormula(size_t) const; // get formula by index
    void setFormula(Formula*, size_t);
    void addFormula(Formula* f) { subs.push_back(f); }
    const Formulas& getFormulas() const { return subs; }
private:
    Formulas subs;
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
    typedef vector<string> Vars;
    T* arg(const string& s) { vars.push_back(s); return static_cast<T*>(this); }
    const Vars& getVars() const { return vars; }
private:
    Vars vars;
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
        if (getFormulas().size() != 2) {
            throw "BINARY shall have exactly two formulas inside";
        }
        return getFormula(0)->toString() + " " + op + " " + getFormula(1)->toString();
    }
};

class Sequence : public Formula {
public:
    typedef enum {OP_TO, OP_AND, OP_OR, OP_SEMICOLON} Operand;
    Sequence(Operand op = OP_TO) : Formula(), operand(op) { /* that's it */ }
    Sequence* addFormula(Formula* f) { Formula::addFormula(f); return this; }
    virtual const string toString() const;
    void append(const Sequence* s);
private:
    Operand operand;
};

template <typename T> class Predicate : public Formula, public Parametrized<T> {
protected:
    const string _toString(const string& t) const {
        return t + "(" + boost::algorithm::join(Parametrized<T>::getVars(), ", ") + ")";
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
    const string _toString(const string& t) const;
};

class Forall : public Quantifier<Forall> {
public:
    virtual const string toString() const { return Quantifier<Forall>::_toString("\\forall"); }
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
    virtual const string toString() const;
};
class Caught : public Primitive<Caught> {
public:
    virtual const string toString() const { return _toString("caught"); }
};
class Throw : public Primitive<Throw> {
public:
    virtual const string toString() const { return _toString("throw"); }
};

template <typename T> class Informal : public Primitive<T> {
};

class Info : public Informal<Info> {
public:
    Info(const string& s) : Informal<Info>() { arg(s); }
    virtual const string toString() const { return _toString("info"); }
};
class Silent : public Informal<Silent> {
public:
    Silent(const string& s) : Informal<Silent>() { arg(s); }
    virtual const string toString() const { return _toString("silent"); }
};
class Err : public Informal<Err> {
public:
    Err(const string& s) : Informal<Err>() { arg(s); }
    virtual const string toString() const { return _toString("err"); }
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
class Updated : public Manipulator<Updated> {
public:
    virtual const string toString() const { return _toString("updated"); }
};

class Math : public Predicate<Math> {
public:
    Math(const string& op) : Predicate<Math>(), operand(op) { /* that's it */ }
    virtual const string toString() const;
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
    static Solm& getInstance(); // singleton pattern
    const double getAmbiguity() const; // calculate scope ambiguity
    template <typename T> const int countTypes() const; // count objects of given type
    template <typename T> const vector<T*> findTypes() const; // find all objects of given type
    const vector<string> getAllFunctions() const; // get list of all declared functions
private:
    Solm() : Sequence(Sequence::OP_SEMICOLON) { /* that's it */ }
    const Formulas _retrieve(Formulas) const; // get all formulas, including sub-formulas
};

#include "Solm/SolmImpl.h"
#include "Solm/Formula.h"
#include "Solm/Declaration.h"
#include "Solm/Sequence.h"
#include "Solm/Math.h"
#include "Solm/Quantifier.h"
#include "Solm/Primitive.h"

}

#endif
