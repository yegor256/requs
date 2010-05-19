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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Front.h
 */

/**
 * Create new instance of the class
 */
Reporter* Reporter::factory(const string& n, const Params& p) {
    Reporter* r;
    
    string name = boost::algorithm::to_lower_copy(n);
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
        throw (boost::format("Reporter '%s' is not supported") % n).str();
    }
    r->name = n;
    return r;
}

/**
 * Append new node to the holder
 */
void Reporter::appendNode(pugi::xml_node& r) {
    pugi::xml_node n = r.append_child();
    n.set_name("report");
    
    for (Params::const_iterator i = params.begin(); i != params.end(); ++i) {
        n.append_attribute((*i).first.c_str()).set_value((*i).second.c_str());
    }
    
    fillNode(n);
}

/**
 * Get INTEGER parameter
 */
template<> int Reporter::getParam<int>(const string& n, const int& d) {
    if (params.find(n) == params.end()) {
        return d;
    }
    return atoi(params[n].c_str());
}

/**
 * Get BOOLEAN parameter
 */
template<> bool Reporter::getParam<bool>(const string& n, const bool& d) {
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
    return false;
}
