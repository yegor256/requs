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
 */

#include "Xml/Node.h"
#include "Xml/Attribute.h"

#include <string>
#include <boost/format.hpp>

Xml::Node operator/(pugi::xml_node n, const std::string& s) {
    pugi::xml_node x = n.child(s.c_str());
    if (x.empty()) {
        x = n.append_child();
        x.set_name(s.c_str());
    }
    return Node(x);
}

Xml::Node Xml::Node::operator+(const std::string& s) {
    pugi::xml_node n = append_child();
    n.set_name(s.c_str());
    return Node(n);
}

Xml::Node& Xml::Node::operator=(const std::string& s) {
    append_child(pugi::node_pcdata).set_value(s.c_str());
    return *this;
}

Xml::Node& Xml::Node::operator=(double d) {
    append_child(pugi::node_pcdata).set_value(
        (boost::format("%0.3f") % d).str().c_str()
    );
    return *this;
}

Xml::Node& Xml::Node::operator=(int i) {
    append_child(pugi::node_pcdata).set_value(
        (boost::format("%d") % i).str().c_str()
    );
    return *this;
}

Xml::Attribute Xml::Node::operator[](const std::string& s) {
    pugi::xml_attribute a = append_attribute(s.c_str());
    return Attribute(a);
}
