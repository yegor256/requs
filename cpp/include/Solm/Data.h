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

#ifndef __INCLUDE_SOLM_DATA_H
#define __INCLUDE_SOLM_DATA_H

#include <string>
#include <map>
#include "Solm/Chain.h"
#include "Solm/Rule.h"

namespace solm {

/**
 * Prolog-style set of clauses
 */
class Data {

public:
    
    /**
     * An answer we can give to the question asked
     */
    class Answer {
    public:
        operator bool() const { return _success; }
        bool has(const std::string& v) { return _values.find(v) != _values.end(); }
        const std::string& operator[](const std::string& v) const { return _values.find(v)->second; }
    private:
        friend class Data;
        bool _success;
        std::map<std::string, std::string> _values;
        Answer(bool s, const std::map<std::string, std::string>& v) : _success(s), _values(v) { /* that's it */ }
    };

    /**
     * Public constructor
     */
    Data();

    /**
     * The data block is positive?
     */
    operator bool() const { return true; }

    /**
     * Add new alternative Data block
     */
    Data& operator<<(const Data&);
    
    /**
     * Make a prolog-styled question, providing a simple rule
     * and get an answer.
     */
    const Answer question(const Rule&);

private:
    
    /**
     * Collection of rules
     */
    std::vector<Rule> _facts;
    
    /**
     * Alternative clauses
     */
    Chain _alternatives;
    
};

}

#endif
