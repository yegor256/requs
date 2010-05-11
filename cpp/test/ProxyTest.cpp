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
#include <boost/algorithm/string/join.hpp>>
#include "rqdql.h"
#include "Solm.h"
#include "Proxy.h"
#include "Logger.h"
using namespace proxy;
using namespace std;

rqdql::LogLevel rqdql::level = L_DEBUG;

void setUp() {
    rqdql::Logger::getInstance().clear();
    Proxy::getInstance().clear();
    Solm::getInstance().clear();
}

void tearDown() {
    if (!rqdql::Logger::getInstance().empty()) {
        rqdql::log("Log report is not empty:\n" + rqdql::Logger::getInstance().getReport());
    }
}

void testGabrageCollectionWorksProperly() {
    setUp();
    Proxy::getInstance().getTypeNames();
    Proxy::getInstance().getType("User");
    Proxy::getInstance().getTypeNames();
    Proxy::getInstance().clear();
    tearDown();
}

void testContainerWorksProperly() {
    setUp();
    Proxy::getInstance().getType("User");
    Proxy::getInstance().getType("Photo");
    Proxy::getInstance().getType("File");
    Proxy::getInstance().getType("File");
    BOOST_CHECK(Proxy::getInstance().countTypes() > 3); // + text, numeric, etc.
    rqdql::log(
        boost::format("Types in container: %s") % 
        boost::algorithm::join(Proxy::getInstance().getTypeNames(), ", ")
    );
    tearDown();
}

void testWeCanBuildNewType() {
    setUp();
    Type* t = Proxy::getInstance().getType("User");
    t->addSlot(
        new Slot(
            "email", 
            "1..n -> 1", 
            new solm::Info("email address"), 
            Proxy::getInstance().getType("text")
        )
    )
    ->addSlot(
        new Slot(
            "photos", 
            "1..n -> 0..n", 
            new solm::Info("a collection of photos"), 
            Proxy::getInstance().getType("Photo")
        )
    )
    ->addSlot(
        new Slot(
            "manager", 
            "1..n -> 1", 
            new solm::Info("user's manager, if any"), 
            Proxy::getInstance().getType("User")
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

    BOOST_CHECK(Proxy::getInstance().countTypes() >= 3); // User, string, and Photo
    
    rqdql::log("Definition of type 'User': " + Proxy::getInstance().getType("User")->toString());
    tearDown();
}

void fillUseCase(UseCase* uc) {
    uc
    ->setSignature(
        (new Signature("${sud} validate ${photo}"))
        ->explain("photo", new Signature::ExpType(Proxy::getInstance().getType("Photo")))
    )
    ->addFlow(
        1,
        new Flow(
            "The user creates photo of himself (the photo)",
            (new Signature("${user} creates ${photo}"))
            ->explain("photo", new Signature::ExpObject("photo", "himself"))
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
                ->explain("photo", new Signature::ExpObject("photo", "himself"))
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
    UseCase* uc = Proxy::getInstance().getUseCase("UC1");
    fillUseCase(uc);
    rqdql::log(uc->toString());
    tearDown();
}

void testWeCanInjectUseCase() {
    setUp();
    UseCase* uc = Proxy::getInstance().getUseCase("UC1");
    
    fillUseCase(uc);
        
    Proxy::getInstance().inject();

    vector<string> list = solm::Solm::getInstance().getAllFunctions();
    BOOST_CHECK(list.size() >= 2);
    rqdql::log(
        boost::format("Totally created %d functions: %s") % 
        list.size() %
        boost::algorithm::join(list, ", ")
    );
    
    // show it all as string
    rqdql::log(solm::Solm::getInstance().toString());
    tearDown();
}

int test_main(int, char *[]) {
    testGabrageCollectionWorksProperly();
    testContainerWorksProperly();
    testWeCanBuildNewType();
    testWeCanBuildNewUseCase();
    testWeCanInjectUseCase();
    
    return 0;
}
