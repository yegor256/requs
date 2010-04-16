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
 * @version $Id: Action.h 1491 2010-04-02 16:48:51Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_CLASSE_H
#define __INCLUDE_SCOPE_CLASSE_H

#include <string>
#include "Scope.h"

class rqdql::Classe {
public:    
    enum Plurality { SINGULAR, MANY, SOME, ANY };

    Object& setPlurality(Plurality plurality) { this->_plurality = plurality; return *this; }

private:
};

#endif
