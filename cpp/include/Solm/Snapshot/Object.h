/**
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id: Snapshot.h 2256 2010-07-08 08:30:01Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_SNAPSHOT_H
#define __INCLUDE_SOLM_SNAPSHOT_H

#include <vector>
#include <string>
#include <map>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace solm {
namespace snapshot {

/**
 * A snapshot inside a fact
 */
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
    bool hasId() const;
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
    void removeId();
    int computeNextId() const;
};

}
}

#endif
