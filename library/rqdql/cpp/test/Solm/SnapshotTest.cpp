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
    rqdql::get<Solm>().addFormula(
        (new Declaration("User"))
        ->arg("u")
        ->setFormula((new Function("number"))->arg("u"))
    );
    
    Formula* f = 
        (new Declaration("UC1"))
        ->arg("x")
        ->setFormula(
            (new Sequence())
            ->addFormula((new Function("User"))->arg("x"))
            ->addFormula(
                (new Exists())
                ->arg("P")
                ->setFormula((new Function("User.photo"))->arg("x")->arg("P"))
            )
            ->addFormula(new Silent("'oops"))
            ->addFormula(
                (new Sequence())
                ->addFormula(
                    (new And())
                    ->setLhs((new Math(">"))->arg("P")->arg("5"))
                    ->setRhs(new Info("'If number of photos of the user is greater than 5"))
                )
                ->addFormula(
                    (new Exists())
                    ->arg("y")
                    ->setFormula((new In())->arg("y")->arg("P"))
                )
                ->addFormula(
                    (new And())
                    ->setLhs((new Deleted())->arg("y"))
                    ->setRhs(new Info("'The user deletes photo of himself"))
                )
            )    
            // ->addFormula(new Silent("'oops"))
            ->addFormula(
                (new Exists())
                ->arg("p")
                ->setFormula((new In())->arg("p")->arg("P"))
            )
            ->addFormula(
                (new And())
                ->setLhs((new Created())->arg("p")->arg("x"))
                ->setRhs(new Info("'The user creates photo of himself (the photo)"))
            )
            ->addFormula(
                (new Sequence(Sequence::OP_OR))
                ->addFormula(
                    (new And())
                    ->setLhs((new Function("UC2"))->arg("p"))
                    ->setRhs(new Info("'We validate the photo immediately"))
                )
                ->addFormula(
                    (new Sequence())
                    ->addFormula((new Caught())->arg("'file format is not valid"))
                    ->addFormula(
                        (new And())
                        ->setLhs((new Deleted())->arg("p"))
                        ->setRhs(new Info("'We delete the photo"))
                    )
                    ->addFormula((new Throw())->arg("'only PNG images are accepted"))
                )
            )
            ->addFormula(new Silent("'We protocol the operation in backlog"))
            ->addFormula(
                (new And())
                ->setLhs((new Read())->arg("p")->arg("x"))
                ->setRhs(new Info("'The user reads the photo"))
            )
        );

    Outcome out = f->getOutcome();
    cout << "snapshot in the end:\n" << out.getPositiveEnd().getSnapshot().toString() << endl;
    // BOOST_REQUIRE(true);
}

vector<testMethod> suite() {
    vector<testMethod> v;
    v.push_back(&testSimple);
    return v;
}
