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

void Metrics::fill(Xml::Node& n) {
    using namespace solm;
    // scope ambiguity
    n / "ambiguity" = rqdql::get<Solm>().getAmbiguity();

    // manipulators to calculate
    n / "manipulatorsCount" = 
        rqdql::get<Solm>().countTypes<Created>()
        + rqdql::get<Solm>().countTypes<Deleted>()
        + rqdql::get<Solm>().countTypes<Read>();

    // silent to calculate
    n / "silentCount" = rqdql::get<Solm>().countTypes<Silent>();

    // total number of errors found
    n / "errorsCount" = (int)rqdql::get<Logger>().size();

    // version of the RQDQL distribution
    n / "version" = RQDQL_VERSION;

    if (getParam<bool>("lists", true)) {
        vector<string> v = rqdql::get<proxy::Proxy>().getNames<proxy::Type>();
        for (vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
            n / "types" + "type" = *i;
        }

        v = rqdql::get<proxy::Proxy>().getNames<proxy::UseCase>();
        for (vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
            n / "useCases" + "uc" = *i;
        }
    }
}


