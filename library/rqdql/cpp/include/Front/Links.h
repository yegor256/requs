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
    using namespace pugi;

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

    for (map<int, int>::const_iterator i = links.begin(); i != links.end(); ++i) {
        pugi::xml_node l = n.append_child();
        l.set_name("link");
        l.append_child().set_name("left");
        l.child("left").append_child(pugi::node_pcdata).set_value((boost::format("%d") % (*i).first).str().c_str());
        l.append_child().set_name("right");
        l.child("right").append_child(pugi::node_pcdata).set_value((boost::format("%d") % (*i).second).str().c_str());
    }
}


