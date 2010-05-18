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
 * This is a singleton pattern. In order to get an instance
 * of this class you should call getInstance()
 */
Front& Front::getInstance() {
    static Front* front;
    if (!front) {
        front = new Front();
    }
    return *front;
}

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
pugi::xml_document& Front::getXml() {
    using namespace pugi;
    static xml_document* doc;
    
    if (!doc) {
        doc = new xml_document();
    }
    
    xml_node root = doc->append_child();
    root.set_name("rqdql");
    for (vector<Reporter*>::const_iterator i = reporters.begin(); i != reporters.end(); ++i) {
        xml_node r = root.child((*i)->getName().c_str());
        if (r.empty()) {
            r = root.append_child();
            r.set_name((*i)->getName().c_str());
        }
        (*i)->appendNode(r);
    }
    
    return *doc;
}

/**
 * Convert full report into STRING
 */
string Front::asXml() {
    ostringstream stream;
    stream << "<?xml version=\"1.0\" ?>\n";
    getXml().print(stream, "  ");
    return stream.str();
}

