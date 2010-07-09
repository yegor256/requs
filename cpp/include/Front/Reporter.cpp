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
 *
 * This file is included ONLY from Front.h
 */

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Front/Reporter.h"
#include "Front/Errors.h"
#include "Front/Links.h"
#include "Front/Metrics.h"
#include "Front/Tc.h"
#include "Front/Uml.h"
#include "Xml/Node.h"
#include "Xml/Attribute.h"

boost::shared_ptr<front::Reporter> front::Reporter::factory(const std::string& n, const front::Reporter::Params& p) {
    boost::shared_ptr<Reporter> r;
    
    std::string name = boost::algorithm::to_lower_copy(n);
    if (name == "errors") {
        r = boost::shared_ptr<Errors>(new Errors(p));
    } else if (name == "uml") {
        r = boost::shared_ptr<Uml>(new Uml(p));
    } else if (name == "metrics") {
        r = boost::shared_ptr<Metrics>(new Metrics(p));
    } else if (name == "tc") {
        r = boost::shared_ptr<Tc>(new Tc(p));
    } else if (name == "links") {
        r = boost::shared_ptr<Links>(new Links(p));
    } else {
        throw rqdql::Exception(
            boost::format("Reporter '%s' is not supported") % n
        );
    }
    r->_name = n;
    return r;
}

void front::Reporter::append(Xml::Node& root) const {
    Xml::Node n = root + _name + "report";
    for (Params::const_iterator i = _params.begin(); i != _params.end(); ++i) {
        n[(*i).first] = (*i).second;
    }
    fill(n);
}

namespace front {
template<> int Reporter::getParam<int>(const std::string& n, const int& d) const {
    if (_params.find(n) == _params.end()) {
        return d;
    }
    return atoi(_params.find(n)->second.c_str());
}
}

namespace front {
template<> bool front::Reporter::getParam<bool>(const std::string& n, const bool& d) const {
    if (_params.find(n) == _params.end()) {
        return d;
    }
    std::string s = boost::algorithm::to_lower_copy(_params.find(n)->second);
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
}
