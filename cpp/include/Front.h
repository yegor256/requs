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

#include <sstream>
#include <pugixml/pugixml.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/case_conv.hpp> // to_lower_copy()
#include "Analysts.h"
#include "Xml.h"

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
    void append(Xml::Node&);
    const string& getName() const { return name; }
protected:
    Reporter(const Params& p) : params(p) { /* it's private, use factory() instead */ };
    virtual void fill(Xml::Node&) = 0;
    template <typename T> T getParam(const string& n, const T&);
private:
    string name;
    Params params;
};

class Errors : public Reporter {
public:
    Errors(const Params& p) : Reporter(p) { /* that's it */ }
    void fill(Xml::Node&);
private:
    class Error {
    public:
        int line;
        string message;
        Error() : line(0), message("") { /* .. */ }
        Error(int l, const string& m) : line(l), message(m) { /* .. */ }
        bool operator< (const Error& e) const { return line < e.line; }
        bool operator== (const Error& e) const { return (line == e.line) && (message == e.message); }
    };
};
class Metrics : public Reporter {
public:
    Metrics(const Params& p) : Reporter(p) { /* that's it */ }
    void fill(Xml::Node&);
};
class Uml : public Reporter {
public:
    Uml(const Params& p) : Reporter(p) { /* that's it */ }
    void fill(Xml::Node&);
};
class Svg : public Reporter {
public:
    Svg(const Params& p) : Reporter(p) { /* that's it */ }
    void fill(Xml::Node&);
};
class Tc : public Reporter {
public:
    Tc(const Params& p) : Reporter(p) { /* that's it */ }
    void fill(Xml::Node&);
};
class Links : public Reporter {
public:
    Links(const Params& p) : Reporter(p) { /* that's it */ }
    void fill(Xml::Node&);
private:
    template<typename T> void addLocations(Xml::Node&, const string&) const;
};
    
class Front {
public:
    void require(const string&); // name of the report to require
    Xml::Document& getXml(); // get XML
    const string asXml(); // get XML as string
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
