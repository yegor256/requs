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
 * @version $Id$
 */

#include <vector>
#include <string>
#include "boost/regex.hpp"
#include "pugixml/pugixml.hpp"
#include "boost/format.hpp"
#include "funcs.h"
#include "rqdql.h"
#include "UseCase.h"

// pugi::xml_node rqdql::scope::Statement::findById(const pugi::xml_node& root, const std::string& id) {
//     return root.select_single_node((boost::format("//*[id='%s']") % id).str().c_str()).node();
// }
// 
// void rqdql::scope::Statement::setStartLineNo(int lineNo) {
//     this->_startLineNo = lineNo;
// }
// 
// void rqdql::scope::Statement::setEndLineNo(int lineNo) {
//     this->_endLineNo = lineNo;
// }
// 
// rqdql::scope::Statement::LeftName::LeftName(const std::string& name, const std::string& attribs) : _name(name), _attribs() {
//     using namespace std;
//     explode(
//         ",", 
//         boost::regex_replace(
//             attribs,
//             boost::regex("^\\[|\\]$"), // kill leading and trailing brackets
//             ""
//         ), 
//         this->_attribs
//     );
//     for(vector<string>::iterator i = this->_attribs.begin(); i != this->_attribs.end(); ++i) {
//         trim(*i);
//     }
// }
