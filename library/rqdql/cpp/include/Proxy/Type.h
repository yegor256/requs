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

/**
 * Validates whether the TYPE has static name.
 */
bool Type::hasName() const {
    return rqdql::get<Proxy>().hasName(this);
}

/**
 * Returns a name of the TYPE if it is in the static
 * holder now. Otherwise will throw an exception. You should use
 * hasName() in order to validate before.
 */
const string Type::getName() const {
    try {
        return rqdql::get<Proxy>().findName(this);
    } catch (rqdql::Exception e) {
        throw rqdql::Exception(rqdql::_t("Type doesn't have a name, but getName() called"));
    }
}

/**
 * Find slot by name or create it if not found
 */
Slot* Type::getSlot(const string& s) {
    for (Slots::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if ((*i)->getName() == s) {
            return (*i);
        }
    }
    addSlot(s);
    return getSlot(s);
}

/**
 * Explicitly add new slot to the type
 */
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
    if (slots.empty()) {
        return "{}";
    }
    
    string s = "{\n";
    for (Slots::const_iterator i = slots.begin(); i != slots.end(); ++i) {
        if (i != slots.begin()) {
            s = s + ";\n";
        }
        s = s + "\t" + (*i)->getName() + "[" + (*i)->getCardinality().toString() + "]: ";
        if ((*i)->getType()->hasName()) {
            s = s + (*i)->getType()->getName();
        } else {
            s = s + boost::algorithm::replace_all_copy((*i)->getType()->toString(), "\n", "\n\t");
        }
    }
    return s + "\n}";
}

solm::Formula* Type::makeFormula(const string& x) const {
    using namespace solm;
    // This TYPE is empty and it's definitely an error
    // in text, but we anyway should work with this type. Thus,
    // we report about a problem here and continue.
    if (isEmpty() && hasName()) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("Entity '%s' is empty, probably its name is misspelled")) % getName()).str()
        );
        return new Err(rqdql::_t("'entity is empty"));
    }
    
    // This is a new declaration of a type. Again, if the TYPE doesn't
    // have a predicated, we don't skip it, but work with it.
    Sequence* sequence;
    if (hasPredicate()) {
        sequence = getPredicate();
    } else {
        if (hasName()) {
            rqdql::get<rqdql::Logger>().log(
                this, 
                (boost::format(rqdql::_t("Entity '%s' doesn't have any textual explanation")) % getName()).str()
            );
        }
        sequence = new Sequence();
    }
    
    // Here we should add slots to the TYPE
    int propertyCounter = 1;
    for (Slots::const_iterator j = slots.begin(); j != slots.end(); ++j) {
        Slot* slot = *j;
        string propertyName = (boost::format("P%d") % propertyCounter).str();
        
        Sequence* sq = new Sequence(Sequence::OP_AND);
        if (slot->getType()->hasName()) {
            sq->addFormula((new Function(slot->getType()->getName()))->arg("p"));
        } else {
            sq->addFormula(slot->getType()->makeFormula("p"));
        }
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
