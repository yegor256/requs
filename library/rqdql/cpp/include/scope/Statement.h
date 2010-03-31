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

class rqdql::scope::Statement : public item {
public:
    void setStartLineNo(int lineNo) {
        this->startLineNo = lineNo;
    }
    void setEndLineNo(int lineNo) {
        this->endLineNo = lineNo;
    }

private:
    int startLineNo;
    int endLineNo;
};

#endif
