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

PugiNodeWrapper operator/(pugi::xml_node n, const string& s) {
    pugi::xml_node x = n.child(s.c_str());
    if (x.empty()) {
        x = n.append_child();
        x.set_name(s.c_str());
    }
    return PugiNodeWrapper(x);
}

void PugiAttributeWrapper::operator=(const string& s) {
    set_value(s.c_str());
    // return PugiNodeWrapper(parent());
}
 
void PugiAttributeWrapper::operator=(int i) {
    set_value((boost::format("%d") % i).str().c_str());
    // return PugiNodeWrapper(parent());
}
 
PugiNodeWrapper PugiNodeWrapper::operator+(const string& s) {
    pugi::xml_node n = append_child();
    n.set_name(s.c_str());
    return PugiNodeWrapper(n);
}

PugiNodeWrapper& PugiNodeWrapper::operator=(const string& s) {
    append_child(pugi::node_pcdata).set_value(s.c_str());
    return *this;
}

PugiNodeWrapper& PugiNodeWrapper::operator=(double d) {
    append_child(pugi::node_pcdata).set_value(
        (boost::format("%0.3f") % d).str().c_str()
    );
    return *this;
}

PugiNodeWrapper& PugiNodeWrapper::operator=(int i) {
    append_child(pugi::node_pcdata).set_value(
        (boost::format("%d") % i).str().c_str()
    );
    return *this;
}

PugiAttributeWrapper PugiNodeWrapper::operator[](const string& s) {
    pugi::xml_attribute a = append_attribute(s.c_str());
    return PugiAttributeWrapper(a);
}
 
