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

#ifndef __INCLUDE_SCOPE_FRONT_H
#define __INCLUDE_SCOPE_FRONT_H

#include <sstream>
#include <pugixml/pugixml.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()

namespace front {
    
class Reporter;
    class Errors;
    class Metrics;
    class Uml;
    class Svg;
    class Tc;
    class Links;

class Reporter {
public:
    typedef map<string, string> Params;
    static Reporter* factory(const string&, const Params&);
    void appendNode(pugi::xml_node&);
    const string& getName() const { return name; }
protected:
    Reporter(const Params& p) : params(p) { /* it's private, use factory() instead */ };
    virtual void fillNode(pugi::xml_node&) = 0;
private:
    string name;
    Params params;
};

class Errors : public Reporter {
public:
    Errors(const Params& p) : Reporter(p) { /* that's it */ }
    void fillNode(pugi::xml_node&);
};
class Metrics : public Reporter {
public:
    Metrics(const Params& p) : Reporter(p) { /* that's it */ }
    void fillNode(pugi::xml_node&);
};
class Uml : public Reporter {
public:
    Uml(const Params& p) : Reporter(p) { /* that's it */ }
    void fillNode(pugi::xml_node&);
};
class Svg : public Reporter {
public:
    Svg(const Params& p) : Reporter(p) { /* that's it */ }
    void fillNode(pugi::xml_node&);
};
class Tc : public Reporter {
public:
    Tc(const Params& p) : Reporter(p) { /* that's it */ }
    void fillNode(pugi::xml_node&);
};
class Links : public Reporter {
public:
    Links(const Params& p) : Reporter(p) { /* that's it */ }
    void fillNode(pugi::xml_node&);
};
    
class Front {
public:
    static Front& getInstance(); // singleton pattern
    void require(const string&); // name of the report to require
    pugi::xml_document& getXml(); // get XML
    string asXml(); // get XML as string
private:
    vector<Reporter*> reporters;
};

#include "Front/FrontImpl.h"
#include "Front/Reporter.h"
#include "Front/Errors.h"
#include "Front/Metrics.h"
#include "Front/Links.h"
#include "Front/Uml.h"
#include "Front/Svg.h"
#include "Front/Tc.h"

}

#endif
