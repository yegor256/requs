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
 * @version $Id: ScopeTest.cpp 1487 2010-04-01 08:45:47Z yegor256@yahoo.com $
 */

#include <boost/test/minimal.hpp>
#include <string>
#include "rqdql.h"
#include "Solm.h"
using namespace solm;
using namespace std;

rqdql::LogLevel rqdql::level = L_DEBUG;

void testSimple() {
    Solm::getInstance().clear();
    Math* math = new Math(">");
    math->addVar("'5")->addVar("'3");
    Solm::getInstance().add(math);
    
    BOOST_CHECK(Solm::getInstance().countTypes<Math>() == 1);
}

void testMoreComplexStructure() {
    Solm::getInstance().clear();
    
    Solm::getInstance().add(
        (new Declaration("UC8"))
        ->addVar("x")
        ->setFormula(
            (new Math(">"))
            ->addVar("'5")
            ->addVar("'3")
        )
    );
    
    Solm::getInstance().add(
        (new Declaration("UC14"))
        ->addVar("x")
        ->setFormula(
            (new Sequence())
            ->addFormula((new Function("User"))->addVar("x"))
            ->addFormula(
                (new Exists())
                ->addVar("P")
                ->setFormula((new Function("User.photos"))->addVar("x")->addVar("P"))
            )
        )
    );
    BOOST_CHECK(Solm::getInstance().countTypes<Sequence>() == 1);
    BOOST_CHECK(Solm::getInstance().countTypes<Function>() == 2);
}

void testComplex() {
    Solm::getInstance().clear();
    Solm::getInstance().add(
        (new Declaration("UC1"))
        ->addVar("x")
        ->setFormula(
            (new Sequence())
            ->addFormula((new Function("User"))->addVar("x"))
            ->addFormula(
                (new Exists())
                ->addVar("P")
                ->setFormula((new Function("User.photos"))->addVar("x")->addVar("P"))
            )
            ->addFormula(
                (new Sequence())
                ->addFormula(
                    (new And())
                    ->setLhs((new Math(">"))->addVar("P")->addVar("'5"))
                    ->setRhs((new Info())->addVar("'If number of photos of the user is greater than 5"))
                )
                ->addFormula(
                    (new Exists())
                    ->addVar("y")
                    ->setFormula((new In())->addVar("y")->addVar("P"))
                )
                ->addFormula(
                    (new And())
                    ->setLhs((new Deleted())->addVar("y"))
                    ->setRhs((new Info())->addVar("'The user deletes photo of himself"))
                )
            )    
            ->addFormula(
                (new Exists())
                ->addVar("p")
                ->setFormula((new In())->addVar("p")->addVar("P"))
            )
            ->addFormula(
                (new And())
                ->setLhs((new Created())->addVar("p")->addVar("x"))
                ->setRhs((new Info())->addVar("'The user creates photo of himself (the photo)"))
            )
            ->addFormula(
                (new Sequence(Sequence::OP_OR))
                ->addFormula(
                    (new And())
                    ->setLhs((new Function("UC2"))->addVar("p"))
                    ->setRhs((new Info())->addVar("'We validate the photo immediately"))
                )
                ->addFormula(
                    (new Sequence())
                    ->addFormula((new Caught())->addVar("'file format is not valid"))
                    ->addFormula(
                        (new And())
                        ->setLhs((new Deleted())->addVar("p"))
                        ->setRhs((new Info())->addVar("'We delete the photo"))
                    )
                    ->addFormula((new Throw())->addVar("'only PNG images are accepted"))
                )
            )
            ->addFormula((new Silent())->addVar("'We protocol the operation in backlog"))
            ->addFormula(
                (new And())
                ->setLhs((new Read())->addVar("p")->addVar("x"))
                ->setRhs((new Info())->addVar("'The user reads the photo"))
            )
        )
    );
        
    int cntSilent = Solm::getInstance().countTypes<Silent>();
    BOOST_CHECK(cntSilent > 0);
    rqdql::log(boost::format("Totally %d SILENT() formulas") % cntSilent);

    int cntManipulators = 
        Solm::getInstance().countTypes<Created>()
        + Solm::getInstance().countTypes<Deleted>()
        + Solm::getInstance().countTypes<Read>();
    BOOST_CHECK(cntManipulators > 0);
    rqdql::log(boost::format("Totally %d manipulators") % cntManipulators);

    double ambiguity = Solm::getInstance().getAmbiguity();
    BOOST_CHECK(ambiguity == (double)cntSilent / cntManipulators);
    
    rqdql::log(boost::format("scope ambiguity is: %0.2f") % ambiguity);
}

int test_main(int, char *[]) {
    testSimple();
    testMoreComplexStructure();
    testComplex();
    
    return 0;
}
