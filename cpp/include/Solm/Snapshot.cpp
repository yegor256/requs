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
 * @version $Id$
 */

#include <string>
#include <vector>
#include <boost/format.hpp>
#include "Solm/Snapshot.h"

solm::Snapshot::Snapshot() : _objects(), _alternatives() {
    /* that's it */
}

bool solm::Snapshot::operator==(const solm::Snapshot& s) const {
    // @todo it's a stub
    return false;
}

solm::Snapshot& solm::Snapshot::operator<<(const solm::Snapshot& s) { 
    _alternatives += s; 
    return *this; 
}

// solm::Snapshot::operator std::string() const {
//     return "snapshot stub";
    // vector<string> lines;
    // const string format = "%-10s %-15s %-3s %-20s %-20s";
    // lines.push_back((boost::format(format) % "Name" % "Type" % "ID" % "Value" % "ACL rules").str());
    // for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
    //     const vector<Object::AclRule>& rules = (*i).getRules();
    //     vector<string> ruleLines;
    //     for (vector<Object::AclRule>::const_iterator r = rules.begin(); r != rules.end(); ++r) {
    //         ruleLines.push_back((*r).toString());
    //     }
    //     lines.push_back(
    //         (
    //             boost::format(format)
    //             % ((*i).hasName() ? (*i).getName() : "")
    //             % ((*i).hasType() ? (*i).getType() : "?")
    //             % ((*i).hasId() ? (boost::format("%d") % (*i).getId()).str() : "-")
    //             % rqdql::cutLongLine(((*i).hasValue() ? (*i).getValue()->toString() : "-"), 20)
    //             % boost::algorithm::join(ruleLines, ", ")
    //         ).str()
    //     );
    // }
    // return boost::algorithm::join(lines, "\n");
// }

// solm::Snapshot::Object& solm::Snapshot::create(const string& t) {
//     objects.push_back(Object(t));
//     return *(objects.end() - 1);
// }
// 
// void solm::Snapshot::assignId(solm::Snapshot::Object& obj) const {
//     isMine(obj); // thows if NOT
//     if (obj.hasId()) {
//         return;
//     }
//     obj.setId(computeNextId());
// }
// 
// void solm::Snapshot::deassignId(solm::Snapshot::Object& obj) const {
//     isMine(obj); // thows if NOT
//     if (!obj.hasId()) {
//         return;
//     }
//     obj.removeId();
// }
// 
// void solm::Snapshot::assignName(solm::Snapshot::Object& obj, const string& n) const {
//     isMine(obj); // thows if NOT
//     if (obj.hasName()) {
//         throw rqdql::Exception(
//             boost::format(rqdql::_t("Object '%s' already has name")) % obj.getName()
//         );
//     }
//     if (hasName(n)) {
//         throw rqdql::Exception(
//             boost::format(rqdql::_t("Object with name '%s' already is in snapshot")) % n
//         );
//     }
//     obj.setName(n);
// }
// 
// solm::Snapshot::Mapping solm::Snapshot::makeMapping(const Function* src, const Declaration* dest) {
//     Mapping mapping;
//     if (src->countVars() != dest->countVars()) {
//         throw rqdql::Exception(
//             boost::format(rqdql::_t("Params mismatch for '%s': %d to %d")) 
//                 % src->getName() 
//                 % src->countVars()
//                 % dest->countVars()
//         );
//     }
//     Function::Vars::const_iterator i = src->getVars().begin();
//     Declaration::Vars::const_iterator j = dest->getVars().begin();
//     while (i != src->getVars().end()) {
//         mapping[*j++] = *i++;
//     }
//     return mapping;
// }
// 
// /**
//  * Validates whether this object is in collection
//  */
// void solm::Snapshot::isMine(solm::Snapshot::Object& obj) const {
//     for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
//         if (&(*i) == &obj) {
//             return;
//         }
//     }
//     throw rqdql::Exception(
//         rqdql::_t("Object is not in snapshot")
//     );
// }
// 
// /**
//  * Finds next available ID
//  */
// int solm::Snapshot::computeNextId() const {
//     int found = 0;
//     for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
//         found = max((*i).computeNextId(), found);
//     }
//     return found;
// }
// 
// /**
//  * Do we have an object with this name?
//  */
// bool solm::Snapshot::hasName(const string& n) const {
//     for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
//         if ((*i).hasName() && ((*i).getName() == n)) {
//             return true;
//         }
//     }
//     return false;
// }
// 
// /**
//  * Get a link to an object with this name. It is not const becase a link to 
//  * the object is returned.
//  */
// solm::Snapshot::Object& solm::Snapshot::getByName(const string& n) {
//     for (vector<Object>::iterator i = objects.begin(); i != objects.end(); ++i) {
//         if ((*i).hasName() && ((*i).getName() == n)) {
//             return *i;
//         }
//     }
//     throw rqdql::Exception(
//         boost::format("Object '%s' is not found in snapshot") % n
//     );
// }
// 
// /**
//  * Get all known names in the snapshot
//  */
// const vector<string> solm::Snapshot::getNames() const {
//     vector<string> v;
//     for (vector<Object>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
//         if ((*i).hasName()) {
//             v.push_back((*i).getName());
//         }
//     }
//     return v;
// }
// 
// /**
//  * Map from one local variable to global
//  * @see Function::getOutcome()
//  */
// const string& solm::Snapshot::Mapping::map(const string& s) const {
//     if (!has(s)) {
//         throw rqdql::Exception(
//             boost::format("Can't find a global equivalent of '%s'") % s
//         );
//     }
//     return this->find(s)->second;
// }
// 
// /**
//  * Global scope has an equivalent to this local var?
//  */
// bool solm::Snapshot::Mapping::has(const string& s) const {
//     return (this->find(s) != this->end());
// }
