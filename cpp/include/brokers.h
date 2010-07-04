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

#ifndef __INCLUDE_SCOPE_BROKERS_H
#define __INCLUDE_SCOPE_BROKERS_H

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

namespace brokers {

class De { // data element
public:
    De() : name(""), explanation(0) { /* that's it */ }
    void setName(const string& n) { name = n; }
    const string getName() const { if (!hasName()) throw rqdql::Exception(rqdql::_t("no NAME in this DE")); return name; }
    bool hasName() const { return !name.empty(); }
    void setExplanation(proxy::Signature::Explanation* e) { explanation = e; }
    proxy::Signature::Explanation* getExplanation() const { if (!hasExplanation()) throw rqdql::Exception(rqdql::_t("no EXPLANATION here")); return explanation; }
    bool hasExplanation() const { return explanation; }
private:
    string name;
    proxy::Signature::Explanation* explanation;
};

class SigElement {
public:
    SigElement() : de(0), informal(""), verb("") { /* that's it */ }
    void setInformal(const string& s) { informal = s; }
    bool hasInformal() const { return !informal.empty(); }
    const string getInformal() const { if (!hasInformal()) throw rqdql::Exception(rqdql::_t("no INFORMAL here")); return informal; }
    void setDe(De* d) { de = d; }
    De* getDe() const { if (!hasDe()) throw rqdql::Exception(rqdql::_t("no DE here")); return de; }
    bool hasDe() const { return de; }
    void setVerb(const string& v) { verb = v; }
    const string getVerb() const { if (!hasVerb()) throw rqdql::Exception(rqdql::_t("no VERB here")); return verb; }
    bool hasVerb() const { return !verb.empty(); }
    const string toFormalString() const; // like "${user}"
    const string toInformalString() const; // like "\"some\" ActorUser (the user)"
private:
    De* de;
    string informal;    
    string verb;
};

typedef vector<SigElement*> SigElements;

class FlowHolder {
public:
    FlowHolder() : flow(0), id(0) { /* that's it */ }
    void setFlow(proxy::Flow* f) { flow = f; }
    bool hasFlow() const { return flow; }
    proxy::Flow* getFlow() const { if (!hasFlow()) throw rqdql::Exception(rqdql::_t("no FLOW here")); return flow; }
    void setId(int i) { id = i; }
    int getId() const { return id; }
private:
    proxy::Flow* flow;
    int id;
};

class SignatureHolder {
public:
    SignatureHolder() : signature(0), text("") { /* that's it */ }
    void setSignature(proxy::Signature* s) { signature = s; }
    void setSignature(const SigElements*);
    proxy::Signature* getSignature() const { if (!hasSignature()) throw rqdql::Exception(rqdql::_t("no signature here")); return signature; }
    bool hasSignature() const { return signature; }
    void setText(const string& t) { text = t; }
    const string getText() const { if (!hasText()) throw rqdql::Exception(rqdql::_t("no TEXT in this SignatureHolder")); return text; }
    bool hasText() const { return !text.empty(); }
private:
    proxy::Signature* signature;
    string text;
};

class AltPair {
public:
    AltPair(int i, char l) : num(i), letter(l) { /* that's it */ }
    void setNum(int i) { num = i; }
    int getNum() const { return num; }
    void setLetter(char l) { letter = l; }
    char getLetter() { return letter; }
private:
    int num; // -1 means STAR
    char letter;
};

typedef vector<AltPair*> AltPairs;

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

void SignatureHolder::setSignature(const SigElements* e) {
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

}

#endif
