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

void Links::fillNode(pugi::xml_node& n) {
    typedef vector<rqdql::Logger::Link> Links;
    Links v = rqdql::Logger::getInstance().getLinks();
    
    map<int, int> links;
    for (Links::const_iterator i = v.begin(); i != v.end(); ++i) {
        for (vector<int>::const_iterator k = (*i).getLeftLines().begin(); k != (*i).getLeftLines().end(); ++k) {
            for (vector<int>::const_iterator j = (*i).getRightLines().begin(); j != (*i).getRightLines().end(); ++j) {
                links[*k] = *j;
            }
        }
    }

    // pugi::xml_node x = n.append_child();
    // x.set_name("crosses");
    for (map<int, int>::const_iterator i = links.begin(); i != links.end(); ++i) {
        ((n / "crosses" + "link") / "left" = (*i).first) / "right" = (*i).second;
    }

    /**
     * @todo Totally ineffective implementation now!!
     */

    vector<string> types = proxy::Proxy::getInstance().getNames<proxy::Type>();
    for (vector<string>::const_iterator i = types.begin(); i != types.end(); ++i) {
        vector<int> lines = rqdql::Logger::getInstance().getLinesFor(proxy::Proxy::getInstance().get<proxy::Type>(*i));
        if (lines.empty()) {
            continue;
        }

        PugiNodeWrapper t = n / "locations" + "loc";
        t["name"] = *i;
        t["what"] = "type";
        for (vector<int>::const_iterator j = lines.begin(); j != lines.end(); ++j) {
            t + "line" = *j;
        }
    }

    vector<string> useCases = proxy::Proxy::getInstance().getNames<proxy::UseCase>();
    for (vector<string>::const_iterator i = useCases.begin(); i != useCases.end(); ++i) {
        vector<int> lines = rqdql::Logger::getInstance().getLinesFor(proxy::Proxy::getInstance().get<proxy::UseCase>(*i));
        if (lines.empty()) {
            continue;
        }

        PugiNodeWrapper t = n / "locations" + "loc";
        t["name"] = *i;
        t["what"] = "uc";
        for (vector<int>::const_iterator j = lines.begin(); j != lines.end(); ++j) {
            t + "line" = *j;
        }
    }
}


