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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Proxy.h
 */

const string Type::getName() const {
    return Proxy::getInstance().findTypeName(this);
}

Type* Type::getSlot(const string& s) {
    for (Slots::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if ((*i)->getName() == s) {
            return (*i);
        }
    }
    return addSlot(s);
}

Type* Type::addSlot(Slot* s) { 
    slots.push_back(s); 
    return this;
}

Type* Type::addPredicate(solm::Formula* f) {
    if (!predicate) {
        predicate = new solm::Sequence(solm::Sequence::OP_AND);
    }
    predicate->addFormula(f);
    return this;
}

Type* Type::addSlot(const string& s) {
    return addSlot(new Slot(s));
}

/**
 * To convert type into string detailed presentation
 */
const string Type::toString() const {
    string s = "{";
    for (Slots::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if (i != slots.begin()) {
            s += "; ";
        }
        // be aware of possible end-less recursion !!
        s += (*i)->getName() + ": " + (*i)->getType()->getName();
    }
    return s + "}";
}
