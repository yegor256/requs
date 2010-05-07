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
    const vector<Formula*>& getFormulas() const {
        return subs;
    }
protected:
    void setFormula(Formula* f, size_t i = 0) {
        if (subs.size() < i+1) {
            subs.resize(i+1);
        }
        subs[i] = f;
    }
    void addFormula(Formula* f) {
        subs.push_back(f);
    }
private:
    vector<Formula*> subs;
};

class Constant : public Formula {
public:
    Constant(bool v = true) : Formula() {
        value = v;
    }
private:
    bool value;
};

template <typename T> class Parametrized {
public:
    T* arg(const string& s) {
        vars.push_back(s);
        return static_cast<T*>(this);
    }
private:
    vector<string> vars;
};

template <typename T> class Unary : public Formula {
public:
    T* setFormula(Formula* f) {
        Formula::setFormula(f);
        return static_cast<T*>(this);
    }
};

template <typename T> class Binary : public Formula {
public:
    T* setLhs(Formula* f) {
        Formula::setFormula(f);
        return static_cast<T*>(this);
    }
    T* setRhs(Formula* f) {
        Formula::setFormula(f, 1);
        return static_cast<T*>(this);
    }
};

class Sequence : public Formula {
public:
    typedef enum {OP_AND, OP_OR} Operand;
    Sequence(Operand op = OP_AND) : Formula() {
        operand = op;
    }
    Sequence* addFormula(Formula* f) {
        Formula::addFormula(f);
        return this;
    }
private:
    Operand operand;
};

template <typename T> class Predicate : public Formula, public Parametrized<T> { /* more later */ };

class Declaration : public Unary<Declaration>, public Parametrized<Declaration> {
public:
    Declaration(const string& n) : Unary<Declaration>(), Parametrized<Declaration>(), name(n) { /* that's it */ }
    const string& getName() const { return name; }
private:
    string name;
};

template <typename T> class Quantifier : public Unary<T>, public Parametrized<T> { /* tbd */ };

class Forall : public Quantifier<Forall> { /* tbd */ };

class Exists : public Quantifier<Exists> { /* tbd */ };

class And : public Binary<And> { /* tbd */ };

class Or : public Binary<Or> { /* tbd */ };

class Function : public Predicate<Function> {
public:
    Function(const string& n) : Predicate<Function>(), name(n) { /* that's it */ }
private:
    string name;
};

template <typename T> class Primitive : public Predicate<T> { /* tbd */ };

class In : public Primitive<In> { /* later maybe more details*/ };
class Caught : public Primitive<Caught> { /* later maybe more details*/ };
class Throw : public Primitive<Throw> { /* later maybe more details*/ };

template <typename T> class Informal : public Primitive<T> { /* tbd */ };

class Info : public Informal<Info> {
public:
    Info(const string& s) : Informal<Info>() {
        arg(s);
    }
};
class Silent : public Informal<Silent> { /* later maybe more details*/ };

template <typename T> class Manipulator : public Primitive<T> { /* tbd */ };

class Created : public Manipulator<Created> { /* later maybe more details*/ };
class Read : public Manipulator<Read> { /* later maybe more details*/ };
class Deleted : public Manipulator<Deleted> { /* later maybe more details*/ };

class Math : public Predicate<Math> {
public:
    Math(const string& op) : Predicate<Math>(), operand(op) { /* that's it */ }
private:
    string operand;
};

/**
 * Second-Order Logic Model (SOLM)
 * This is a collection of formulas, and some nice methods
 * to manipulate with the collection.
 */
class Solm {
public:
    /**
     * This is a singleton pattern. In order to get an instance
     * of this class you should call getInstance()
     */
    static Solm& getInstance() {
        static Solm* solm;
        if (!solm) {
            solm = new Solm();
        }
        return *solm;
    }
    /**
     * Add new formula to the collection.
     */
    Solm& add(Formula* f) {
        collection.push_back(f);
        return *this;
    }
    /**
     * Remove all formulas from the collection.
     */
    void clear() {
        collection.clear();
    }
    /**
     * To calculate ambiguity of the SOLM, as a relation between
     * total number of silent elements and data manipulators, which
     * include CREATED(), DELETED() and READ(). This list of manipulators
     * is fixed and won't be changed ever.
     */
    double getAmbiguity() {
        int x = countTypes<Silent>();
        int y = countTypes<Created>() + countTypes<Deleted>() + countTypes<Read>();
        if (!y) {
            return 0;
        }
        return (double)x / y;
    }
    /**
     * To calculate how many formulas of a given type
     * we have in the collection. For example:
     * Solm::getInstance().countTypes<Function>() will return integer
     */
    template <typename T> int countTypes() {
        return findTypes<T>().size();
    }
    /**
     * Find formulas with given type
     */
    template <typename T> vector<T*> findTypes() {
        vector<T*> list;
        vector<Formula*> v = _retrieve(collection);
        for (vector<Formula*>::iterator i = v.begin(); i != v.end(); ++i) {
            if (typeid(**i) == typeid(T)) {
                list.push_back(static_cast<T*>(*i));
            }
        }
        return list;
    }
    /**
     * Get names of all declared functions, which are inside
     * declarations.
     */
    vector<string> getAllFunctions() {
        vector<string> list;
        vector<Declaration*> v = findTypes<Declaration>();
        for (vector<Declaration*>::iterator i = v.begin(); i != v.end(); ++i) {
            list.push_back((*i)->getName());
        }
        return list;
    }
private:
    vector<Formula*> collection;
    /**
     * Recursively collects all formulas in the collection into
     * a flat vector
     */
    vector<Formula*> _retrieve(vector<Formula*> v) const {
        vector<Formula*> result;
        for (vector<Formula*>::iterator i = v.begin(); i != v.end(); ++i) {
            result.push_back(*i);
            vector<Formula*> fs = _retrieve((*i)->getFormulas());
            for (vector<Formula*>::iterator j = fs.begin(); j != fs.end(); ++j) {
                result.push_back(*j);
            }
        }
        return result;
    }
};

}

#endif