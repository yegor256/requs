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
    using solm::Term;
    using std::string;
%}

%union {
    string* p;
    solm::Term* term;
}

%name-prefix="term"

%token DOT
%token <p> OPEN_BRACE CLOSE_BRACE
%token <p> OPERATOR
%token <p> NUMBER
%token <p> VARIABLE
%token <p> OBJECT
%token <p> TEXT

%type <term> term
%type <term> infixed
%type <term> prefixed

%left OPERATOR
%nonassoc DOT

%%

sentence:
    term DOT
        {
            /* the TERM is found, inject it into the destination */
            
            /**
             * This variable is defined in Term.cpp
             */
            extern solm::Term::Term* term_target;
            
            Term* term = static_cast<Term*>($1);
            *term_target = *term;
            delete term;
        }
    ;

term: /* solm::Term* */
    NUMBER
        {
            /* create new TERM from number */
            string* number = static_cast<string*>($1);
            Term* term = new Term(*number, std::vector<Term>());
            delete number;
            $$ = term;
        }
    |
    VARIABLE
        {
            /* create new TERM from variable */
            string* variable = static_cast<string*>($1);
            Term* term = new Term(*variable, std::vector<Term>());
            delete variable;
            $$ = term;
        }
    |
    OBJECT
        {
            /* create new TERM from object */
            string* object = static_cast<string*>($1);
            Term* term = new Term(*object, std::vector<Term>());
            delete object;
            $$ = term;
        }
    |
    TEXT
        {
            /* create new TERM from text */
            string* text = static_cast<string*>($1);
            Term* term = new Term(*text, std::vector<Term>());
            delete text;
            $$ = term;
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
    
infixed: /* solm::Term* */
    term OPERATOR term
        {
            /* create new TERM from two other terms and operator */
            string* op = static_cast<string*>($2);
            Term* term1 = static_cast<Term*>($1);
            Term* term2 = static_cast<Term*>($3);
            std::vector<Term> terms;
            terms.push_back(*term1);
            terms.push_back(*term2);
            Term* infixed = new Term(*op, terms);
            delete op;
            delete term1;
            delete term2;
            $$ = infixed;
        }
    ;
    
prefixed: /* solm::Term* */
    OBJECT OPEN_BRACE term CLOSE_BRACE
        {
            /* create new TERM from name and other term */
            string* object = static_cast<string*>($1);
            Term* term = static_cast<Term*>($3);
            std::vector<Term> terms;
            terms.push_back(*term);
            Term* prefixed = new Term(*object, terms);
            delete object;
            delete term;
            $$ = prefixed;
        }
    ;
    
%%

// see Solm/Term.cpp