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

#include <string>
#include <boost/format.hpp>
#include "Xml/Attribute.h"

namespace Xml {
template<> void Attribute::operator=(const std::string& s) {
    set_value(s.c_str());
}
}
 
namespace Xml {
template<> void Attribute::operator=(const int& i) {
    set_value((boost::format("%d") % i).str().c_str());
}
}
 