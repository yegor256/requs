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
 * This file is included ONLY from Front.h
 */

void Tc::fillNode(pugi::xml_node& n) {
    using namespace pugi;
    using namespace analysts::tc;
    vector<TestCase*> v = rqdql::get<Analyst>().retrieve();

    for (vector<TestCase*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        PugiNodeWrapper tc = (n / "cases" + "tc");
        tc["name"] = (*i)->getName();
        
        // list test case steps
        vector<TestStep> steps = (*i)->computeSteps();
        for (vector<TestStep>::const_iterator step = steps.begin(); step != steps.end(); ++step) {
            xml_node fact = tc / "facts" + "fact";
            fact / "text" = (*step).getText();
            vector<int> lines = (*step).getLines();
            for (vector<int>::const_iterator j = lines.begin(); j != lines.end(); ++j) {
                fact / "lines" + "line" = *j;
            }
        }
    }
}


