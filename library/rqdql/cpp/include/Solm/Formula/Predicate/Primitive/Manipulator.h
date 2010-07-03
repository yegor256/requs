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
 * @version $Id: Sequence.h 1819 2010-05-11 10:37:15Z yegor256@yahoo.com $
 */

/**
 * Find an actor, originator of this manipulation (arg#1)
 */
template <typename T> int Manipulator<T>::findActor(Snapshot& s) const {
    if (Primitive<T>::countVars() < 2) {
        if (!s.hasName(Function::F_SUD)) {
            Snapshot::Object& sud = s.create(Function::F_SUD);
            s.assignId(sud);
            s.assignName(sud, Function::F_SUD);
        }
        return s.getByName(Function::F_SUD).getId();
    }
    return s.getByName(Primitive<T>::getVar(1)).getId();
}

#include "Solm/Formula/Predicate/Primitive/Manipulator/Read.h"
#include "Solm/Formula/Predicate/Primitive/Manipulator/Created.h"
#include "Solm/Formula/Predicate/Primitive/Manipulator/Deleted.h"
#include "Solm/Formula/Predicate/Primitive/Manipulator/Updated.h"
