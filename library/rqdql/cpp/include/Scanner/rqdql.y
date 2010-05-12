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
    #include "Proxy.h"
    #include "Solm.h"
    #include "brokers.h"
	using boost::format;    
    using namespace proxy;
%}

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
%type <name> words
%type <name> className
%type <ptr> classPath
%type <name> objectName
%type <ptr> slots
%type <ptr> slot
%type <name> slotName
%type <ptr> predicate
%type <ptr> invariant
%type <ptr> classDefinition
%type <ptr> useCaseDefinition
%type <ptr> invariantDeclaration
%type <ptr> slotsDeclaration
%type <ptr> useCaseDeclaration
%type <ptr> useCaseAlternativeDeclaration
%type <ptr> useCaseStarter
%type <ptr> signature
%type <ptr> sigElements
%type <ptr> sigElement
%type <ptr> de
%type <ptr> deType
%type <ptr> verb
%type <ptr> flows
%type <ptr> flow
%type <name> informal


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
%token SELF
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
    srs statement |
    srs error { lyyerror(@2, "statement ignored"); }
    ;

statement:
    classDefinition  | 
    useCaseDefinition 
    ;

classDefinition:
    invariantDeclaration |
    slotsDeclaration
    ;
    
useCaseDefinition:
    useCaseDeclaration |
    useCaseAlternativeDeclaration
    ;

/** 
 * Invariants... 
 */
invariantDeclaration:
    className IS_A invariant DOT 
        { 
            Type* t = Proxy::getInstance().getType(*$1);
            t->addPredicate(static_cast<solm::Formula*>($3));
            $$ = t;
            protocol(@1, $$);
        } 
    |
    className IS_A invariant error { lyyerror(@3, "Maybe a trailing DOT missed?"); }
    ;
    
invariant:
    predicate |
    predicate informal |
    error { lyyerror(@1, "Predicate is not clear"); }
    ;
    
predicate:
    informal 
        {
            $$ = new solm::Info("'" + *$1);
            protocol(@1, $$);
        } 
    |
    className 
        {
            $$ = new solm::Info("'instance of " + *$1);
            protocol(@1, $$);
        }
    ;

/**
 * Slots... 
 */
slotsDeclaration:
    classPath INCLUDES COLON slots DOT 
        {
            Type* t = static_cast<Type*>($1);
            Type::Slots* e = static_cast<Type::Slots*>($4);
            for (Type::Slots::const_iterator i = e->begin(); i != e->end(); ++i) {
                t->addSlot(*i);
            }
            $$ = t;
            protocol(@1, $$);
        }
    ;
    
classPath:
    className 
        {
            $$ = Proxy::getInstance().getType(*$1);
            protocol(@1, $$);
        }
    |
    slotName OF classPath
        {
            Type* t = static_cast<Type*>($3);
            $$ = t->getSlot(*$1)->getType();
            protocol(@1, $$);
        }
    ;
    
slots:
    slot
        {
            Type::Slots* v = new Type::Slots();
            v->push_back(static_cast<Slot*>($1));
            $$ = v;
            protocol(@1, $$);
        }
    |
    slots separator slot 
        {
            Type::Slots* v = new Type::Slots();
            Type::Slots* e = static_cast<Type::Slots*>($1);
            for (Type::Slots::const_iterator i = e->begin(); i != e->end(); ++i) {
                v->push_back(*i);
            }
            v->push_back(static_cast<Slot*>($3));
            $$ = v;
            protocol(@1, $$);
        } 
    ;
    
slot:
    slotName
        {
            $$ = new Slot(*$1);
            protocol(@1, $$);
        }
    |
    slotName COLON invariant
        { 
            $$ = new Slot(
                *$1, 
                "1..n -> 1", 
                static_cast<solm::Formula*>($3), 
                Proxy::getInstance().getType("text")
            );
            protocol(@1, $$);
        }
    ;
    
/**
 * Use cases... 
 */
useCaseDeclaration:
    useCaseStarter flows { /*$$ = $1; static_cast<UseCase*>($$) += $2; */} |
    useCaseStarter informal DOT |
    useCaseStarter error { lyyerror(@2, "use case definition is not clear"); } |
    useCaseStarter informal error { lyyerror(@3, "maybe a trailing DOT missed after use case definition?"); }
    ;
     
useCaseStarter:
    UC WHERE signature COLON { /*$$ = new UseCase($3);*/ } |
    UC WHERE signature error { lyyerror(@4, "COLON missed after UC signature"); }
    ;
    
/**
 * V
 * O V O V ...
 * O V O V ... O
 */
signature:
    informal { /*$$ = new Signature($1);*/ } |
    sigElements { /*$$ = new Signature("signature...", $1);*/ } |
    sigElements informal { /*$$ = new Signature("signature...", $1);*/ }
    ;
    
sigElements:
    sigElement { /*$$ = (new vector<Signature::Element>)->push_back(static_cast<Signature::Element*>($1)); delete $1;*/ } |
    sigElements sigElement { /*$$ = $1; static_cast<vector<Signature::Element> >($$)->push_back(static_cast<Signature::Element*>($1)); delete $1;*/ } 
    ;
    
sigElement:
    de |
    verb |
    informal de { /*$$ = $2; static_cast<Signature::Element*>($$)->addPrefix($1);*/ } |
    informal verb { /*$$ = $2; static_cast<Signature::Element*>($$)->addPrefix($1);*/ }
    ;

de:
    objectName |
    deType |
    deType OPEN_BRACE objectName CLOSE_BRACE
    ;
    
deType:    
    className { /*$$ = makeClasse($1);*/ } |
    slotName OF objectName { /*$$ = makeClasse($1); appendObject($$, $3);*/ }
    ;
    
/**
 * w1 w2 TO - is it "(w1) (w2 TO)" or "(w1 w2 TO)"
 */    
verb:
    words PREPOSITION { /*$$ = (new Signature::Element())->setVerb(format("%s %s") % $1 $2);*/ } |
    WORD { /*$$ = (new Signature::Element())->setVerb($1);*/ } |
    WORD PREPOSITION { /*$$ = (new Signature::Element())->setVerb(format("%s %s") % $1 $2);*/ } 
    ;
    
flows:
    flow |
    flows flow
    ;
    
flow:
    flowOpener signature DOT { /*$$ = new UseCase::Flow($1, $2);*/ } |
    flowOpener signature COLON { /*$$ = new UseCase::Flow($1, $2);*/ } |
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
useCaseAlternativeDeclaration:
    UC words COLON flows { /*$$ = new UseCase(); *$$ ;*/}
    ;
    
/**
 * global elementary things 
 */
words:
    WORD WORD { /*$$ = &format("%s %s") % *$1 *$2;*/ } |
    words WORD { /*$$ = &format("%s %s") % *$1 *$2;*/ }
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
    SUD { /*$$ = new Classe("SUD");*/ } |
    SOMEBODY { /*$$ = new Classe("somebody");*/ } |
    SOMETHING { /*$$ = new Classe("something");*/ } |
    CAMEL { /*$$ = new Classe($1);*/ } |
    SELF { /*$$ = new Classe("self");*/ }
    ;
    
slotName:
    WORD |
    words
    ;
    
objectName:
    THE WORD { $$ = $2; }
    ;
    
%%

// see global.cpp