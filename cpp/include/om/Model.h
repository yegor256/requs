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

#ifndef __INCLUDE_OM_MODEL_H
#define __INCLUDE_OM_MODEL_H

#include <vector>
#include <string>
#include "pugixml/pugixml.hpp"
#include "om.h"
#include "scope.h"

class rqdql::om::Model {
private:
    std::vector<rqdql::scope::Statement> scope;
    pugi::xml_document xml;
    
    void _buildXml();
    void _validateXPointer();
    
public:
    void setScope(const std::vector<rqdql::scope::Statement>&);
    std::string query(const std::string&);
};

#endif
