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
 */

#ifndef __INCLUDE_SCOPE_BROKERS_H
#define __INCLUDE_SCOPE_BROKERS_H

#include <vector>
#include <boost/algorithm/string/join.hpp>>
#include "Proxy.h"

namespace brokers {

class De { // data element
public:
    De() : name(""), explanation(0) { /* that's it */ }
    void setName(const string& n) { name = n; }
    const string getName() const { if (!hasName()) throw "no NAME in this DE"; return name; }
    bool hasName() const { return !name.empty(); }
    void setExplanation(proxy::Signature::Explanation* e) { explanation = e; }
    proxy::Signature::Explanation* getExplanation() const { if (!hasExplanation()) throw "no EXPLANATION here"; return explanation; }
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
    const string getInformal() const { if (!hasInformal()) throw "no INFORMAL here"; return informal; }
    void setDe(De* d) { de = d; }
    De* getDe() const { if (!hasDe()) throw "no DE here"; return de; }
    bool hasDe() const { return de; }
    void setVerb(const string& v) { verb = v; }
    const string getVerb() const { if (!hasVerb()) throw "no VERB here"; return verb; }
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
    proxy::Flow* getFlow() const { if (!hasFlow()) throw "no FLOW here"; return flow; }
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
    void setSignature(SigElements*);
    proxy::Signature* getSignature() const { if (!hasSignature()) throw "no signature here"; return signature; }
    bool hasSignature() const { return signature; }
    void setText(const string& t) { text = t; }
    const string getText() const { if (!hasText()) throw "no TEXT in this SignatureHolder"; return text; }
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
    //     txt = txt + getDe()->getExplanation()->toString();
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

void SignatureHolder::setSignature(SigElements* e) {
    using namespace proxy;
    Signature* s = new Signature();
    vector<string> texts; // full informal presentation of the signature
    vector<string> sigs; // formal signature string elements
    for (SigElements::const_iterator i = e->begin(); i != e->end(); ++i) {
        SigElement* se = *i;
        sigs.push_back(se->toFormalString());
        if (se->hasDe() && se->getDe()->hasName()) {
            s->explain(se->getDe()->getName(), se->getDe()->getExplanation());
        }
        texts.push_back(se->toInformalString());
    }
    s->setText(boost::algorithm::join(sigs, " "));
    setText(boost::algorithm::join(texts, " "));
    setSignature(s);
}

}

#endif