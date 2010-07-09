/**
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

#ifndef __INCLUDE_SCOPE_FRONT_H
#define __INCLUDE_SCOPE_FRONT_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "Xml/Document.h"

namespace front {
    
/**
 * Forward declaration
 */
class Reporter;
    
/**
 * Front-end of all reporters
 */
class Front {

public:

    /**
     * Require this report to appear in final XML
     */
    void require(const std::string&);

    /**
     * Get XML as string
     */
    const std::string asXml();

private:

    /**
     * Collection of reporters
     */
    std::vector<boost::shared_ptr<Reporter> > _reporters;

};

}

#endif
