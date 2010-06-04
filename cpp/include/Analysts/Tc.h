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
 * One step in a Test Case
 */
class TestStep {
public:
    const string getText() const { return "step"; }
    const vector<int> getLines() const;
private:
};    

/**
 * One Test Case, as an instruction to a tester
 */
class TestCase {
public:
    TestCase(const solm::FactPath& fp) : name() { /* that's it */ }
    void setName(const string& s) { name = s; }
    const string getName() const { return name; }
    const vector<TestStep> computeSteps() const { return vector<TestStep>(); }
private:
    string name;
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
#include "Analysts/Tc/TestStep.h"
#include "Analysts/Tc/TestCase.h"

}
