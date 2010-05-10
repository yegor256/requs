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

void Formula::setFormula(Formula* f, size_t i) {
    if (subs.size() < i+1) {
        subs.resize(i+1);
    }
    subs[i] = f;
}

Formula* Formula::getFormula(size_t i) const {
    if (i > subs.size()-1) {
        return new Constant(true);
    }
    return subs.at(i);
}

