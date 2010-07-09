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

#ifndef __INCLUDE_SCOPE_FRONT_REPORTER_H
#define __INCLUDE_SCOPE_FRONT_REPORTER_H

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "Xml/Node.h"

namespace front {
    
/**
 * Abstract reporter class
 */
class Reporter {

public:

    /**
     * List of parameters for this reporter
     */
    typedef std::map<std::string, std::string> Params;

    /**
     * Factory pattern, to create a new reporter class by its name
     * and a collection of params
     */
    static boost::shared_ptr<Reporter> factory(const std::string&, const Params&);
    
    /**
     * Append this reporter to the XML node provided
     * @see Front::asXml()
     */
    void append(Xml::Node&) const;
    
protected:

    /**
     * Constructor to be used from factory() method only
     */
    Reporter(const Params& p) : _params(p) { /* it's private, use factory() instead */ };
    
    /**
     * Pure virtual method, that is going to fill the provided
     * XML node with a new element <report>, which will give all
     * details required.
     */
    virtual void fill(Xml::Node&) const = 0;
    
    /**
     * Get one parameter by its name and type. Second param is the
     * default value of param, which will be returned if nothing
     * found. For example:
     * getParam<string>("filename", "/dev/null")
     */
    template <typename T> T getParam(const std::string& n, const T&) const;
    
private:

    /**
     * Name of the report
     */
    std::string _name;

    /**
     * List of params provided
     */
    Params _params;

};

}

#endif
