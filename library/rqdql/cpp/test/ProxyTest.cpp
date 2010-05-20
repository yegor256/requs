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

using namespace proxy;

void testGabrageCollectionWorksProperly() {
    setUp();
    Proxy::getInstance().getNames<Type>();
    Proxy::getInstance().get<Type>("User");
    Proxy::getInstance().getNames<Type>();
    Proxy::getInstance().clear();
    tearDown();
}

void testContainerWorksProperly() {
    setUp();
    Proxy::getInstance().get<Type>("User");
    Proxy::getInstance().get<Type>("Photo");
    Proxy::getInstance().get<Type>("File");
    Proxy::getInstance().get<Type>("File");
    BOOST_REQUIRE(Proxy::getInstance().count<Type>() > 3); // + text, numeric, etc.
    cout <<
        boost::format("Types in container: %s") % 
        boost::algorithm::join(Proxy::getInstance().getNames<Type>(), ", ") << endl;
    tearDown();
}

void testWeCanBuildNewType() {
    setUp();
    Type* t = Proxy::getInstance().get<Type>("User");
    t->addSlot(
        new Slot(
            "email", 
            "1..n -> 1", 
            new solm::Info("email address"), 
            Proxy::getInstance().get<Type>("text")
        )
    )
    ->addSlot(
        new Slot(
            "photos", 
            "1..n -> 0..n", 
            new solm::Info("a collection of photos"), 
            Proxy::getInstance().get<Type>("Photo")
        )
    )
    ->addSlot(
        new Slot(
            "manager", 
            "1..n -> 1", 
            new solm::Info("user's manager, if any"), 
            Proxy::getInstance().get<Type>("User")
        )
    )
    ->addSlot(
        new Slot(
            "address", 
            "1..n -> 1", 
            new solm::Info(""), 
            (new Type())->addSlot("city")->addSlot("country")->addSlot("street")
        )
    );
    
    Proxy::getInstance().inject();

    BOOST_REQUIRE(Proxy::getInstance().count<Type>() >= 3); // User, string, and Photo
    
    cout << "Definition of type 'User': " 
    << Proxy::getInstance().get<Type>("User")->toString() << endl;
    tearDown();
}

void fillUseCase(UseCase* uc) {
    uc
    ->setSignature(
        (new Signature("${sud} validate ${photo}"))
        ->explain("photo", new Signature::Explanation(Proxy::getInstance().get<Type>("Photo")))
    )
    ->addFlow(
        1,
        new Flow(
            "The user creates photo of himself (the photo)",
            (new Signature("${user} creates ${photo}"))
            ->explain("photo", new Signature::Explanation("photo", "himself"))
        )
    )
    ->addFlow(
        2,
        new Flow(
            "We validate the photo immediately",
            new Signature("${sud} validate ${photo}")
        )
    )
    ->addFlow(
        3,
        new Flow(
            "We protocol the operation in backlog"
        )
    )
    ->addFlow(
        4,
        new Flow(
            "The user reads the photo",
            new Signature("${user} read ${photo}")
        )
    );
    
    uc->getFlow(0)->addAlternative(new solm::Info("'number of photos of the user is greater than 5"))
        ->addFlow(
            1,
            new Flow(
                "The user deletes photo of himself",
                (new Signature("${user} read ${photo}"))
                ->explain("photo", new Signature::Explanation("photo", "himself"))
            )
        );
        
    uc->getFlow(2)->addAlternative((new solm::Caught())->arg("'file format is not valid"))
        ->addFlow(
            1,
            new Flow(
                "We delete the photo",
                new Signature("${sud} delete ${photo}")
            )
        )
        ->addFlow(
            2,
            new Flow(
                "Fail with \"only PNG images\" are accepted"
            )
        );
}

void testWeCanBuildNewUseCase() {
    setUp();
    UseCase* uc = Proxy::getInstance().get<UseCase>("UC1");
    fillUseCase(uc);
    cout << uc->toString() << endl;
    tearDown();
}

void testWeCanInjectUseCase() {
    setUp();
    UseCase* uc = Proxy::getInstance().get<UseCase>("UC1");
    
    fillUseCase(uc);
        
    Proxy::getInstance().inject();

    vector<string> list = solm::Solm::getInstance().getAllFunctions();
    BOOST_REQUIRE(list.size() >= 2);
    cout <<
        boost::format("Totally created %d functions: %s") % 
        list.size() %
        boost::algorithm::join(list, ", ") << endl;
    
    // show it all as string
    cout << solm::Solm::getInstance().toString() << endl;
    tearDown();
}

void testUseCasesMatchEachOther() {
    setUp();
    UseCase* uc1 = Proxy::getInstance().get<UseCase>("UC1");
    uc1->setSignature(
        (new Signature("${sud} validate ${photo}"))
        ->explain("photo", new Signature::Explanation(Proxy::getInstance().get<Type>("Photo")))
    );
    uc1->addFlow(
        1,
        new Flow("We check that it's either PNG or GIF")
    );
    
    UseCase* uc2 = Proxy::getInstance().get<UseCase>("UC2");
    uc2->setSignature(
        (new Signature("${user} upload ${photo}"))
        ->explain("photo", new Signature::Explanation(Proxy::getInstance().get<Type>("Photo")))
    );
    uc2->addFlow(
        1,
        new Flow(
            "We validate the photo",
            (new Signature("${sud} validate ${photo}"))
            ->explain("photo", new Signature::Explanation(Proxy::getInstance().get<Type>("Photo")))
        )
    );
    
    Proxy::getInstance().inject();
    cout << solm::Solm::getInstance().toString() << endl;
    tearDown();
}

int test_main(int, char *[]) {
    testGabrageCollectionWorksProperly();
    testContainerWorksProperly();
    testWeCanBuildNewType();
    testWeCanBuildNewUseCase();
    testWeCanInjectUseCase();
    testUseCasesMatchEachOther();
    
    return 0;
}
