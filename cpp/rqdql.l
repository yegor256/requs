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

%{
    #include "rqdql.h"
%}

%{
    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
%}

%option noyywrap yylineno
%option nodefault

SPACE ([ \t\r\n]+)
NSFX ([1-9]+(\.[1-9]+)?)
CAMEL_PART ([A-Z][a-z]+)
CAMEL ({CAMEL_PART}({CAMEL_PART})+)
ACTOR (Actor({CAMEL_PART})+|SUD)
FUR (R{NSFX})
ACRONYM ([A-Z]+(\+[A-Z]+)?)
TBD (TBD\(.*?\))
SEE (see|See)

    /* singular after entity or actor */
%x SINGULAR

    /* who is on the left side of the statement? */
    /* it's important to have in REGULAR state, not EXCLUSIVE */
%s LHS_FUR LHS_ENTITY

    /* what we should expect on the right side? */
%s RHS_INHERITANCE RHS_PARTS RHS_ACTIONS RHS_INFORMAL

    /* informal text for entity part */
%s PARTS_INFORMAL

%%

<INITIAL>#.* { /* ignore comments */ }

    /* who is on the left side of the statement? */
<INITIAL>{FUR} { BEGIN(LHS_FUR); rqdql::log(rqdql::debug, "LHS_FUR"); REJECT; }
<INITIAL>{CAMEL} { BEGIN(LHS_ENTITY); rqdql::log(rqdql::debug, "LHS_ENTITY"); REJECT; }
<INITIAL>{SEE} { rqdql::log(rqdql::debug, "SEE"); return SEE; }

    /* LHS modifiers */
<LHS_ENTITY>is{SPACE}a: { BEGIN(RHS_INHERITANCE); rqdql::log(rqdql::debug, "RHS_INHERITANCE"); return IS_A; }
<LHS_ENTITY>includes?{SPACE}?: { BEGIN(RHS_PARTS); rqdql::log(rqdql::debug, "INCLUDES, RHS_PARTS"); return INCLUDES; }
<LHS_ENTITY>produces?{SPACE}?: { BEGIN(RHS_PARTS); rqdql::log(rqdql::debug, "PRODUCES, RHS_PARTS"); return PRODUCES; }
<LHS_FUR>":" { BEGIN(RHS_ACTIONS); rqdql::log(rqdql::debug, "RHS_ACTIONS"); REJECT; }
<LHS_ENTITY>":" { BEGIN(RHS_INFORMAL); rqdql::log(rqdql::debug, "RHS_INFORMAL"); REJECT; }

    /* informal text on the right part of entity */
<RHS_INFORMAL>[^\.]+ { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "INFORMAL"); return INFORMAL; }

    /* parts */
<RHS_PARTS>(include|produce)s?{SPACE}: { rqdql::log(rqdql::debug, "PARTS INCLUDE"); return INCLUDES; }
<RHS_PARTS>":" { BEGIN(PARTS_INFORMAL); rqdql::log(rqdql::debug, "PARTS_INFORMAL"); REJECT; }
<PARTS_INFORMAL>[^\.;]+ {
    yylval.name = strdup(yytext); 
    rqdql::log(rqdql::debug, "PART INFORMAL: '%s'", yytext);
    BEGIN(RHS_PARTS);
    return INFORMAL;
}

    /* get back to initial context */
"." { BEGIN(INITIAL); rqdql::log(rqdql::debug, "DOT, INITIAL"); return DOT; }

    /* find entities */
{FUR} { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "FUR: '%s'", yytext); return FUR; }
{ACTOR} { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "ACTOR: '%s'", yytext); return ACTOR; }
{CAMEL} { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "ENTITY: '%s'", yytext); return ENTITY; }

<RHS_PARTS>"-s" |
<RHS_ACTIONS>"-s" { rqdql::log(rqdql::debug, "PLURAL_MANY"); return PLURAL_MANY; }
<RHS_PARTS>"(s)" |
<RHS_ACTIONS>"(s)" { rqdql::log(rqdql::debug, "PLURAL_SOME"); return PLURAL_SOME; }
<RHS_ACTIONS>"?" |
<RHS_PARTS>"?" { rqdql::log(rqdql::debug, "PLURAL_ANY"); return PLURAL_ANY; }
    
"/" |
"or" { rqdql::log(rqdql::debug, "OR"); return OR; }
":" { rqdql::log(rqdql::debug, "COLON"); return COLON; }
";" { rqdql::log(rqdql::debug, "SEMICOLON"); return SEMICOLON; }
"," { rqdql::log(rqdql::debug, "COMMA"); return COMMA; }
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"can" { rqdql::log(rqdql::debug, "CAN"); return CAN; }
"and" { rqdql::log(rqdql::debug, "AND"); return AND; }
"of" { rqdql::log(rqdql::debug, "OF"); return OF; }
"if" | 
"only" { return IF; }
"using" { return USING; }
"himself" | 
"them" | 
"it" | 
"itself" { return THIS; }

[a-z]+ { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "WORD: '%s'", yytext); return WORD; }
{ACRONYM} { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "ACRONYM: '%s'", yytext); return ACRONYM; }
{TBD} { yylval.name = strdup(yytext); rqdql::log(rqdql::debug, "TBD: '%s'", yytext); return TBD; }

{SPACE} { /* ignore spaces */ }
\n { yycolumn = 1; }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
