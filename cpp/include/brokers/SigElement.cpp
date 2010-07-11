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

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "brokers/SigElement.h"
#include "brokers/De.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

brokers::SigElement::SigElement() : _de(), _informal(), _verb() { 
    /* that's it */ 
}

void brokers::SigElement::setInformal(const std::string& s) { 
    _informal = s; 
}

bool brokers::SigElement::hasInformal() const { 
    return !_informal.empty(); 
}

const std::string brokers::SigElement::getInformal() const { 
    if (!hasInformal()) {
        throw rqdql::Exception(
            rqdql::_t("no INFORMAL here")
        ); 
    }
    return _informal; 
}

void brokers::SigElement::setDe(const brokers::De& d) { 
    _de = boost::shared_ptr<brokers::De>(new brokers::De(d)); 
}

const brokers::De& brokers::SigElement::getDe() const { 
    if (!hasDe()) {
        throw rqdql::Exception(
            rqdql::_t("no DE here")
        ); 
    }
    return *_de; 
}

bool brokers::SigElement::hasDe() const { 
    return _de; 
}

void brokers::SigElement::setVerb(const std::string& v) { 
    _verb = v; 
}

const std::string brokers::SigElement::getVerb() const { 
    if (!hasVerb()) {
        throw rqdql::Exception(
            rqdql::_t("no VERB here")
        ); 
    }
    return _verb; 
}

bool brokers::SigElement::hasVerb() const { 
    return !_verb.empty(); 
}

const std::string brokers::SigElement::toInformalString() const {
    std::string txt;
    if (hasInformal()) {
        txt = txt + getInformal() + " ";
    }
    if (hasDe()) {
        if (getDe().hasExplanation()) {
            txt = txt + (std::string)(getDe().getExplanation());
        } else {
            txt = txt + "the " + getDe().getName();
        }
    } else {
        txt = txt + getVerb();
    }
    return txt;
}

const std::string brokers::SigElement::toFormalString() const {
    if (hasDe()) {
        return "{" + (getDe().hasName() ? getDe().getName() : "?") + "}";
    } else {
        return getVerb();
    }
}

