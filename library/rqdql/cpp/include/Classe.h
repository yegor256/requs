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

#ifndef __INCLUDE_SCOPE_CLASSE_H
#define __INCLUDE_SCOPE_CLASSE_H

#include <string>
#include <vector>
#include "rqdql.h"

/**
 * Class, like "ActorUser" or "files of ..."
 */
class rqdql::Classe {
public:        
    Classe(const std::string& n) : name(n) { /* that's it */ }
    
    Classe& operator+=(const Classe& c) { slots.push_back(c); return *this; }
    Classe& operator[](const std::string& n) throw(rqdql::Exception) {
        for (std::vector<Classe>::iterator i=slots.begin(); i!=slots.end(); i++) {
            if (i->getName() == n) {
                return *i;
            }
        }
        throw new rqdql::Exception(boost::format("slot '%s' not found") % n);
    }

    std::string getName() const { return name; }
    
    void setObject(const std::string& s) { object = s; }
    std::string getObject() const { return object; }

private:
    std::string name;
    std::string object;
    std::vector<Classe> slots;
};

#endif
