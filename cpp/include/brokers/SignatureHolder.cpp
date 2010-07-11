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
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/join.hpp>
#include "Proxy/Signature.h"
#include "brokers/SignatureHolder.h"
#include "brokers/SigElement.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

brokers::SignatureHolder::SignatureHolder() : _signature(), _text("") { 
    /* that's it */ 
}

void brokers::SignatureHolder::set(const boost::shared_ptr<proxy::Signature>& s) { 
    _signature = s; 
}

boost::shared_ptr<proxy::Signature>& brokers::SignatureHolder::getSignature() const { 
    if (!hasSignature()) {
        throw rqdql::Exception(
            rqdql::_t("no signature here")
        ); 
    }
    return _signature; 
}

bool brokers::SignatureHolder::hasSignature() const { 
    return _signature; 
}

void brokers::SignatureHolder::set(const std::string& t) { 
    text = t; 
}

const std::string brokers::SignatureHolder::getText() const { 
    if (!hasText()) {
        throw rqdql::Exception(
            rqdql::_t("no TEXT in this SignatureHolder")
        ); 
    }
    return _text; 
}

bool brokers::SignatureHolder::hasText() const { 
    return !_text.empty(); 
}

void brokers::SignatureHolder::set(const brokers::SigElements* e) {
    using namespace proxy;
    Signature* s = new Signature();
    vector<string> texts; // full informal presentation of the signature
    vector<string> sigs; // formal signature string elements
    
    map<string, proxy::Signature::Explanation*> exps;
    
    for (SigElements::const_iterator i = e->begin(); i != e->end(); ++i) {
        SigElement* se = *i;
        sigs.push_back(se->toFormalString());
        if (se->hasDe() && se->getDe()->hasName() && se->getDe()->hasExplanation()) {
            exps[se->getDe()->getName()] = se->getDe()->getExplanation();
        }
        texts.push_back(se->toInformalString());
    }
    s->setText(boost::algorithm::join(sigs, " ")); // formal signature
    setText(boost::algorithm::join(texts, " ")); // informal string
    setSignature(s);

    // now explain it
    for (map<string, proxy::Signature::Explanation*>::const_iterator i = exps.begin(); i != exps.end(); ++i) {
        s->explain((*i).first, (*i).second);
    }
}
