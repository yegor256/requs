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

// we should track locations of errors, in YYLTYPE, see lyyerror()
%locations

%union {
    char* name;
};

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
%type <name> actions
%type <name> action
%type <name> verbs
%type <name> verb
%type <name> predicates
%type <name> predicate
%type <name> words
%type <name> modifier
%type <name> subjects
%type <name> subject
%type <name> object
%type <name> attribute
%type <name> lambda

// Declaration of all known tokens
%token <name> ENTITY
%token <name> ENTITY_FUR
%token <name> ENTITY_ACTOR
%token <name> COLON SEMICOLON DOT COMMA
%token <name> AND CAN OF
%token <name> IF
%token <name> USING
%token <name> THIS
%token <name> WORD
%token <name> PLURAL_MANY PLURAL_SOME PLURAL_ANY
%token <name> OPEN_BRACE CLOSE_BRACE

%{
    #include "rqdql.h"
    #include "Scope.h"
    Scope scope;
%}

%%

SRS:
    /* it can be empty */ |
    SRS Statement;

Statement:
    FurStatement { cout << "FUR statement processed\n"; } |
    EntityStatement |
    error { lyyerror(@1, "statement expected but missed"); };

FurStatement:
    ENTITY_FUR COLON actions DOT |
    ENTITY_FUR error { lyyerror(@2, "colon expected after %s", $1); } |
    ENTITY_FUR COLON error { lyyerror(@3, "actions expected after %s:", $1); } |
    ENTITY_FUR COLON actions error { lyyerror(@4, "trailing dot missed after %s: %s", $1, $3); }
    ;
    
actions:
    action |
    actions SEMICOLON action
    ;
    
action:
    ENTITY_ACTOR CAN verbs subjects |
    ENTITY_ACTOR error { lyyerror(@2, "'can' missed after '%s'", $1); } |
    ENTITY_ACTOR CAN error { lyyerror(@3, "list of verbs not found after '%s %s'", $1, $2); } |
    ENTITY_ACTOR CAN verbs error { lyyerror(@4, "list of subjects missed after '%s can %s'", $1, $3); }
    ;
    
verbs:
    verb |
    verb COMMA verbs { $$ = rqdql::sprintf("%s%s %s", $1, $2, $3); } |
    verb AND verbs { $$ = rqdql::sprintf("%s %s %s", $1, $2, $3); }  |
    verb COMMA AND verbs { $$ = rqdql::sprintf("%s%s %s %s", $1, $2, $3, $4); } 
    ;
    
verb:
    WORD |
    WORD modifier
    ;
    
subjects:
    subject |
    subject COMMA subjects |
    subject AND subjects |
    subject COMMA AND subjects
    ;
    
subject:
    object |
    object modifier { $$ = rqdql::sprintf("%s %s", $1, $2); } |
    object error { lyyerror(@1, "invalid modifier after '%s'", $1); }
    ;
    
object:
    THIS |
    ENTITY plural |
    attribute OF object { $$ = rqdql::sprintf("%s %s %s", $1, $2, $3); }
    ;
    
attribute:
    words |
    words modifier { $$ = rqdql::sprintf("%s %s", $1, $2); }
    ;
    
words:
    WORD |
    words WORD { $$ = rqdql::sprintf("%s %s", $1, $2); }
    ;
    
plural:
    /* singular */ | PLURAL_MANY | PLURAL_SOME | PLURAL_ANY;

modifier:
    OPEN_BRACE predicates CLOSE_BRACE
    ;
    
predicates:
    predicate |
    predicates SEMICOLON predicate
    ;
    
predicate:
    lambda subjects { $$ = rqdql::sprintf("%s %s", $1, $2); } |
    lambda subjects verbs { $$ = rqdql::sprintf("%s %s %s", $1, $2, $3); }
    ;
    
lambda:
    IF |
    USING
    ;
    
EntityStatement:
    ENTITY COLON
    ;
    
%%

// see global.cpp