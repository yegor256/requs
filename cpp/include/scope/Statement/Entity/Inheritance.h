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

#ifndef __INCLUDE_SCOPE_STATEMENT_ENTITY_INHERITANCE_H
#define __INCLUDE_SCOPE_STATEMENT_ENTITY_INHERITANCE_H

#include <string>
#include <vector>
#include "pugixml/pugixml.hpp"
#include "funcs.h"
#include "scope/Statement/Entity.h"

class rqdql::scope::EntityInheritanceStatement : public rqdql::scope::EntityStatement {
private:
    vector<rqdql::scope::Object*> _parents; // name of parent entity

public:
    EntityInheritanceStatement(const LeftName& name, const vector<rqdql::scope::Object*>& parents) :
        EntityStatement(name), _parents(parents) {
        /* nothing more */
    };
    void derive(pugi::xml_node&);
};

#endif
