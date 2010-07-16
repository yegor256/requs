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

    /**
     * This variable is defined in Term.cpp
     */
    extern solm::Term::Term* term_target;
%}

%union {
    string* p;
    solm::Term* one;
    solm::Term::Terms* many;
}

%name-prefix="term"

%token <p> OPEN_BRACE CLOSE_BRACE
%token <p> VARIABLE
%token <p> OBJECT
%token <p> NUMBER
%token <p> TEXT

%type <one> term
%type <one> list
%type <many> terms

%%

sentence:
    term
        {
            /* the TERM is found, inject it into the destination */
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
    list
        {
            $$ = $1;
        }
    ;
    
list: /* solm::Term* */
    OPEN_BRACE VARIABLE terms CLOSE_BRACE
        {
            /* create new TERM from name and other terms */
            string* variable = static_cast<string*>($2);
            Term::Terms* terms = static_cast<Term::Terms*>($3);
            Term* list = new Term(*variable, *terms);
            delete variable;
            delete terms;
            $$ = list;
        }
    ;
    
terms:
    /* can be empty */
        {
            solm::Term::Terms* terms = new solm::Term::Terms();
            $$ = terms;
        }
    |
    terms term
        {
            Term::Terms* terms = static_cast<Term::Terms*>($1);
            Term* term = static_cast<Term*>($2);
            terms->push_back(*term);
            delete term;
            $$ = terms;
        }
    ;
    
%%

// see Solm/Term.cpp