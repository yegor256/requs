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

#include "AbstractTestCase.h"

using namespace solm;

void testSimple() {
    rqdql::get<Solm>().clear();
    Math* math = new Math(">");
    math->arg("5")->arg("3");
    rqdql::get<Solm>().addFormula(math);
    
    BOOST_REQUIRE(rqdql::get<Solm>().countTypes<Math>() >= 1);
}

void testMoreComplexStructure() {
    rqdql::get<Solm>().clear();
    
    rqdql::get<Solm>().addFormula(
        (new Declaration("UC8"))
        ->arg("x")
        ->setFormula(
            (new Math(">"))
            ->arg("5")
            ->arg("3")
        )
    );
    
    rqdql::get<Solm>().addFormula(
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
    BOOST_REQUIRE(rqdql::get<Solm>().countTypes<Sequence>() == 1);
    BOOST_REQUIRE(rqdql::get<Solm>().countTypes<Function>() == 2);
}

void testComplex() {
    rqdql::get<Solm>().clear();
    rqdql::get<Solm>().addFormula(
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
        
    int cntSilent = rqdql::get<Solm>().countTypes<Silent>();
    BOOST_REQUIRE(cntSilent > 0);
    cout << boost::format("Totally %d SILENT() formulas") % cntSilent << endl;

    int cntManipulators = 
        rqdql::get<Solm>().countTypes<Created>()
        + rqdql::get<Solm>().countTypes<Deleted>()
        + rqdql::get<Solm>().countTypes<Read>();
    BOOST_REQUIRE(cntManipulators > 0);
    cout << boost::format("Totally %d manipulators") % cntManipulators << endl;

    double ambiguity = rqdql::get<Solm>().getAmbiguity();
    BOOST_REQUIRE(ambiguity == (double)cntSilent / (cntManipulators + cntSilent));
    
    cout << boost::format("scope ambiguity is: %0.2f") % ambiguity << endl;

    // show it all as string
    cout << rqdql::get<Solm>().toString() << endl;
}

void testWeCanFindAllFunctionDeclarations() {
    rqdql::get<Solm>().clear();
    rqdql::get<Solm>()
        .addFormula((new Declaration("User"))->arg("x")->setFormula(new Info("nothing to say")))
        ->addFormula((new Declaration("Photo"))->arg("x")->setFormula(new Info("nothing to say")))
        ->addFormula((new Declaration("File"))->arg("x")->setFormula(new Info("nothing to say")))
        ->addFormula((new Declaration("Image"))->arg("x")->setFormula(new Info("nothing to say")));
        
    vector<string> list = rqdql::get<Solm>().getAllFunctions();
    BOOST_REQUIRE(list.size() >= 4);
    cout <<
        boost::format("Totally found %d functions: %s") % 
        list.size() %
        boost::algorithm::join(list, ", ") << endl;
}

void testFactsOperatorsWork() {
    Silent* f = new Silent("'just test");
    FactPath fp1;
    fp1.push_back(Fact(f, true));
    fp1.push_back(Fact(f, true));

    FactPath fp2;
    fp2.push_back(Fact(f, true));
    
    BOOST_REQUIRE((fp1 + fp2).size() == 3);
}

void testOutcomesAreProperlyReturned() {
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

    Outcome out;
    try {
        out = f->getOutcome();
    } catch (rqdql::Exception e) {
        cout << "exception: " << e.getMessage() << endl;
        BOOST_REQUIRE(false);
    }
    BOOST_REQUIRE(out.size() > 0);
    
    vector<FactPath> fp = out.getPaths();
    // BOOST_REQUIRE(fp.size() == 5);
    for (vector<FactPath>::const_iterator i = fp.begin(); i != fp.end(); ++i) {
        cout << "new path:\n" << (*i).toString() << endl;
    }
}

int test_main(int, char *[]) {
    testSimple();
    testMoreComplexStructure();
    testComplex();
    testWeCanFindAllFunctionDeclarations();
    testFactsOperatorsWork();
    testOutcomesAreProperlyReturned();
    
    return 0;
}
