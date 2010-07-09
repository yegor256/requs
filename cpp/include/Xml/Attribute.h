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

#ifndef __INCLUDE_SCOPE_XML_ATTRIBUTE_H
#define __INCLUDE_SCOPE_XML_ATTRIBUTE_H

#include <string>
#include <pugixml/pugixml.hpp>

namespace Xml {

/**
 * XML Attribute
 */
class Attribute : public pugi::xml_attribute {

public:

    /**
     * Set attribute value
     */
    template <typename T> void operator=(const T&);

private:
    
    friend class Node;
    
    /**
     * Private constructor, available only to class Node
     */
    Attribute(pugi::xml_attribute& a) : xml_attribute(a) { /* that's it */ }

};

}

#endif
