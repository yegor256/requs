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
 * @version $Id: Formula.h 2070 2010-05-24 14:19:35Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Solm.h
 */

/**
 * Two snapshots are equal?
 */
bool Snapshot::operator==(const Snapshot& s) const {
    return false;
}

/**
 * Create new object and return a reference to it
 */
Snapshot::Object& Snapshot::create(const string& t, const string& n = "") {
    Object obj(t);
    obj.setName(n);
    objects.push_back(obj);
    return *(objects.end() - 1);
}

/**
 * Convert snapshot to a user-friendly text
 */
const string Snapshot::toString() const {
    vector<string> lines;
    const string format = "%-10s %-15s %-3s %-20s %-20s";
    lines.push_back((boost::format(format) % "Name" % "Type" % "ID" % "Value" % "ACL rules").str());
    for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
        const vector<Object::AclRule>& rules = (*i).getRules();
        vector<string> ruleLines;
        for (vector<Object::AclRule>::const_iterator r = rules.begin(); r != rules.end(); ++r) {
            ruleLines.push_back((*r).toString());
        }
        lines.push_back(
            (
                boost::format(format)
                % ((*i).hasName() ? (*i).getName() : "")
                % ((*i).hasType() ? (*i).getType() : "?")
                % ((*i).hasId() ? (boost::format("%d") % (*i).getId()).str() : "-")
                % ((*i).hasValue() ? (*i).getValue()->toString() : "-")
                % boost::algorithm::join(ruleLines, ", ")
            ).str()
        );
    }
    return boost::algorithm::join(lines, "\n");
}

/**
 * Assign ID to the object
 */
void Snapshot::assignId(Snapshot::Object& obj) const {
    isMine(obj); // thows if NOT
    if (obj.hasId()) {
        throw rqdql::Exception(boost::format(rqdql::_t("ID '%d' already assigned")) % obj.getId());
    }
    obj.setId(computeNextId());
}

/**
 * Assign name to the object
 */
void Snapshot::assignName(Snapshot::Object& obj, const string& n) const {
    isMine(obj); // thows if NOT
    if (obj.hasName()) {
        throw rqdql::Exception(boost::format(rqdql::_t("Object '%s' already has name")) % obj.getName());
    }
    for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
        if ((*i).getName() == n) {
            throw rqdql::Exception(boost::format(rqdql::_t("Object with name '%s' already is in snapshot")) % n);
        }
    }
    obj.setName(n);
}

/**
 * Validates whether this object is in collection
 */
void Snapshot::isMine(Snapshot::Object& obj) const {
    for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
        if (&(*i) == &obj) {
            return;
        }
    }
    throw rqdql::Exception(rqdql::_t("Object is not in snapshot"));
}

/**
 * Finds next available ID
 */
int Snapshot::computeNextId() const {
    int found = 0;
    for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
        if ((*i).getId() > found) {
            found = (*i).getId();
        }
    }
    return found + 1;
}

/**
 * Set value, wrapper
 */
void Snapshot::Object::setValue(const string& s) {
    setValue(boost::shared_ptr<Snapshot::Object::Value>(new Snapshot::Object::ValueString(s)));
}

/**
 * Set value, wrapper
 */
void Snapshot::Object::setValue(const vector<int>& v) {
    setValue(boost::shared_ptr<Snapshot::Object::Value>(new Snapshot::Object::ValueSet(v)));
}

/**
 * Convert ACL rule to a user-friendly text
 */
const string Snapshot::Object::AclRule::toString() const {
    string s;
    switch (operation) {
        case CREATE:
            s = "CREATE";
            break;
        case UPDATE:
            s = "UPDATE";
            break;
        case READ:
            s = "READ";
            break;
        case DELETE:
            s = "DELETE";
            break;
    }
    return (boost::format("%s:%d") % s % id).str();
}


