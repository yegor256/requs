%{
/**
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

%option noyywrap

%{
    # include <cstdlib>
    # include "rqdql.tab.hh"

    #define YY_DECL int yylex( \
        yy::cppcalc::semantic_type *yylval, \
        yy::cppcalc::location_type *yylloc)

    // make location include the current token
    # define YY_USER_ACTION yylloc->columns(yyleng);

    typedef yy::Parser::token token;
%}

%%

%{
    // start where previous token ended
    yylloc->step ();
%}

[a-zA-Z]+ { yylval->name = strdup(yytext); return token::ENTITY; }

%%
