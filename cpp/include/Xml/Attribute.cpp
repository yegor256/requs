/**
 *

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

#include "Xml/Attribute.h"

#include <string>
#include <boost/format.hpp>

void Xml::Attribute::operator=(const std::string& s) {
    set_value(s.c_str());
}
 
void Xml::Attribute::operator=(int i) {
    set_value((boost::format("%d") % i).str().c_str());
}
 