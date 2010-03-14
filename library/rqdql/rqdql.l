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
    int oldState;
%}

%{
    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
        
    void logg(const char* str)
    {
        if (1) {
            cout << str << endl;
        }
    }
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
<INITIAL>{FUR} { BEGIN(LHS_FUR); logg("LHS_FUR"); REJECT; }
<INITIAL>{CAMEL} { BEGIN(LHS_ENTITY); logg("LHS_ENTITY"); REJECT; }

    /* LHS modifiers */
<LHS_ENTITY>is{SPACE}a: { BEGIN(RHS_INHERITANCE); logg("RHS_INHERITANCE"); return IS_A; }
<LHS_ENTITY>includes?{SPACE}?: { BEGIN(RHS_PARTS); logg("INCLUDES, RHS_PARTS"); return INCLUDES; }
<LHS_ENTITY>produces?{SPACE}?: { BEGIN(RHS_PARTS); logg("PRODUCES, RHS_PARTS"); return PRODUCES; }
<LHS_FUR>":" { BEGIN(RHS_ACTIONS); logg("RHS_ACTIONS"); REJECT; }
<LHS_ENTITY>":" { BEGIN(RHS_INFORMAL); logg("RHS_INFORMAL"); REJECT; }

    /* informal text on the right part of entity */
<RHS_INFORMAL>[^\.]+ { yylval.name = strdup(yytext); logg("INFORMAL"); return INFORMAL; }

    /* parts */
<RHS_PARTS>(include|produce)s?{SPACE}: { logg("PARTS INCLUDE"); return INCLUDES; }
<RHS_PARTS>":" { BEGIN(PARTS_INFORMAL); logg("PARTS_INFORMAL"); REJECT; }
<PARTS_INFORMAL>[^\.;]+ { yylval.name = strdup(yytext); cout << "PART INFORMAL: '" << yytext << "'\n"; BEGIN(RHS_PARTS); return INFORMAL; }

    /* get back to initial context */
"." { BEGIN(INITIAL); logg("DOT, INITIAL"); return DOT; }

    /* find entities */
{FUR} { yylval.name = strdup(yytext); cout << "FUR: " << yytext << endl; return FUR; }
{ACTOR} { yylval.name = strdup(yytext); cout << "ACTOR: " << yytext << endl; return ACTOR; }
{CAMEL} { yylval.name = strdup(yytext); cout << "ENTITY: " << yytext << endl; return ENTITY; }

    /*
{ACTOR} { yylval.name = strdup(yytext); oldState = YY_START; BEGIN(SINGULAR); cout << "actor: " << oldState << endl; return ACTOR; }
{CAMEL} { yylval.name = strdup(yytext); oldState = YY_START; BEGIN(SINGULAR); cout << "actor: " << oldState << endl; return ENTITY; }
<SINGULAR>"-s" { BEGIN(oldState); return PLURAL_MANY; }
<SINGULAR>"(s)" { BEGIN(oldState); return PLURAL_SOME; }
<SINGULAR>"?" { BEGIN (oldState); return PLURAL_ANY; }
<SINGULAR>. { BEGIN(oldState); cout << "stop SINGULAR with '" << yytext << "', state back to " << oldState << "\n"; REJECT; }
    */
<RHS_PARTS>"-s" |
<RHS_ACTIONS>"-s" { logg("PLURAL_MANY"); return PLURAL_MANY; }
<RHS_PARTS>"(s)" |
<RHS_ACTIONS>"(s)" { logg("PLURAL_SOME"); return PLURAL_SOME; }
<RHS_ACTIONS>"?" |
<RHS_PARTS>"?" { logg("PLURAL_ANY"); return PLURAL_ANY; }
    
"/" |
"or" { logg("OR"); return OR; }
":" { logg("COLON"); return COLON; }
";" { logg("SEMICOLON"); return SEMICOLON; }
"," { logg("COMMA"); return COMMA; }
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"can" { logg("CAN"); return CAN; }
"and" { logg("AND"); return AND; }
"of" { logg("OF"); return OF; }
"if"|"only" { return IF; }
"using" { return USING; }
"himself"|"them"|"it"|"itself" { return THIS; }

[a-z]+ { yylval.name = strdup(yytext); cout << "WORD: " << yytext << "\n"; return WORD; }
{ACRONYM} { yylval.name = strdup(yytext); cout << "ACRONYM: " << yytext << "\n"; return ACRONYM; }

{SPACE} { /* ignore spaces */ }
\n { yycolumn = 1; }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
