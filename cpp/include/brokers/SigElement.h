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

#ifndef __INCLUDE_SCOPE_BROKERS_SIGELEMENT_H
#define __INCLUDE_SCOPE_BROKERS_SIGELEMENT_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace brokers {

/**
 * Forward declarations
 */
class De;

/**
 * One element inside signature
 * @see rqdql.y
 */
class SigElement {
public:
    SigElement();
    void setInformal(const std::string&);
    bool hasInformal() const;
    const std::string getInformal() const;
    void setDe(const De&);
    const De& getDe() const;
    bool hasDe() const;
    void setVerb(const std::string&);
    const std::string getVerb() const;
    bool hasVerb() const;
    const std::string toFormalString() const; // like "${user}"
    const std::string toInformalString() const; // like "\"some\" ActorUser (the user)"
private:
    boost::shared_ptr<De> _de;
    std::string _informal;    
    std::string _verb;
};

typedef std::vector<SigElement> SigElements;

}

#endif
