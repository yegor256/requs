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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Front.h
 */

#include <vector>
#include "rqdql.h"
#include "Front/Tc.h"
#include "Xml/Node.h"
#include "Analysts.h"
#include "Analysts/Tc.h"

void front::Tc::fill(Xml::Node& n) {
    using namespace std;
    
    vector<TestCase*> v = rqdql::get<Analyst>().retrieve();

    for (vector<TestCase*>::const_iterator i = v.begin(); i != v.end(); ++i) {
        Xml::Node tc = (n / "cases" + "tc");
        tc["name"] = (*i)->getName();
        
        // list test case steps
        tc / "model" = (*i)->getXmi();
    }
}


