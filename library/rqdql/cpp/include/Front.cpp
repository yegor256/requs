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
 * @version $Id$
 *
 * This file is included ONLY from Front.h
 */

/**
 * Require this report to appear in final XML
 */
void Front::require(const string& s) {
    string name = s;
    string args;
    if (name.find(":") != name.npos) {
        args = name.substr(name.find(":") + 1); 
        name = name.substr(0, name.find(":"));
    }
    
    Reporter::Params p;
    vector<string> v;
    boost::algorithm::split_regex(v, args, boost::regex(","));
    for (vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
        string val = "true";
        string attr = *i;
        if (attr.empty()) {
            break;
        }
        if (attr.find("=") != attr.npos) {
            val = attr.substr(attr.find("=") + 1); 
            attr = attr.substr(0, attr.find("="));
        }
        p[attr] = val;
    }
    reporters.push_back(Reporter::factory(name, p));
}

/**
 * Get final XML
 */
Xml::Document& Front::getXml() {
    static Xml::Document* doc;
    
    // if the document is not yet initialized - instantiate it now
    if (!doc) {
        Xml::Document doc;
        Xml::Node root = doc.root("rqdql");
        // append reporters one by one to the document
        for (vector<Reporter*>::const_iterator i = reporters.begin(); i != reporters.end(); ++i) {
            Xml::Node n = root / (*i)->getName();
            (*i)->append(n);
        }
    }
    // return a link to this static document
    return *doc;
}

/**
 * Convert full report into STRING
 */
const string Front::asXml() {
    return getXml().asXml();
}
