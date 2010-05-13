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
    const string getName() const { return name; }
    bool hasName() const { return !name.empty(); }
    void setExplanation(proxy::Signature::Explanation* e) { explanation = e; }
    proxy::Signature::Explanation* getExplanation() const { return explanation; }
    bool hasExplanation() const { return explanation; }
    const string toString() const;
private:
    string name;
    proxy::Signature::Explanation* explanation;
};

class SigElement {
public:
    SigElement() : de(0), informal(""), verb("") { /* that's it */ }
    void setInformal(const string& s) { informal = s; }
    bool hasInformal() const { return !informal.empty(); }
    const string getInformal() const { return informal; }
    void setDe(De* d) { de = d; }
    De* getDe() const { return de; }
    bool hasDe() const { return de; }
    void setVerb(const string& v) { verb = v; }
    const string getVerb() const { return verb; }
    bool hasVerb() const { return !verb.empty(); }
    const string toString() const;
private:
    De* de;
    string informal;    
    string verb;
};

typedef vector<SigElement*> SigElements;

class FlowHolder {
public:
    void setFlow(proxy::Flow* f) { flow = f; }
    proxy::Flow* getFlow() const { return flow; }
    void setId(int i) { id = i; }
    int getId() const { return id; }
private:
    proxy::Flow* flow;
    int id;
};

class SignatureHolder {
public:
    void setSignature(proxy::Signature* s) { signature = s; }
    void setSignature(SigElements*);
    proxy::Signature* getSignature() const { return signature; }
    void setText(const string& t) { text = t; }
    const string getText() const { return text; }
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

const string De::toString() const {
    string s = "${";
    if (!name.empty()) {
        s = s + "oops"; 
        // why so? endless cycle here... can't understand...
        // s = s + name;
    } else {
        s = s + "noname";
    }
    return s + "}";
}

const string SigElement::toString() const {
    vector<string> sectors;
    if (hasInformal()) {
        sectors.push_back(getInformal());
    }
    if (hasDe()) {
        sectors.push_back(getDe()->toString());
    }
    if (hasVerb()) {
        sectors.push_back(getVerb());
    }
    return boost::algorithm::join(sectors, " ");
}

void SignatureHolder::setSignature(SigElements* e) {
    using namespace proxy;
    Signature* s = new Signature();
    vector<string> texts;
    for (SigElements::const_iterator i = e->begin(); i != e->end(); ++i) {
        texts.push_back((*i)->toString());
        if ((*i)->hasDe()) {
            s->explain((*i)->getDe()->getName(), (*i)->getDe()->getExplanation());
        }
    }
    s->setText(boost::algorithm::join(texts, " "));
    setText(boost::algorithm::join(texts, " "));
    setSignature(s);
}

}

#endif