/**
 *

 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

const string SigElement::toInformalString() const {
    string txt;
    if (hasInformal()) {
        txt = txt + getInformal() + " ";
    }
    if (hasDe()) {
        if (getDe()->hasExplanation()) {
            txt = txt + getDe()->getExplanation()->toString();
        } else {
            txt = txt + "the " + getDe()->getName();
        }
    } else {
        txt = txt + getVerb();
    }
    return txt;
}

const string SigElement::toFormalString() const {
    if (hasDe()) {
        return "{" + (getDe()->hasName() ? getDe()->getName() : "?") + "}";
    } else {
        return getVerb();
    }
}

