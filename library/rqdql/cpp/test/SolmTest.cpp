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
#include <boost/algorithm/string/join.hpp>
#include <string>
#include <iostream>
#include "rqdql.h"
#include "Solm.h"
#include "Logger.h"
using namespace solm;
using namespace std;

rqdql::LogLevel rqdql::level = L_DEBUG;

void testSimple() {
    Solm::getInstance().clear();
    Math* math = new Math(">");
    math->arg("5")->arg("3");
    Solm::getInstance().addFormula(math);
    
    BOOST_CHECK(Solm::getInstance().countTypes<Math>() >= 1);
}

void testMoreComplexStructure() {
    Solm::getInstance().clear();
    
    Solm::getInstance().addFormula(
        (new Declaration("UC8"))
        ->arg("x")
        ->setFormula(
            (new Math(">"))
            ->arg("5")
            ->arg("3")
        )
    );
    
    Solm::getInstance().addFormula(
        (new Declaration("UC14"))
        ->arg("x")
        ->setFormula(
            (new Sequence())
            ->addFormula((new Function("User"))->arg("x"))
            ->addFormula(
                (new Exists())
                ->arg("P")
                ->setFormula((new Function("User.photos"))->arg("x")->arg("P"))
            )
        )
    );
    BOOST_CHECK(Solm::getInstance().countTypes<Sequence>() == 1);
    BOOST_CHECK(Solm::getInstance().countTypes<Function>() == 2);
}

void testComplex() {
    Solm::getInstance().clear();
    Solm::getInstance().addFormula(
        (new Declaration("UC1"))
        ->arg("x")
        ->setFormula(
            (new Sequence())
            ->addFormula((new Function("User"))->arg("x"))
            ->addFormula(
                (new Exists())
                ->arg("P")
                ->setFormula((new Function("User.photos"))->arg("x")->arg("P"))
            )
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
        )
    );
        
    int cntSilent = Solm::getInstance().countTypes<Silent>();
    BOOST_CHECK(cntSilent > 0);
    cout << boost::format("Totally %d SILENT() formulas") % cntSilent << endl;

    int cntManipulators = 
        Solm::getInstance().countTypes<Created>()
        + Solm::getInstance().countTypes<Deleted>()
        + Solm::getInstance().countTypes<Read>();
    BOOST_CHECK(cntManipulators > 0);
    cout << boost::format("Totally %d manipulators") % cntManipulators << endl;

    double ambiguity = Solm::getInstance().getAmbiguity();
    BOOST_CHECK(ambiguity == (double)cntSilent / cntManipulators);
    
    cout << boost::format("scope ambiguity is: %0.2f") % ambiguity << endl;

    // show it all as string
    cout << Solm::getInstance().toString() << endl;
}

void testWeCanFindAllFunctionDeclarations() {
    Solm::getInstance().clear();
    Solm::getInstance()
        .addFormula((new Declaration("User"))->arg("x")->setFormula(new Info("nothing to say")))
        ->addFormula((new Declaration("Photo"))->arg("x")->setFormula(new Info("nothing to say")))
        ->addFormula((new Declaration("File"))->arg("x")->setFormula(new Info("nothing to say")))
        ->addFormula((new Declaration("Image"))->arg("x")->setFormula(new Info("nothing to say")));
        
    vector<string> list = Solm::getInstance().getAllFunctions();
    BOOST_CHECK(list.size() >= 4);
    cout <<
        boost::format("Totally found %d functions: %s") % 
        list.size() %
        boost::algorithm::join(list, ", ") << endl;
}

int test_main(int, char *[]) {
    testSimple();
    testMoreComplexStructure();
    testComplex();
    testWeCanFindAllFunctionDeclarations();
    
    return 0;
}
