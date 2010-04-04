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

#ifndef __INCLUDE_SCOPE_STATEMENT_H
#define __INCLUDE_SCOPE_STATEMENT_H

namespace rqdql {
    namespace scope {
        class FurStatement;
        class EntityStatement;
        class QosStatement;
        class EmptyStatement;
        class VerbStatement;
    }
};

#include <string>
#include <vector>
#include <set>
#include "scope.h"
#include "pugixml/pugixml.hpp"

class rqdql::scope::Statement : public rqdql::scope::item {
protected:
    int _startLineNo;
    int _endLineNo;

public:
    class LeftName {
    private:
        std::string _name;
        std::vector<std::string> _attribs;
        std::set<std::string> _tags;
        
    public:
        LeftName(const std::string& = "", const std::string& = "");
        const std::string& getName() { return this->_name; }
        const std::vector<std::string>& getAttribs() { return this->_attribs; }
        const std::set<std::string>& getTags() { return this->_tags; }
        LeftName& addTag(const std::string& tag) { this->_tags.insert(tag); return *this; }
    };
    
    void setStartLineNo(int lineNo);
    void setEndLineNo(int lineNo);

    pugi::xml_node findById(const pugi::xml_node&, const std::string&);
    
    virtual void derive(pugi::xml_node&) = 0;
};

#endif
