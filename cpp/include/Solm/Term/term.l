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
	#include <boost/format.hpp>
    #include <vector>
    #include "Solm/Term.h"
	using boost::format;
%}

%option prefix="term"
%option noyywrap

SPACE ([ \t\r\n]+)
ATOM ([0-9]+(\.[0-9]+)*)

%%

    /* find entities */
{ATOM} { yylval.str = yytext); return ATOM; }
{UC} { yySet(yylval.name, yytext); log(format("UC: '%s'") % yytext); return UC; }
{CAMEL} { yySet(yylval.name, yytext); log(format("CAMEL: '%s'") % yytext); return CAMEL; }

. { yyerror("Unknown symbol \"%c\"", yytext[0]); }

%%
