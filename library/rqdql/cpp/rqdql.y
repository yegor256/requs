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

%{
    #include <vector>
    #include "../rqdql.tab.h"
    #include "rqdql.h"
    
    using rqdql::log;
    using namespace rqdql::scope;
    using std::vector;
%}

%union {
    char* name;
    vector<Statement> statements();
    Statement statement();
    vector<Action> actions();
    Action action();
};

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
%type <actions> actions
%type <action> action
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
%type <name> attributes

// Declaration of all known tokens
%token <name> INFORMAL
%token <name> ENTITY
%token <name> FUR
%token <name> QOS
%token <name> ACTOR
%token <name> UC
%token <name> WORD
%token <name> ACRONYM 
%token <name> TBD
%token <name> ATTRIBS
%token <name> INFINITIVE
%token <name> AKA

%token COLON SEMICOLON DOT COMMA
%token MEANS
%token SEE
%token AND OR
%token CAN
%token IF
%token OF
%token USING
%token THIS
%token PLURAL_MANY PLURAL_SOME PLURAL_ANY
%token OPEN_BRACE CLOSE_BRACE
%token IS_A INCLUDES PRODUCES

%nonassoc COMMA
%nonassoc AND
%nonassoc SEMICOLON
%right OF
%right COLON
%right INCLUDES
%right PRODUCES

%%

SRS:
    /* it can be empty */ |
    SRS DottedStatement;

DottedStatement:
    Statement DOT;

Statement:
    FurStatement { log("FUR statement processed"); } |
    EntityStatement { log("Entity statement processed"); } | 
    QosStatement { log("QOS statement processed"); } | 
    VerbStatement { log("Verb statement processed"); } | 
    SeeStatement 
    ;

FurStatement:
    lfur COLON actions |
    lfur COLON TBD |
    lfur error { lyyerror(@2, "colon expected after FUR"); } |
    lfur COLON error { lyyerror(@3, "actions expected after 'FUR:'"); } 
    ;
    
/* left FUR */
lfur:
    FUR |
    FUR ATTRIBS
    ;
    
actions:
    action { $$.erase(); $$.push_back($1); } |
    actions SEMICOLON action { $$.push_back($3); } 
    ;
    
action:
    ACTOR CAN verbs subjects { $$ = new Scope::Action(); } |
    ACTOR error { lyyerror(@2, "'can' missed after '%s'", $1); } |
    ACTOR CAN error { lyyerror(@3, "list of verbs not found after '%s can'", $1); } |
    ACTOR CAN verbs error { lyyerror(@4, "list of subjects missed after '%s can %s'", $1, $3); }
    ;
    
verbs:
    verb |
    verbs separator verb { $$ = rq.sprintf("%s, %s", $1, $3); }
    ;
    
verb:
    ACRONYM |
    WORD |
    WORD modifier
    ;
    
subjects:
    subject |
    subjects separator subject
    ;
    
separator:
    COMMA |
    AND |
    COMMA AND
    ;
    
subject:
    object |
    object modifier { $$ = rq.sprintf("%s %s", $1, $2); }
    ;
    
object:
    THIS { $$ = rq.sprintf("this"); } |
    ACTOR plural { $$ = rq.sprintf("%s", $1); } |
    ENTITY plural { $$ = rq.sprintf("%s", $1); } |
    attributes OF object { $$ = rq.sprintf("%s of %s", $1, $3); }
    ;
    
attributes:
    attribute |
    attributes separator attribute { $$ = rq.sprintf("%s, %s", $1, $3); }
    ;
    
attribute:
    words
    ;
    
words:
    WORD |
    words WORD { $$ = rq.sprintf("%s %s", $1, $2); }
    ;
    
plural:
    /* singular */ | PLURAL_MANY | PLURAL_SOME | PLURAL_ANY;

modifier:
    OPEN_BRACE predicates CLOSE_BRACE { $$ = rq.sprintf("%s", $2); }
    ;
    
predicates:
    predicate |
    predicates SEMICOLON predicate
    ;
    
predicate:
    lambda subjects { $$ = rq.sprintf("L %s", $2); } |
    lambda subjects verbs { $$ = rq.sprintf("L %s %s", $2, $3); }
    ;
    
lambda:
    IF |
    USING 
    ;
    
EntityStatement:
    lobject COLON INFORMAL |
    lobject IS_A object |
    lobject INCLUDES parts |
    lobject PRODUCES parts
    ;
    
lobject:
    ENTITY |
    ACTOR
    ;

/* e.g. "email; password; files" */
parts: 
    part |
    parts SEMICOLON part
    ;

/* e.g. "email: string text" */
part:
    attribute |
    attribute COLON INFORMAL |
    attribute INCLUDES parts SEMICOLON
    ;

/* QOS3.3: some text. */    
QosStatement:
    QOS COLON INFORMAL
    ;

/* email of ActorUser "to approve" means: some text... */
VerbStatement:
    INFINITIVE object MEANS COLON INFORMAL |
    INFINITIVE object AKA MEANS COLON INFORMAL 
    ;
    
/* See: R4.4, ActorUser, ... */
SeeStatement:
    SEE COLON entities
    ;
    
entities:
    entity |
    entities separator entity
    ;
    
entity: 
    FUR |
    UC |
    subject 
    ;

%%

// see global.cpp