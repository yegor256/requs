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

#ifndef __INCLUDE_SCOPE_BROKERS_SIGNATUREHOLDER_H
#define __INCLUDE_SCOPE_BROKERS_SIGNATUREHOLDER_H

#include <vector>
#include <boost/algorithm/string/join.hpp>
#include "Proxy.h"

namespace brokers {

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

}

#endif
