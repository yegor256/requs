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
 *
 * This file has to be included ONLY from Analytics.h
 */

namespace tc {
    
/**
 * One fact, positive or negative, with a text explanation.
 */
class Fact {
public:
    Fact(bool p, string t) : positive(p), text(t) { /* that's it */ }
    bool isPositive() const { return positive; }
private:
    bool positive;
    string text;
};

/**
 * Result of any formula from SOLM. Outcome is a collection of
 * facts (where only one is positive).
 */
class Outcome {
public:
    Outcome() : facts() { /* that's it */ }
    bool hasPositive() const;
private:
    vector<Fact*> facts;
};

/**
 * One Test Case, as an instruction to a tester
 */
class TestCase {
public:
    bool isPositive() const;
private:
    string name;
    TestCase* predecessor;
    vector<Fact*> before;
    vector<Fact*> after;
};

/**
 * Builder of Test Cases
 */
class Analyst {
public:
    vector<TestCase*> retrieve() const;
private:
};

#include "Analysts/Tc/AnalystImpl.h"

}
