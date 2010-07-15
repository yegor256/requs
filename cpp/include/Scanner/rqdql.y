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

// we should track locations of errors, in YYLTYPE, see lyyerror()
%locations

%{
    #include <string>
    #include <vector>
    #include <boost/format.hpp>
    #include "rqdql.h"

    #include "Proxy.h"
    #include "Proxy/Type.h"
    #include "Proxy/Slot.h"
    #include "Proxy/UseCase.h"
    #include "Proxy/Signature.h"

    #include "Solm.h"
    #include "Solm/Predicate.h"

    #include "brokers/De.h"
    #include "brokers/FlowHolder.h"
    #include "brokers/SigElement.h"
    #include "brokers/AltPair.h"
    #include "brokers/SignatureHolder.h"
%}

// Here we should say that the type of non-terminal
// terms are mapped to %union.name, and are strings because of that
%type <name> words
%type <name> slotName
%type <name> objectName
%type <name> informal
%type <name> verb
%type <ptr> theClass
%type <ptr> classPath
%type <ptr> slots
%type <ptr> slot
%type <ptr> predicate
%type <ptr> invariant
%type <ptr> classDefinition
%type <ptr> useCaseDefinition
%type <ptr> invariantDeclaration
%type <ptr> slotsDeclaration
%type <ptr> useCaseDeclaration
%type <ptr> useCaseAlternativeDeclaration
%type <ptr> ucStarter
%type <ptr> signature
%type <ptr> sigElements
%type <ptr> sigElement
%type <ptr> de
%type <ptr> deType
%type <ptr> flows
%type <ptr> flow
%type <ptr> altId
%type <ptr> altIdPair

// Declaration of all known tokens
%token <name> QUOTED
%token <name> CAMEL
%token <name> QOS
%token <name> UC
%token <name> WORD
%token <num> NUMBER
%token <name> LETTER
%token <name> PREPOSITION

// Declaration of all known un-typed tokens
%token COLON SEMICOLON DOT COMMA STAR
%token AND OR
%token WHERE
%token SUD
%token SOMEBODY
%token SOMETHING
%token THE
%token OF
%token IF
%token SELF
%token PLURAL_MANY PLURAL_SOME PLURAL_ANY
%token OPEN_BRACE CLOSE_BRACE
%token IS_A
%token INCLUDES

// Declaration of associating rules
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
    /* it can be empty */ 
    |
    srs statement 
    ;

statement:
    classDefinition  
    | 
    useCaseDefinition  
    | 
    qosDefinition 
    |
    informal DOT
    |
    error DOT
        {
            lyyerror(@1, "Statement ignored"); 
        }
    ;

classDefinition:
    invariantDeclaration |
    slotsDeclaration
    ;
    
useCaseDefinition:
    useCaseDeclaration |
    useCaseAlternativeDeclaration
    ;

qosDefinition:
    QOS COLON informal DOT
    ;
    
/** 
 * Invariants... 
 */
invariantDeclaration: /* proxy::Type* */
    classPath IS_A invariant DOT 
        {
            if (!$1) {
                lyyerror(@3, "You can't place HIMSELF to the left part of declaration");
            } else {
                proxy::Type* classPath = static_cast<proxy::Type*>($1);
                solm::Predicate* invariant = static_cast<solm::Predicate*>($3);
                classPath->invariant() += *invariant;
                delete invariant;
                $$ = classPath;
                protocol(@1, classPath);
            }
        }
    ;
    
invariant: /* solm::Predicate* */
    predicate 
    |
    predicate informal
    ;
    
predicate: /* solm::Predicate* */
    informal
        {
            solm::Predicate* predicate = new solm::Predicate("(info)");
            std::string* informal = static_cast<std::string*>($1);
            predicate->arg(0, "\"" + *informal + "\"");
            delete informal;
            $$ = predicate;
            protocol(@1, predicate);
        } 
    |
    words
        {
            solm::Predicate* predicate = new solm::Predicate("(info)");
            std::string* words = static_cast<std::string*>($1);
            predicate->arg(0, "\"" + *words + "\"");
            delete words;
            $$ = predicate;
            protocol(@1, predicate);
        }
    |
    WORD
        {
            solm::Predicate* predicate = new solm::Predicate("(info)");
            std::string* word = static_cast<std::string*>($1);
            predicate->arg(0, "\"" + *word + "\"");
            delete word;
            $$ = predicate;
            protocol(@1, predicate);
        }
    |
    theClass plurality
        {
            if (!$1) {
                lyyerror(@1, "Class can't be an instance of himself");
            } else {
                proxy::Type* theClass = static_cast<proxy::Type*>($1);
                solm::Predicate* predicate = new solm::Predicate("(" + (std::string)*theClass + ")"); // by name of type
                predicate->arg(0, "x");
                $$ = predicate;
                protocol(@1, predicate);
            }
        }
    ;

/**
 * Slots... 
 */
slotsDeclaration: /* proxy::Type* */
    classPath INCLUDES COLON slots DOT 
        {
            proxy::Type* classPath = static_cast<proxy::Type*>($1);
            proxy::Entity::Slots* slots = static_cast<proxy::Entity::Slots*>($4);
            *classPath += *slots; // add all slots to the type
            delete slots;
            $$ = classPath;
            protocol(@1, classPath);
        }
    ;
    
classPath: /* proxy::Type* */
    theClass 
        {
            proxy::Type* theClass = static_cast<proxy::Type*>($1);
            if (!theClass) {
                lyyerror(@1, "HIMSELF is forbidden here, in class path");
            } else {
                $$ = theClass;
                protocol(@1, theClass);
            }
        }
    |
    slotName OF classPath
        {
            std::string* slotName = static_cast<std::string*>($1);
            proxy::Type* classPath = static_cast<proxy::Type*>($3);
            proxy::Type* classPathLhs = static_cast<proxy::Type*>(classPath->slot(*slotName).entity().get());
            delete slotName;
            $$ = classPathLhs;
            protocol(@1, classPathLhs);
        }
    ;
    
slots: /* std::vector<proxy::Slot*>* */
    slot
        {
            proxy::Entity::Slots* slots = new proxy::Entity::Slots();
            proxy::Slot* slot = static_cast<proxy::Slot*>($1);
            slots->push_back(*slot);
            delete slot;
            $$ = slots;
            protocol(@1, slots);
        }
    |
    slots separator slot 
        {
            proxy::Entity::Slots* slots = static_cast<proxy::Entity::Slots*>($1);
            proxy::Slot* slot = static_cast<proxy::Slot*>($3);
            proxy::Entity::Slots* slotsLhs = new proxy::Entity::Slots();
            slotsLhs = slots; // copy all slots
            slotsLhs->push_back(*slot);
            $$ = slotsLhs;
            protocol(@1, slotsLhs);
        } 
    |
    slots separator error
        {
            lyyerror(@3, "Slot ignored"); 
        }
    ;
    
slot: /* proxy::Slot* */
    slotName
        {
            std::string* slotName = static_cast<std::string*>($1);
            proxy::Slot* slot = new proxy::Slot(*slotName);
            delete slotName;
            $$ = slot;
            protocol(@1, slot);
        }
    |
    slotName COLON invariant
        { 
            std::string* slotName = static_cast<std::string*>($1);
            solm::Predicate* invariant = static_cast<solm::Predicate*>($3);
            proxy::Slot* slot = new proxy::Slot(*slotName);
            slot->entity()->invariant() += *invariant;
            delete slotName;
            delete invariant;
            protocol(@1, slot);
        }
    ;
    
/**
 * Use cases... 
 */
useCaseDeclaration: /* NULL */
    ucStarter flows 
        {
            proxy::UseCase* ucStarter = static_cast<proxy::UseCase*>($1);
            proxy::UseCase* flows = static_cast<proxy::UseCase*>($2);
            *ucStarter = *flows; // set full collection of flows
            delete flows;
        } 
    |
    ucStarter informal DOT
        {
            proxy::UseCase* ucStarter = static_cast<proxy::UseCase*>($1);
            std::string* informal = static_cast<std::string*>($2);
            // @todo To make explicit injection into SOLM of just this formula
            // in a form of declaration
            delete informal;
        }
    ;
     
ucStarter: /* proxy::UseCase */
    UC WHERE signature COLON 
        {
            std::string* uc = static_cast<std::string*>($1);
            brokers::SignatureHolder* signature = static_cast<brokers::SignatureHolder*>($3);
            if (!signature->hasSignature()) {
                lyyerror(@1, "Use Case signature can't be completely informal");
            } else {
                proxy::Slot& s = rqdql::get<proxy::Proxy>().slot(*uc);
                if (s) {
                    lyyerror(@1, "Use Case is already declared");
                } else {
                    proxy::UseCase* ucStarter = new proxy::UseCase(signature->getSignature());
                    s.entity(boost::shared_ptr<proxy::UseCase>(ucStarter));
                    $$ = ucStarter;
                    protocol(@1, ucStarter);
                }
            }
            delete uc;
            delete signature;
        }
    ;
    
/**
 * V
 * O V O V ...
 * O V O V ... O
 */
signature: /* brokers::SignatureHolder* */
    informal 
        {
            std::string* informal = static_cast<std::string*>($1);
            brokers::SignatureHolder* signature = new brokers::SignatureHolder();
            signature->set(*informal);
            delete informal;
            $$ = signature;
            protocol(@1, signature);
        }
    |
    sigElements 
        {
            brokers::SigElements* sigElements = static_cast<brokers::SigElements*>($1);
            brokers::SignatureHolder* signature = new brokers::SignatureHolder();
            signature->set(*sigElements);
            delete sigElements;
            $$ = signature;
            protocol(@1, signature);
        }
    |
    sigElements informal 
        {
            brokers::SigElements* sigElements = static_cast<brokers::SigElements*>($1);
            std::string* informal = static_cast<std::string*>($2);
            brokers::SignatureHolder* signature = new brokers::SignatureHolder();
            signature->set(*sigElements);
            signature->set(*informal);
            delete sigElements;
            delete informal;
            $$ = signature;
            protocol(@1, signature);
        }
    ;
    
sigElements: /* brokers::SigElements* */
    sigElement
        {
            brokers::SigElement* sigElement = static_cast<brokers::SigElement*>($1);
            brokers::SigElements* sigElements = new brokers::SigElements();
            sigElements->push_back(*sigElement);
            delete sigElement;
            $$ = sigElements;
            protocol(@1, sigElements);
        }
    |
    sigElements sigElement
        {
            brokers::SigElements* sigElements = static_cast<brokers::SigElements*>($1);
            brokers::SigElement* sigElement = static_cast<brokers::SigElement*>($2);
            brokers::SigElements* sigElementsLhs = new brokers::SigElements();
            sigElementsLhs = sigElements; // copy entire vector
            sigElementsLhs->push_back(*sigElement);
            delete sigElements;
            delete sigElement;
            $$ = sigElementsLhs;
            protocol(@1, sigElementsLhs);
        }
    ;
    
sigElement: /* brokers::SigElement* */
    de
        {
            brokers::De* de = static_cast<brokers::De*>($1);
            brokers::SigElement* sigElement = new brokers::SigElement();
            sigElement->setDe(*de);
            delete de;
            $$ = sigElement;
            protocol(@1, sigElement);
        }
    |
    verb 
        {
            std::string* verb = static_cast<std::string*>($1);
            brokers::SigElement* sigElement = new brokers::SigElement();
            sigElement->setVerb(*verb);
            delete verb;
            $$ = sigElement;
            protocol(@1, sigElement);
        }
    |
    informal de 
        {
            std::string* informal = static_cast<std::string*>($1);
            brokers::De* de = static_cast<brokers::De*>($2);
            brokers::SigElement* sigElement = new brokers::SigElement();
            sigElement->setInformal(*informal);
            sigElement->setDe(*de);
            delete informal;
            delete de;
            $$ = sigElement;
            protocol(@1, sigElement);
        }
    |
    informal verb
        {
            std::string* informal = static_cast<std::string*>($1);
            std::string* verb = static_cast<std::string*>($2);
            brokers::SigElement* sigElement = new brokers::SigElement();
            sigElement->setInformal(*informal);
            sigElement->setVerb(*verb);
            delete informal;
            delete verb;
            $$ = sigElement;
            protocol(@1, sigElement);
        }
    ;

de: /* brokers::De* */
    objectName 
        { 
            std::string* objectName = static_cast<std::string*>($1);
            brokers::De* de = new brokers::De();
            de->setName(*objectName);
            delete objectName;
            $$ = de;
            protocol(@1, de);
        }
    |
    deType 
        {
            brokers::Explanation* deType = static_cast<brokers::Explanation*>($1);
            brokers::De* de = new brokers::De();
            de->setExplanation(*deType);
            delete deType;
            $$ = de;
            protocol(@1, de);
        }
    |
    deType OPEN_BRACE objectName CLOSE_BRACE
        {
            brokers::Explanation* deType = static_cast<brokers::Explanation*>($1);
            std::string* objectName = static_cast<std::string*>($3);
            brokers::De* de = new brokers::De();
            de->setExplanation(*deType);
            de->setName(*objectName);
            delete deType;
            delete objectName;
            $$ = de;
            protocol(@1, de);
        }
    ;
    
deType: /* brokers::Explanation* */
    theClass
        {
            proxy::Type* theClass = static_cast<proxy::Type*>($1);
            brokers::Explanation* deType = new brokers::Explanation();
            // maybe it's SELF?
            if (theClass) {
                deType->setType(*theClass);
            }
            $$ = deType;
            protocol(@1, deType);
        }
    |
    slotName OF objectName 
        {
            std::string* slotName = static_cast<std::string*>($1);
            std::string* objectName = static_cast<std::string*>($3);
            brokers::Explanation* deType = new brokers::Explanation();
            deType->setNames(*slotName, *objectName);
            delete slotName;
            delete objectName;
            $$ = deType;
            protocol(@1, deType);
        }
    ;
    
/**
 * w1 w2 TO - is it "(w1) (w2 TO)" or "(w1 w2 TO)"
 */    
verb:
    words PREPOSITION 
        {
            std::string* words = static_cast<std::string*>($1);
            std::string* preposition = static_cast<std::string*>($2);
            std::string* verb = new std::string((boost::format("%s %s") % *words % *preposition).str());
            delete words;
            delete preposition;
            $$ = verb;
        } 
    |
    WORD 
        {
            $$ = $1;
        }
    |
    PREPOSITION 
        {
            $$ = $1;
        }
    |
    WORD PREPOSITION 
        {
            std::string* word = static_cast<std::string*>($1);
            std::string* preposition = static_cast<std::string*>($2);
            std::string* verb = new std::string((boost::format("%s %s") % *word % *preposition).str());
            delete word;
            delete preposition;
            $$ = verb;
        } 
    ;
    
flows: /* proxy::UseCase* */
    flow 
        {
            brokers::FlowHolder* flow = static_cast<brokers::FlowHolder*>($1);
            proxy::UseCase* flows = new proxy::UseCase(proxy::Signature(""));
            boost::shared_ptr<proxy::UseCase> uc(new proxy::UseCase(flow->getFlow())); // allocate it in HEAP
            flows->slot(flow->getId()).entity(uc);
            delete flow;
            $$ = flows;
            protocol(@1, flows);
        }
    |
    flows flow
        {
            proxy::UseCase* flows = static_cast<proxy::UseCase*>($1);
            brokers::FlowHolder* flow = static_cast<brokers::FlowHolder*>($2);
            proxy::UseCase* flowsLhs = new proxy::UseCase(proxy::Signature(""));
            flowsLhs = flows; // copy entire vector
            boost::shared_ptr<proxy::UseCase> uc(new proxy::UseCase(flow->getFlow())); // allocate it in HEAP
            flowsLhs->slot(flow->getId()).entity(uc);
            delete flows;
            delete flow;
            $$ = flowsLhs;
            protocol(@1, flowsLhs);
        }
    ;
    
flow: /* brokers::FlowHolder* */
    NUMBER DOT signature DOT 
        {
            int number = $1;
            brokers::SignatureHolder* signature = static_cast<brokers::SignatureHolder*>($3);
            brokers::FlowHolder* flow = new brokers::FlowHolder();
            if (signature->hasSignature()) {
                flow->setFlow(proxy::UseCase(signature->getSignature()));
            } else {
                flow->setFlow(proxy::UseCase(proxy::Signature("")));
            }
            flow->setId(number);
            $$ = flow;
            protocol(@1, flow);
        }
    ;
    
/**
 * alternative flow of a use case
 */
useCaseAlternativeDeclaration: /* NULL */
    UC altId CLOSE_BRACE IF predicate COLON flows 
    {
        std::string* uc = static_cast<std::string*>($1);
        brokers::AltPairs* altId = static_cast<brokers::AltPairs*>($2);
        solm::Predicate* predicate = static_cast<solm::Predicate*>($5);
        proxy::UseCase* flows = static_cast<proxy::UseCase*>($7);

        // brokers::SignatureHolder* signature = static_cast<brokers::SignatureHolder*>($3);
        // if (!signature->hasSignature()) {
        //     lyyerror(@1, "Use Case signature can't be completely informal");
        // } else {
        //     proxy::Slot& s = rqdql::get<proxy::Proxy>().slot(*UC);
        //     if (s) {
        //         lyyerror(@1, "Use Case is already declared");
        //     } else {
        //         proxy::UseCase* ucStarter = new proxy::UseCase(signature->getSignature());
        //         s.entity(ucStarter);
        //         $$ = ucStarter;
        //         protocol(@1, ucStarter);
        //     }
        // }
        // delete UC;
        // delete signature;


        // Flows* flows = rqdql::get<Proxy>().get<UseCase>(*$1);
        // Flow* dest = 0;
        // for (brokers::AltPairs::const_iterator i = e->begin(); i != e->end(); ++i) {
        //     if (dest) {
        //         flows = dest->findAlternative((*(i-1))->getLetter());
        //     }
        //     if ((*i)->getNum() == -1) {
        //         lyyerror(@2, "STAR is not supported yet");
        //         dest = 0;
        //         break;
        //     } else {
        //         dest = flows->getFlow((*i)->getNum());
        //     }
        // }
        // if (dest) {
        //     // it's found, inject flows there!
        //     protocol(@1, dest);
        //     Flows* alt = dest->addAlternative(static_cast<solm::Predicate*>($5));
        //     alt->setFlows(static_cast<Flows*>($7));
        // }
    }
    ;
    
altId: /* brokers::AltPairs* */
    altIdPair
        {
            brokers::AltPair* altIdPair = static_cast<brokers::AltPair*>($1);
            brokers::AltPairs* altId = new brokers::AltPairs();
            altId->push_back(*altIdPair);
            delete altIdPair;
            $$ = altId;
        }
    |
    altId altIdPair
        {
            brokers::AltPairs* altId = static_cast<brokers::AltPairs*>($1);
            brokers::AltPair* altIdPair = static_cast<brokers::AltPair*>($2);
            brokers::AltPairs* altIdLhs = new brokers::AltPairs();
            altIdLhs = altId;
            altIdLhs->push_back(*altIdPair);
            $$ = altIdLhs;
        }
    ;
    
altIdPair: /* brokers::AltPair* */
    NUMBER LETTER 
        {
            int number = $1;
            std::string* letter = static_cast<std::string*>($2);
            brokers::AltPair* altIdPair = new brokers::AltPair(number, letter->at(0));
            delete letter;
            $$ = altIdPair;
        }
    |
    STAR LETTER
        {
            std::string* letter = static_cast<std::string*>($2);
            brokers::AltPair* altIdPair = new brokers::AltPair(-1, letter->at(0));
            delete letter;
            $$ = altIdPair;
        }
    ;
    
/**
 * global elementary things 
 */
words: /* std::string* */
    WORD WORD
        {
            std::string* word1 = static_cast<std::string*>($1);
            std::string* word2 = static_cast<std::string*>($2);
            std::string* words = new std::string((boost::format("%s %s") % *word1 % *word2).str());
            delete word1;
            delete word2;
            $$ = words;
        }
    |
    words WORD
        {
            std::string* words = static_cast<std::string*>($1);
            std::string* word = static_cast<std::string*>($2);
            std::string* wordsLhs = new std::string((boost::format("%s %s") % *words % *word).str());
            delete words;
            delete word;
            $$ = wordsLhs;
        }
    ;
    
informal: /* std::string* */
    QUOTED
    ;
    
separator: /* int */
    SEMICOLON | 
    SEMICOLON AND | 
    COMMA | 
    COMMA AND |
    AND
    ;

theClass: /* proxy::Type* */
    CAMEL 
        {
            std::string* camel = static_cast<std::string*>($1);
            proxy::Type* theClass = static_cast<proxy::Type*>(rqdql::get<proxy::Proxy>().slot(*camel).entity().get());
            delete camel;
            $$ = theClass;
            protocol(@1, theClass);
        }
    |
    SUD 
        {
            proxy::Type* theClass = static_cast<proxy::Type*>(rqdql::get<proxy::Proxy>().slot("SUD").entity().get());
            $$ = theClass;
            protocol(@1, theClass);
        }
    |
    SOMEBODY
        {
            proxy::Type* theClass = static_cast<proxy::Type*>(rqdql::get<proxy::Proxy>().slot("somebody").entity().get());
            $$ = theClass;
            protocol(@1, theClass);
        }
    |
    SOMETHING
        {
            proxy::Type* theClass = static_cast<proxy::Type*>(rqdql::get<proxy::Proxy>().slot("something").entity().get());
            $$ = theClass;
            protocol(@1, theClass);
        }
    |
    SELF
        {
            $$ = 0; // NULL pointer to TYPE
        }
    ;
    
plurality: /* int */
    /* empty */ |
    PLURAL_MANY |
    PLURAL_SOME |
    PLURAL_ANY
    ;
    
slotName: /* std::string* */
    WORD |
    words
    ;
    
objectName: /* std::string* */
    THE WORD { $$ = $2; }
    ;
    
%%

// see Scanner.h