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

%union {
    char* name;
};

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
//%type <name> verb

// Declaration of all known tokens
%token <name> ENTITY
%token <name> ENTITY_FUR
%token <name> ENTITY_ACTOR
%token COLON

%{
    extern void yyerror(const char *error);
    extern int yylex(void);
%}

%{
    #include <iostream>
        using namespace std;

    #include "Scope.h"
    Scope scope;
%}

%%

Statement:
    FurStatement | EntityStatement;

FurStatement:
    ENTITY_FUR COLON { scope.add($1); cout << "FUR: " << $1; }
    ;
    
EntityStatement:
    ENTITY COLON
    ;
    
%%

void yyerror(const char *error)
{
    cerr << error << endl;
}
    
main()
{
    cout << "rqdql v0.1\n";
    int result = yyparse();
    
    // error in parsing?
    if (!result) {
        cerr << "parsing error\n";
        return result;
    }
    
    return 0;
}

