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

void Errors::fillNode(pugi::xml_node& n) {
    using namespace pugi;

    typedef vector<rqdql::Logger::Message> Msgs;
    Msgs v = rqdql::Logger::getInstance().getMessages();
    
    for (Msgs::const_iterator i = v.begin(); i != v.end(); ++i) {
        pugi::xml_node err = n.append_child();
        err.set_name("error");
        
        pugi::xml_node m = err.append_child();
        m.set_name("msg");
        m.append_child(pugi::node_pcdata).set_value((*i).getMessage().c_str());
        
        pugi::xml_node lines = err.append_child();
        lines.set_name("lines");
        for (vector<int>::const_iterator k = (*i).getLines().begin(); k != (*i).getLines().end(); ++k) {
            pugi::xml_node l = lines.append_child();
            l.set_name("line");
            l.append_child(pugi::node_pcdata).set_value((boost::format("%d") % *k).str().c_str());
        }
    }
}


