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
 *
 * This file is included ONLY from Front.h
 */

void Links::fill(Xml::Node& n) {
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
template<typename T> void Links::addLocations(Xml::Node& n, const string& label) const {
    vector<string> types = rqdql::get<Proxy>().getNames<T>();
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
