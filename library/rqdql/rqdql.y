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

// This directive tells BISON to use C++ framework, instead of
// standard C.
//%language "C++"

// This directives instructs BISON to put code to handle locations
// inside the parser class.
//%locations

// The class will be created by BISON in "yy" namespace and will
// have name "Parser". It will be accessible as "yy::Parser".
// %defines directive tells BISON that our yy::Parser shall be used
// instead of a default class.
//%defines
//%define namespace "yy"
//%define parser_class_name "Parser"

%union {
    char* name;
};

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
//%type <name> verb

// Declaration of all known tokens
%token <name> ENTITY

// %{
//     extern int yylex(
//         yy::RqdqlParser::semantic_type *yylval,
//         yy::RqdqlParser::location_type* yylloc
//     );
// %}

// %initial-action {
//     // Filename for locations here
//     @$.begin.filename = @$.end.filename = new std::string("stdin");
// }

%{
    #include <scope.hh>
    Scope scope;
%}

%%

statement:
    ENTITY { scope.add($1); }
    ;

%%

main()
{
    cout << "rqdql v0.1\n";
    return yyparse();
}

void yyerror(const char *error)
{
    cout << error << endl;
}