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
 * @version $Id: Chain.h 2256 2010-07-08 08:30:01Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_CHAIN_H
#define __INCLUDE_SOLM_CHAIN_H

#include <string>
#include <vector>

namespace solm {

/**
 * Forward declarations
 */
class Snapshot;

/**
 * Tree-like chain of snapshots
 */
class Chain : public std::vector<Snapshot> {

public:

    /**
     * Public constructor
     */
    Chain();

    /**
     * These two chains are equivalent?
     */
    bool operator==(const Chain&) const;

    /**
     * One chain is shorter than the other?
     */
    bool operator<(const Chain&) const;

    /**
     * Append one chain to another, concatenating them vertically
     */
    Chain operator+(const Chain&) const;

    /**
     * Concatenate them vertically
     */
    Chain& operator+=(const Chain&);

    /**
     * Concatenate them horizontally
     */
    Chain& operator<<(const Chain&);

    /**
     * Concatenate them horizontally
     */
    Chain& operator<<(const Snapshot&);

    /**
     * This chain has a positive ending?
     */
    operator bool() const;

    /**
     * Convert this chain to a user-friendly string
     */
    operator std::string() const;

private:

};

}

#endif
