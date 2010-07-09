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

#ifndef __INCLUDE_SCOPE_XML_DOCUMENT_H
#define __INCLUDE_SCOPE_XML_DOCUMENT_H

#include <string>
#include <pugixml/pugixml.hpp>

namespace Xml {

/**
 * Forward declaration
 */
class Node;

/**
 * Standalone document
 */
class Document : public pugi::xml_document {

public:

    /**
     * Create and return a root element of the document
     */
    Node root(const std::string&);

    /**
     * Convert XML Document into string
     */
    const std::string asXml() const;

};

}

#endif
