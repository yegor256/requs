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
 * Convert snapshot to a user-friendly text
 */
const string Snapshot::toString() const {
    vector<string> lines;
    const string format = "%-10s %-15s %-3s %-6s %-20s";
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
                % (*i).getName()
                % (*i).getType()
                % (*i).getId()
                % (*i).getVal()->toString()
                % boost::algorithm::join(ruleLines, ", ")
            ).str()
        );
    }
    return boost::algorithm::join(lines, "\n");
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


