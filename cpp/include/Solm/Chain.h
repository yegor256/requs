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
 * Ordered list of snapshots, which will happen on scope one after
 * another. Every snapshot will have a number of alternatives. Together
 * they constitute a tree-like structure.
 */
class Chain : public std::vector<Snapshot> {

public:

    /**
     * Public constructor
     */
    Chain();

    /**
     * These two chains are equivalent? We will compare them snapshot
     * by snapshot, and will use operator==() from snapshots.
     */
    bool operator==(const Chain&) const;

    /**
     * One chain is shorter than the other? We just compare their length
     * as vectors and return the result, depending on who is the longest
     */
    bool operator<(const Chain&) const;

    /**
     * Append one chain to another, concatenating them vertically. We assume
     * here that the chain is positive and can accept more snapshots. Every
     * snapshot is either positive or negative, the same for a chain. If this
     * chain is negative, it's not extendable any longer.
     */
    Chain operator+(const Chain&) const;

    /**
     * Concatenate them vertically, this is just a wrapper around operator+()
     */
    Chain& operator+=(const Chain& c) { return *this = *this + c; }

    /**
     * Concatenate them vertically. This method simply add new snapshot
     * to the end of the chain, but validates beforehand that this chain
     * is positive.
     */
    Chain operator+(const Snapshot&) const;

    /**
     * Concatenate them vertically, this is just a wrapper around operator+()
     */
    Chain& operator+=(const Snapshot& s) { return *this = *this + s; }

    /**
     * We extend the list of alternatives for the last snapshot in this
     * chain. If the snapshot is positive. If it's negative there will be
     * an exception raised.
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
