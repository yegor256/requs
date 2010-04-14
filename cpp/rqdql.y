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
    #include "rqdql.h"
	using boost::format;    
    using rqdql::log;
%}

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
// %type <statements> SRS

// Declaration of all known tokens
%token <name> INFORMAL
%token <name> CLASS
%token <name> QOS
%token <name> ACTOR
%token <name> UC
%token <name> WORD

%token COLON SEMICOLON DOT COMMA
%token AND OR
%token IF
%token THE
%token OF
%token THIS
%token PLURAL_MANY PLURAL_SOME PLURAL_ANY
%token OPEN_BRACE CLOSE_BRACE
%token IS_A INCLUDES

%nonassoc COMMA
%nonassoc AND
%nonassoc SEMICOLON
%right OF
%right COLON
%right INCLUDES

%%

SRS:
    /* it can be empty */ |
    SRS Statement { } |
    SRS error { lyyerror(@2, "statement ignored"); };

Statement:
    InvariantDeclaration | 
    SlotsDeclaration | 
    UseCaseDefinition | 
    UseCaseAlternativeFlow
    ;

InvariantDeclaration:
    class IS_A INFORMAL {  } |
    class IS_A invariant {  } |
    ;
    
/* left FUR */
class:
    FUR { yySave($$, new Statement::LeftName(*$1, "")); } |
    FUR ATTRIBS { yySave($$, new Statement::LeftName(*$1, *$2)); }
    ;
    
actions:
    action { yyAppend($$, $1); } |
    actions SEMICOLON action { yyConcat($$, $1, $3); } 
    ;
    
action:
    ACTOR CAN verbs subjects {  } |
    ACTOR error { lyyerror(@2, "'can' missed after '%s'", $1); } |
    ACTOR CAN error { lyyerror(@3, "list of verbs not found after '%s can'", $1); } |
    ACTOR CAN verbs error { lyyerror(@4, "list of subjects missed after '%s can %s'", $1, $3); }
    ;
    
verbs:
    verb |
    verbs separator verb { yySet($$, format("%s, %s") % $1 % $3); }
    ;
    
verb:
    ACRONYM |
    WORD |
    WORD modifier
    ;
    
subjects:
    subject |
    subjects separator subject { /*yyConcat($$, $1, $3);*/ }
    ;
    
separator:
    COMMA |
    AND |
    COMMA AND
    ;
    
subject:
    object |
    object modifier { /* to add modifier to the object */ }
    ;
    
object:
    THIS
        {
            yyAppend($$, new Object());
        } |
    ACTOR plural
        { 
            Object* obj = new Object((format("%s") % $1).str());
            obj->setPlurality($2);
            obj->addTag("actor");
            yyAppend($$, obj);
        } |
    ENTITY plural
        {
            Object* obj = new Object((format("%s") % $1).str());
            obj->setPlurality($2);
            yyAppend($$, obj);
        } |
    attributes OF object
        { 
            // set parent for every object
            //$$->setParent($3); 
            // add them all to collection
            $$ = $1; 
        }
    ;
    
attributes:
    attribute { yyAppend($$, $1); } |
    attributes separator attribute { yyConcat($$, $1, $3); }
    ;
    
attribute:
    words { yySave($$, new Object(*$1)); }
    ;
    
words:
    WORD |
    words WORD { yySet($$, format("%s %s") % $1 % $2); }
    ;
    
plural:
    /* singular */ { $$ = Object::SINGULAR; } |
    PLURAL_MANY { $$ = Object::MANY; } | 
    PLURAL_SOME { $$ = Object::SOME; } |
    PLURAL_ANY { $$ = Object::ANY; } 
    ;

modifier:
    OPEN_BRACE predicates CLOSE_BRACE { yySet($$, format("%s") % $2); }
    ;
    
predicates:
    predicate |
    predicates SEMICOLON predicate
    ;
    
predicate:
    lambda subjects { yySet($$, format("L %s") % $2); } |
    lambda subjects verbs { yySet($$, format("L %s %s") % $2 % $3); }
    ;
    
lambda:
    IF |
    USING 
    ;
    
EntityStatement:
    lobject COLON INFORMAL { yySave<Statement>($$, new EntityDeclarationStatement(*$1, *$3)); } |
    lobject IS_A object { yySave<Statement>($$, new EntityInheritanceStatement(*$1, *$3)); }  |
    lobject INCLUDES parts { yySave<Statement>($$, new EntityStatement(*$1 /* todo! */)); }  |
    lobject PRODUCES parts { yySave<Statement>($$, new EntityStatement(*$1 /* todo! */)); } 
    ;
    
lobject:
    ENTITY { yySave($$, new Statement::LeftName(*$1, "")); } |
    ACTOR { yySave($$, new Statement::LeftName(*$1, "")); $$->addTag("actor"); } 
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
    QOS COLON INFORMAL { yySave<Statement>($$, new QosStatement(Statement::LeftName(*$1, "")/* todo! */)); } 
    ;

/* email of ActorUser "to approve" means: some text... */
VerbStatement:
    INFINITIVE object MEANS COLON INFORMAL { yySave<Statement>($$, new VerbStatement(/* todo! */)); }  |
    INFINITIVE object AKA MEANS COLON INFORMAL { yySave<Statement>($$, new VerbStatement(/* todo! */)); }  
    ;
    
/* See: R4.4, ActorUser, ... */
SeeStatement:
    SEE COLON entities { yySave<Statement>($$, new EmptyStatement()); } 
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