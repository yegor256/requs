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
 * @version $Id: Fur.cpp 1497 2010-04-04 13:47:20Z yegor256@yahoo.com $
 */

#include <vector>
#include <string>
#include "pugixml/pugixml.hpp"
#include "rqdql.h"
#include "scope/Statement/Entity.h"

void rqdql::scope::EntityStatement::derive(pugi::xml_node& root) {
    pugi::xml_node stmt = root.append_child();
    stmt.set_name("object");
    stmt.append_attribute("id") = this->_name.getName().c_str();
    
    // if this tag is present?
    if (this->_name.getTags().find("actor") != this->_name.getTags().end()) {
        stmt.append_attribute("type") = "actor";
    }
}
