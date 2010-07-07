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

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()
#include "rqdql.h"
#include "Front/Reporter.h"
#include "Xml/Node.h"

/**
 * Create new instance of the class
 */
boost::shared_ptr<Reporter> front::Reporter::factory(const std::string& n, const front::Reporter::Params& p) {
    Reporter* r;
    
    std::string name = boost::algorithm::to_lower_copy(n);
    if (name == "errors") {
        r = new Errors(p);
    } else if (name == "svg") {
        r = new Svg(p);
    } else if (name == "uml") {
        r = new Uml(p);
    } else if (name == "metrics") {
        r = new Metrics(p);
    } else if (name == "tc") {
        r = new Tc(p);
    } else if (name == "links") {
        r = new Links(p);
    } else {
        throw rqdql::Exception(boost::format("Reporter '%s' is not supported") % n);
    }
    r->_name = n;
    return r;
}

/**
 * Append new node to the holder
 * @see Front::getXml()
 */
void front::Reporter::append(Xml::Node& root) {
    Xml::Node n = root + "report";
    for (Params::const_iterator i = params.begin(); i != params.end(); ++i) {
        n[(*i).first] = (*i).second;
    }
    fill(n);
}

/**
 * Get INTEGER parameter
 */
template<> int front::Reporter::getParam<int>(const std::string& n, const int& d) {
    if (params.find(n) == params.end()) {
        return d;
    }
    return atoi(params[n].c_str());
}

/**
 * Get BOOLEAN parameter
 */
template<> bool front::Reporter::getParam<bool>(const std::string& n, const bool& d) {
    if (params.find(n) == params.end()) {
        return d;
    }
    string s = boost::algorithm::to_lower_copy(params[n]);
    if (s == "yes") {
        return true;
    }
    if (s == "on") {
        return true;
    }
    if (s == "true") {
        return true;
    }
    return false;
}
