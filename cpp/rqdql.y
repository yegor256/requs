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
%token <name> QUOTED
%token <name> CAMEL
%token <name> QOS
%token <name> UC
%token <name> WORD
%token <num> NUMBER
%token <name> LETTER

%token COLON SEMICOLON DOT COMMA STAR
%token AND OR
%token PREPOSITION
%token WHERE
%token SUD
%token SOMEBODY
%token SOMETHING
%token THE
%token OF
%token THIS
%token PLURAL_MANY PLURAL_SOME PLURAL_ANY
%token OPEN_BRACE CLOSE_BRACE
%token IS_A
%token IS
%token INCLUDES

%nonassoc COMMA
%nonassoc AND
%nonassoc SEMICOLON
%nonassoc DOT
%nonassoc PREPOSITION
%left WORD
%left NUMBER
%right OF
%right COLON
%right INCLUDES

%%

srs:
    /* it can be empty */ |
    srs statement { } |
    srs error { lyyerror(@2, "statement ignored"); }
    ;

statement:
    invariantDeclaration | 
    slotsDeclaration | 
    useCaseDefinition | 
    useCaseAlternativeFlow
    ;

/** 
 * Invariants... 
 */
invariantDeclaration:
    className IS_A invariant DOT |
    className IS_A invariant error { lyyerror(@3, "Maybe a trailing DOT missed?"); }
    ;
    
invariant:
    predicate |
    predicate informal |
    error { lyyerror(@1, "Predicate is not clear"); }
    ;
    
predicate:
    informal |
    classe
    ;

classe:
    className |
    className OPEN_BRACE objectName CLOSE_BRACE
    ;

/**
 * Slots... 
 */
slotsDeclaration:
    classe INCLUDES COLON slots DOT
    ;
    
slots:
    slot |
    slots separator slot
    ;
    
slot:
    slotName |
    slotName COLON invariant
    ;
    
/**
 * Use cases... 
 */
useCaseDefinition:
    useCaseDeclaration flows |
    useCaseDeclaration informal DOT |
    useCaseDeclaration error { lyyerror(@2, "use case definition is not clear"); } |
    useCaseDeclaration informal error { lyyerror(@3, "maybe a trailing DOT missed after use case definition?"); }
    ;
     
useCaseDeclaration:
    UC WHERE signature COLON |
    UC WHERE signature error { lyyerror(@4, "COLON missed after UC signature"); }
    ;
    
/**
 * V
 * O V O V ...
 * O V O V ... O
 */
signature:
    informal |
    sigElements |
    sigElements informal
    ;
    
sigElements:
    sigElement |
    sigElements sigElement
    ;
    
sigElement:
    sigObject |
    sigVerb |
    informal sigObject |
    informal sigVerb
    ;

sigObject:
    classe |
    object
    ;
    
object:
    objectName |
    slotName OF object
    ;

/**
 * w1 w2 TO - is it "(w1) (w2 TO)" or "(w1 w2 TO)"
 */    
sigVerb:
    words PREPOSITION |
    WORD |
    WORD PREPOSITION
    ;
    
flows:
    flow |
    flows flow
    ;
    
flow:
    flowOpener signature DOT |
    flowOpener signature COLON |
    flowOpener signature error { lyyerror(@3, "maybe a trailing DOT missed after flow?"); } |
    flowOpener error { lyyerror(@2, "invalid SIGNATURE for the flow"); }
    ;
    
flowOpener:
    flowId CLOSE_BRACE |
    flowId DOT
    ;
    
flowId:
    NUMBER |
    flowIdPairs
    ;
    
flowIdPairs:
    flowIdPair |
    flowIdPairs flowIdPair
    ;
    
flowIdPair:
    NUMBER LETTER |
    STAR LETTER
    ;
    
/**
 * alternative flow of a use case
 */
useCaseAlternativeFlow:
    UC words COLON flows
    ;
    
/**
 * global elementary things 
 */
 
words:
    WORD WORD |
    words WORD
    ;
    
informal:
    QUOTED
    ;
    
separator:
    SEMICOLON | 
    SEMICOLON AND | 
    COMMA | 
    COMMA AND |
    AND
    ;

className:
    SUD |
    SOMEBODY |
    SOMETHING |
    CAMEL |
    THIS |
    slotName OF className
    ;
    
slotName:
    WORD |
    words
    ;
    
objectName:
    THE WORD
    ;
    
%%

// see global.cpp