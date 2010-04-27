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
#include "rqdql.h"
#include "Classe.h"
#include "UseCase.h"
#include "Predicate.h"
using namespace rqdql;

int test_main(int, char *[]) {
    // BOOST_CHECK(true);
    // BOOST_REQUIRE(true);

    Classe actorUser("ActorUser");
    Classe sud("SUD");
    
    // signature of UC
    Signature signature;
    signature << actorUser << "pays his bills to" << sud;
        
    // UC itself
    // UseCase uc(signature);
    // uc[1] = "New expenses report arrived to us by mail"; // just informal
    // uc[2] = Flow(
    //     "We send notification to ActorUser (the user) when possible", 
    //     Signature()
    //         += sud
    //         += "send notification to"
    //         += actorUser
    // );
    // uc[3] = Flow(
    //     "When possible the user pays his bills to us",
    //     Signature()
    //         += actorUser
    //         += "pays his bills to"
    //         += sud
    // );
    // 
    // Flows alt = Flows();
    // alt[1] = "Notify admin about this problem";
    // uc[2]["If there is no email registered"] = alt;
    
    return 0;
}
