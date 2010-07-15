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
    #include <vector>
    #include <boost/format.hpp>
    #include "Solm/Term.h"
%}

%union {
    std::string* p;
}

%name-prefix="term"

%token DOT
%token <p> OPEN_BRACE CLOSE_BRACE
%token <p> OPERATOR
%token <p> NUMBER
%token <p> VARIABLE
%token <p> OBJECT
%token <p> TEXT

%left OPERATOR
%nonassoc DOT

%%

sentence:
    term DOT
    ;

term: 
    NUMBER
    |
    VARIABLE
    |
    OBJECT
    |
    TEXT
    |
    infixed
    |
    prefixed
    ;
    
infixed:
    term OPERATOR term
    ;
    
prefixed:
    OBJECT OPEN_BRACE term CLOSE_BRACE
    ;
    
%%

// see Solm/Term.cpp