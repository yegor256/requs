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
#include "Scanner.h"
#include "Scanner/supplementary.h"
#include "Scanner/rqdql.y.c"
#include "Scanner/rqdql.l.c"

void rqdql::Scanner::scan(const std::string& s) {
    yylineno = 1; // reset line number to 1
    yy_switch_to_buffer(yy_scan_string(s.c_str()));
    yyparse();
}
