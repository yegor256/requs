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
 * @version $Id$
 */

#include "../AbstractTestCase.h"

using namespace solm;

void testSimple() {
    Formula* f = 
    (new Declaration("UC1"))
        ->arg("x")
        ->setFormula(
            (new Sequence())
            ->addFormula(new Silent("'We receive new file by mail"))
            ->addFormula(
                (new Sequence())
                ->addFormula(new Silent("'File is being validated"))
                ->addFormula(
                    (new Sequence())
                    ->addFormula(new Silent("'What if not?"))
                )
            )
            ->addFormula(new Silent("'We protocol this operation"))
        );

    Outcome out = f->getOutcome();
    cout << "snapshot in the end:\n" << out.getPositiveEnd().getSnapshot().toString() << endl;
    // BOOST_REQUIRE(true);
}

int test_main(int, char *[]) {
    testSimple();
    
    return 0;
}
