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

Slot* Type::getSlot(const string& s) {
    for (Slots::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if ((*i)->getName() == s) {
            return (*i);
        }
    }
    addSlot(s);
    return getSlot(s);
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

solm::Formula* Type::makeFormula(const string& x) const {
    using namespace solm;
    // This TYPE is empty and it's definitely an error
    // in text, but we anyway should work with this type. Thus,
    // we report about a problem here and continue.
    if (isEmpty()) {
        rqdql::Logger::getInstance().log(
            this, 
            (boost::format("Entity '%s' is empty, probably its name is misspelled") % getName()).str()
        );
        return new Err("'entity is empty");
    }
    
    // This is a new declaration of a type. Again, if the TYPE doesn't
    // have a predicated, we don't skip it, but work with it.
    Sequence* sequence;
    if (hasPredicate()) {
        sequence = getPredicate();
    } else {
        rqdql::Logger::getInstance().log(
            this, 
            (boost::format("Entity '%s' doesn't have any textual explanation") % getName()).str()
        );
        sequence = new Sequence();
    }
    
    // Here we should add slots to the TYPE
    int propertyCounter = 1;
    for (Slots::const_iterator j = slots.begin(); j != slots.end(); ++j) {
        Slot* slot = *j;
        string propertyName = (boost::format("P%d") % propertyCounter).str();
        
        Sequence* sq = new Sequence(Sequence::OP_AND);
        sq->addFormula((new Function(slot->getType()->getName()))->arg("p"));
        sq->addFormula((new Function("composition"))->arg(x)->arg("p"));
        sq->addFormula(slot->getFormula());
        
        Exists* e = (new Exists())
            ->arg(propertyName)
            ->setFormula(
                (new And())
                ->setLhs(
                    (new Math("="))
                    ->arg("|" + propertyName + "|")
                    ->arg("1")
                )
                ->setRhs(
                    (new Forall())
                    ->arg("p")
                    ->setFormula(
                        (new Sequence())
                        ->addFormula(
                            (new In())
                            ->arg("p")
                            ->arg(propertyName)
                        )
                        ->addFormula(sq)
                    )
                )
            );
        sequence->addFormula(e);
        propertyCounter++;
    }
    return sequence;
}
