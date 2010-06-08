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
class Fact;
    class FactPath;
    class Outcome;
class Snapshot;
class Formula;
    class Constant;
    template<typename T> class Unary;
        class Declaration; // extends Parametrized
        template<typename T> class Quantifier; // extends Parametrized
            class Forall;
            class Exists;
    class Sequence;
        // template<typename T, Sequence::Operand op> class Binary;
            class And;
            class Or;
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

/**
 * A snapshot inside a fact
 */
class Snapshot {
public:
    class Object {
    public:
        class Value {
        public:
            virtual const string toString() const = 0;
        };
        class ValueString : public Value {
        public:
            ValueString(const string& s) : value(s) { /* that's it */ }
            const string toString() const { return value; }
        private:
            string value;
        };
        class ValueSet : public Value {
        public:
            ValueSet(const vector<int>& v) : ids(v) { /* that's it */ }
            const string toString() const;
        private:
            vector<int> ids;
        };
        class AssocMember {
        public:
            virtual const string toString() const = 0;
        };
        class AssocMemberId : public AssocMember {
        public:
            const string toString() const { return (boost::format("%d") % id).str(); }
        private:
            int id;
        };
        class AssocMemberName : public AssocMember {
        public:
            const string toString() const { return name; }
        private:
            string name;
        };
        class ValueAssoc : public Value, 
            public pair<boost::shared_ptr<AssocMember>, boost::shared_ptr<AssocMember> > {
        public:    
            const string toString() const { first->toString() + ":" + second->toString(); }
        };
        class AclRule {
        public:
            typedef enum {CREATE, READ, UPDATE, DELETE} Operation;
            AclRule(Operation op, int i) : operation(op), id(i) { /* that's it */ }
            const string toString() const;
        private:
            Operation operation;
            int id;
        };
        Object(const string& t) : id(0), name(""), type(t), value(), rules() { /* that's it */ }
        int getId() const;
        bool hasId() const { return id > 0; }
        const string& getName() const;
        bool hasName() const { return !name.empty(); }
        const string& getType() const;
        void setType(const string&);
        bool hasType() const { return !type.empty(); }
        const boost::shared_ptr<const Value>& getValue() const;
        bool hasValue() const { return (bool)value; }
        void setValue(const boost::shared_ptr<const Value>& v) { value = v; }
        void setValue(const string&);
        void setValue(const vector<int>&);
        void addRule(const AclRule& r) { rules.push_back(r); }
        const vector<AclRule>& getRules() const { return rules; }
    private:
        int id;
        string name;
        string type;
        boost::shared_ptr<const Value> value; 
        vector<AclRule> rules;

        friend class Snapshot;
        void setName(const string& n) { name = n; }
        void setId(int i) { id = i; }
        void removeId() { id = -1; }
    };
    class Mapping : public map<string, string> {
    public:
        const string& map(const string& s) const;
        bool has(const string& s) const;
    };
    static const Mapping NullMapping;
    bool operator==(const Snapshot&) const;
    const string toString() const;
    Object& create(const string&);
    void assignId(Object&) const;
    void deassignId(Object&) const;
    void assignName(Object&, const string&) const;
    bool hasName(const string&) const;
    const vector<string> getNames() const;
    Object& getByName(const string&); // non-const intentionally
    static Mapping makeMapping(const Function*, const Declaration*);
private:
    vector<Object> objects;
    int computeNextId() const;
    void isMine(Object&) const;
};
const Snapshot::Mapping Snapshot::NullMapping = Snapshot::Mapping();

class Formula {
public:
    typedef vector<Formula*> Formulas;
    virtual ~Formula() { /* nothing, just to make this class polymorphic */ };
    virtual const string toString() const = 0;
    void clear() { subs.clear(); } // remove everything from the collection
    Formula* getFormula(size_t) const; // get formula by index
    void setFormula(Formula*, size_t);
    void addFormula(Formula* f) { subs.push_back(f); }
    const Formulas& getFormulas() const { return subs; }
    Outcome getOutcome() const;
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
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
    const string& getVar(size_t i = 0) const;
    size_t countVars() const { return vars.size(); }
private:
    Vars vars;
};

template <typename T> class Unary : public Formula {
public:
    T* setFormula(Formula* f) { Formula::setFormula(f); return static_cast<T*>(this); }
};

class Sequence : public Formula {
public:
    typedef enum {OP_TO, OP_AND, OP_OR, OP_SEMICOLON} Operand;
    Sequence(Operand op = OP_TO) : Formula(), operand(op) { /* that's it */ }
    Sequence* addFormula(Formula* f) { Formula::addFormula(f); return this; }
    virtual const string toString() const;
    void append(const Sequence* s);
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
private:
    Operand operand;
};

template <typename T, Sequence::Operand op> class Binary : public Sequence {
public:
    Binary() : Sequence(op) { /* that's it */ }
    T* setLhs(Formula* f) { Formula::setFormula(f); return static_cast<T*>(this); }
    T* setRhs(Formula* f) { Formula::setFormula(f, 1); return static_cast<T*>(this); }
protected:
    const string _toString(const string& o) const {
        if (getFormulas().size() != 2) {
            throw "BINARY shall have exactly two formulas inside";
        }
        return getFormula(0)->toString() + " " + o + " " + getFormula(1)->toString();
    }
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
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
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
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};

class And : public Binary<And, Sequence::OP_AND> {
public:
    virtual const string toString() const { return Binary<And, Sequence::OP_AND>::_toString("\\vee"); }
};

class Or : public Binary<Or, Sequence::OP_OR> {
public:
    virtual const string toString() const { return Binary<Or, Sequence::OP_OR>::_toString("\\wedge"); }
};

class Function : public Predicate<Function> {
public:
    static const string F_NUMBER;
    static const string F_TEXT;
    static const string F_SUD;
    
    Function(const string& n) : Predicate<Function>(), name(n) { /* that's it */ }
    virtual const string toString() const { return _toString(name); }
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
    const string& getName() const { return name; }
private:
    string name;
};
const string Function::F_NUMBER = "number";
const string Function::F_TEXT = "text";
const string Function::F_SUD = "SUD";

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
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};
class Silent : public Informal<Silent> {
public:
    Silent(const string&);
    virtual const string toString() const { return _toString("silent"); }
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};
class Err : public Informal<Err> {
public:
    Err(const string& s) : Informal<Err>() { arg(s); }
    virtual const string toString() const { return _toString("err"); }
};

template <typename T> class Manipulator : public Primitive<T> {
protected:
    int findActor(Snapshot&) const;
};

class Created : public Manipulator<Created> {
public:
    virtual const string toString() const { return _toString("created"); }
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};
class Read : public Manipulator<Read> {
public:
    virtual const string toString() const { return _toString("read"); }
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};
class Deleted : public Manipulator<Deleted> {
public:
    virtual const string toString() const { return _toString("deleted"); }
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};
class Updated : public Manipulator<Updated> {
public:
    virtual const string toString() const { return _toString("updated"); }
    virtual Outcome getOutcome(const Fact&, const Snapshot::Mapping&) const;
};

class Math : public Predicate<Math> {
public:
    Math(const string& op) : Predicate<Math>(), operand(op) { /* that's it */ }
    virtual const string toString() const;
private:
    string operand;
};

/**
 * Result of any formula from SOLM. Outcome is a collection of
 * facts (where only one is positive).
 */
class Outcome : public vector<Fact> {
public:
    Outcome() : vector<Fact>() { /* that's it */ }
    Outcome operator+(const Outcome&) const;
    Outcome& operator+=(const Outcome&);
    Outcome& operator<<(const Outcome&);
    Outcome& operator<<(const Fact&);
    operator bool() const;
    vector<FactPath> getPaths() const;
    Fact& getPositiveEnd();
private:
    class AbsentPositiveEndException : public rqdql::Exception {};
};

/**
 * One fact, positive or negative, with a text explanation.
 */
class Fact {
public:
    operator bool() const;
    virtual const string toString() const { return snapshot.toString(); }
    bool operator==(const Fact&) const;
    void setFormula(const Formula* f) { formula = f; }
    void setException(const string& e) { exception = e; }
    void setOutcome(const Outcome& o) { outcome = o; }
    bool hasOutcome() const { return outcome.size(); }
    Outcome& getOutcome() { return outcome; }
    const Outcome& getOutcome() const { return outcome; }
    const Formula* getFormula() const { return formula; }
    Snapshot getSnapshot() const { return snapshot; }
    void setSnapshot(const Snapshot& s) { snapshot = s; }
private:
    string exception;
    Outcome outcome;
    const Formula* formula;
    Snapshot snapshot;
};

/**
 * Serie of facts, ordered
 */
class FactPath : public Fact, public vector<Fact> {
public:
    FactPath operator+(const FactPath&) const;
    bool operator==(const FactPath&) const;
    bool operator<(const FactPath&) const;
    const string toString() const;
private:
};

/**
 * Second-Order Logic Model (SOLM)
 * This is a collection of formulas, and some nice methods
 * to manipulate with the collection.
 */
class Solm : public Sequence {
public:
    Solm() : Sequence(Sequence::OP_SEMICOLON) { /* that's it */ }
    const double getAmbiguity() const; // calculate scope ambiguity
    template <typename T> const int countTypes() const; // count objects of given type
    template <typename T> const vector<T*> findTypes() const; // find all objects of given type
    const vector<string> getAllFunctions() const; // get list of all declared functions
    bool hasDeclaration(const string&) const; // do we have this particular declaration?
    Declaration* getDeclaration(const string&) const; // get this particular declaration
private:
    const Formulas _retrieve(Formulas) const; // get all formulas, including sub-formulas
};

#include "Solm/SolmImpl.h"
#include "Solm/Formula.h"
#include "Solm/Snapshot.h"
#include "Solm/Fact.h"
#include "Solm/FactPath.h"
#include "Solm/Outcome.h"

}

#endif
