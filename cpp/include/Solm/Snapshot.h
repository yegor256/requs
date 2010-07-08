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

#ifndef __INCLUDE_SOLM_SNAPSHOT_H
#define __INCLUDE_SOLM_SNAPSHOT_H

#include <vector>
#include <string>
#include <map>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

namespace solm {

/**
 * Forward declarations
 */
class Predicate;
class Declaration;

/**
 * A snapshot inside a fact
 */
class Snapshot {
public:
    
    /**
     * The fact is positive?
     */
    operator bool() const;

    /**
     * Conver it to a user-friendly string
     */
    virtual operator std::string() const;

    /**
     * Two paths are equal?
     */
    bool operator==(const Fact&) const;

    /**
     * Outgoing context to retrieve
     */
    operator Context() const;

    /**
     * Set outcome to this path
     */
    void set(const Outcome& o) { _outcome = o; }
    bool operator==(const Snapshot&) const;
    const string toString() const;
    Object& create(const string&);
    void assignId(Object&) const;
    void deassignId(Object&) const;
    void assignName(Object&, const string&) const;
    bool hasName(const string&) const;
    const vector<string> getNames() const;
    Object& getByName(const string&); // non-const intentionally
    static Mapping makeMapping(const Predicate*, const Declaration*);
private:
    vector<Object> objects;
    int computeNextId() const;
    void isMine(Object&) const;
};

}

#endif
