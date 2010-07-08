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
#include "Solm/Chain.h"
#include "Solm/Snapshot/Object.h"

namespace solm {

/**
 * Forward declarations
 */
// class Predicate;
// class Declaration;

/**
 * A snapshot
 */
class Snapshot {
public:
    
    /**
     * Public constructor
     */
    Snapshot();

    /**
     * The snapshot is positive?
     */
    operator bool() const;

    /**
     * Conver it to a user-friendly string
     */
    virtual operator std::string() const;

    /**
     * Two snapshots are equal?
     */
    bool operator==(const Snapshot&) const;

    /**
     * Set chain to this snapshot
     */
    void set(const Chain& c) { _chain = c; }

private:
    
    /**
     * Set chain to this snapshot
     */
    std::vector<snapshot::Object> _objects;
    
    /**
     * Sub-chain
     */
    Chain _chain;
    
};

}

#endif
