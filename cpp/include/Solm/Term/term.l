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

%{
	#include <string>
	#include <boost/format.hpp>
    #include "Solm/Term.h"
	using boost::format;
	using std::string;
%}

%option prefix="term"
%option noyywrap

SPACE ([ \t\r\n]+)
TAIL ([a-zA-Z_0-9]+)
VARIABLE ([A-Z]({TAIL})*)
OBJECT ([a-z_]({TAIL})*)
NUMBER ([\-\+]?[0-9]+(\.[0-9]+)*)
TEXT ('.*')
OPERATOR ([,:/\\\*\-\?\+\$\&<>=]+|"is")

%%

	/* find punctuation */
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"." { return DOT; }

    /* find entities */
{OPERATOR} { termlval.p = new string(termtext); return OPERATOR; }
{OBJECT} { termlval.p = new string(termtext); return OBJECT; }
{VARIABLE} { termlval.p = new string(termtext); return VARIABLE; }
{NUMBER} { termlval.p = new string(termtext); return NUMBER; }
{TEXT} { termlval.p = new string(termtext); return TEXT; }

{SPACE} { /* ignore spaces */ }
. { termerror("unknown symbol"); }

%%
