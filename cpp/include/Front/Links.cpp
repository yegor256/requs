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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Front.h
 */

#include <string>
#include <vector>
#include <map>
#include "rqdql.h"
#include "Logger.h"
#include "Front/Links.h"
#include "Xml/Node.h"
#include "Xml/Attribute.h"
#include "Proxy.h"
#include "Proxy/Type.h"
#include "Proxy/UseCase.h"

void front::Links::fill(Xml::Node& n) {
    using namespace std;
    
    typedef vector<rqdql::Logger::Link> Links;
    Links v = rqdql::get<rqdql::Logger>().getLinks();
    
    map<int, int> links;
    for (Links::const_iterator i = v.begin(); i != v.end(); ++i) {
        for (vector<int>::const_iterator k = (*i).getLeftLines().begin(); k != (*i).getLeftLines().end(); ++k) {
            for (vector<int>::const_iterator j = (*i).getRightLines().begin(); j != (*i).getRightLines().end(); ++j) {
                links[*k] = *j;
            }
        }
    }

    for (map<int, int>::const_iterator i = links.begin(); i != links.end(); ++i) {
        Xml::Node x = n / "crosses" + "link";
        x / "left" = (*i).first;
        x / "right" = (*i).second;
    }
    
    addLocations<proxy::Type>(n, "type");
    addLocations<proxy::UseCase>(n, "uc");
}

/**
 * Add locations of objects, found in the scope
 */
template<typename T> void front::Links::addLocations(Xml::Node& n, const std::string& label) const {
    using namespace std;
     
    vector<string> types = rqdql::get<proxy::Proxy>().getNames<T>();
    for (vector<string>::const_iterator i = types.begin(); i != types.end(); ++i) {
        vector<int> lines = rqdql::get<rqdql::Logger>().getLinesFor(rqdql::get<Proxy>().get<T>(*i));
        if (lines.empty()) {
            continue;
        }

        // leave only unique lines
        lines.resize(unique(lines.begin(), lines.end()) - lines.begin());
        
        Xml::Node t = n / "locations" + "loc";
        t["name"] = *i;
        t["what"] = label;
        for (vector<int>::const_iterator j = lines.begin(); j != lines.end(); ++j) {
            t + "line" = *j;
        }
    }
}
