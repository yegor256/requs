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
    #include "Solm/Predicate.h"
    using solm::P;
    using std::string;

    /**
     * This variable is defined in Predicate.cpp
     */
    extern solm::Predicate::Predicate* predicate_target;
%}

%union {
    string* p;
    solm::Predicate* predicate;
}

%name-prefix="predicate"

%token DOT
%token <p> COMMA
%token <p> OPEN_BRACE CLOSE_BRACE
%token <p> OPERATOR
%token <p> NUMBER
%token <p> VARIABLE
%token <p> OBJECT
%token <p> TEXT

%type <predicate> predicate
%type <predicate> infixed
%type <predicate> prefixed
%type <p> op

%left OPERATOR
%left COMMA

%%

sentence:
    predicate DOT
        {
            /* the TERM is found, inject it into the destination */
            Predicate* predicate = static_cast<Predicate*>($1);
            *predicate_target = *predicate;
            delete predicate;
        }
    ;

predicate: /* solm::Predicate* */
    NUMBER
        {
            /* create new TERM from number */
            string* number = static_cast<string*>($1);
            Predicate* predicate = new Predicate(*number, std::vector<Predicate>());
            delete number;
            $$ = predicate;
        }
    |
    VARIABLE
        {
            /* create new TERM from variable */
            string* variable = static_cast<string*>($1);
            Predicate* predicate = new Predicate(*variable, std::vector<Predicate>());
            delete variable;
            $$ = predicate;
        }
    |
    OBJECT
        {
            /* create new TERM from object */
            string* object = static_cast<string*>($1);
            Predicate* predicate = new Predicate(*object, std::vector<Predicate>());
            delete object;
            $$ = predicate;
        }
    |
    TEXT
        {
            /* create new TERM from text */
            string* text = static_cast<string*>($1);
            Predicate* predicate = new Predicate(*text, std::vector<Predicate>());
            delete text;
            $$ = predicate;
        }
    |
    infixed
        {
            /* do nothing, just copy pointers */
            $$ = $1;
        }
    |
    prefixed
        {
            /* do nothing, just copy pointers */
            $$ = $1;
        }
    ;
    
op: /* std::string* */
    OPERATOR
    |
    COMMA
    ;
    
infixed: /* solm::Predicate* */
    predicate op predicate
        {
            /* create new TERM from two other predicates and operator */
            string* op = static_cast<string*>($2);
            Predicate* predicate1 = static_cast<Predicate*>($1);
            Predicate* predicate2 = static_cast<Predicate*>($3);
            std::vector<Predicate> predicates;
            predicates.push_back(*predicate1);
            predicates.push_back(*predicate2);
            Predicate* infixed = new Predicate(*op, predicates);
            delete op;
            delete predicate1;
            delete predicate2;
            $$ = infixed;
        }
    ;
    
prefixed: /* solm::Predicate* */
    OBJECT OPEN_BRACE predicate CLOSE_BRACE
        {
            /* create new TERM from name and other predicate */
            string* object = static_cast<string*>($1);
            Predicate* predicate = static_cast<Predicate*>($3);
            std::vector<Predicate> predicates;
            predicates.push_back(*predicate);
            Predicate* prefixed = new Predicate(*object, predicates);
            delete object;
            delete predicate;
            $$ = prefixed;
        }
    ;
    
%%

// see Solm/Predicate.cpp