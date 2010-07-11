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

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Proxy/Signature.h"
#include "brokers/SigElement.h"

namespace brokers {

/**
 * Forward declarations
 */
// class SigElements;

/**
 * Holder of a signature
 * @see rqdql.y
 */
class SignatureHolder {
public:
    SignatureHolder();
    void set(const proxy::Signature&);
    void set(const SigElements&);
    const proxy::Signature& getSignature() const;
    bool hasSignature() const;
    void set(const std::string&);
    const std::string getText() const;
    bool hasText() const;
private:
    boost::shared_ptr<proxy::Signature> _signature;
    std::string _text;
};

}

#endif
