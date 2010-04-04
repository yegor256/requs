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

#ifndef __INCLUDE_SCOPE_STATEMENT_FUR_H
#define __INCLUDE_SCOPE_STATEMENT_FUR_H

#include "pugixml/pugixml.hpp"
#include "scope/Statement.h"

class rqdql::scope::FurStatement : public rqdql::scope::Statement {
private:
    LeftName _name; // name of the FUR, like R6.7, R5 or R9.3.6, with attribs
    
public:
    FurStatement(const LeftName& name) : Statement(), _name(name) {
        /* that's it */
    };
    void appendXmlNode(pugi::xml_node&);
};

#endif
