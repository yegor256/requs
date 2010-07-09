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
 * @version $Id$
 */

#include <string>
#include <boost/regex.hpp> // boost::regex_match
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join()
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Solm/Formula/Declaration.h"

solm::Declaration::Declaration(const std::string& n) : 
    solm::Variadic(solm::Variadic::OP_AND), solm::Parametrized<solm::Declaration>() {
    if (!boost::regex_match(n, boost::regex("[a-zA-Z][a-zA-Z0-9\\.]+"))) {
        throw rqdql::Exception(
            boost::format("Invalid name for a function: '%s'") % n
        );
    }
    _name = n;
}

solm::Chain solm::Declaration::operator+(const solm::Context&) {
    // Fact fact;
    // fact.setFormula(this);
    // 
    // Snapshot s = f.getSnapshot();
    // for (Vars::const_iterator i = getVars().begin(); i != getVars().end(); ++i) {
    //     Snapshot::Object& obj = s.create("");
    //     s.assignName(obj, *i);
    //     s.assignId(obj);
    // }
    // fact.setSnapshot(s);
    // 
    // return (Outcome() << fact) + getFormula()->getOutcome(fact); 
    return Chain();
}

solm::Declaration::operator std::string() const { 
    return 
        _name 
        + "(" 
        + Parametrized<Declaration>::operator std::string()
        + "): " 
        + Variadic::operator std::string();
}
