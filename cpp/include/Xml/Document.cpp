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

#include "Xml/Document.h"
#include "Xml/Node.h"

#include <string>
#include <pugixml/pugixml.hpp>

/**
 * Create and return a root element of the document
 */
Xml::Node Xml::Document::root(const std::string& name) {
    pugi::xml_node n = append_child();
    n.set_name(name.c_str());
    return Node(n);
}

/**
 * Convert full report into STRING
 */
const string Xml::Document::asXml() const {
    ostringstream stream;
    stream << "<?xml version=\"1.0\" ?>\n";
    print(stream, "  ");
    return stream.str();
}

