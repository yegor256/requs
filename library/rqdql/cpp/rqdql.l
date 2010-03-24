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
    #include "Rqdql.hpp"
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
NSFX ([1-9](\.[1-9])?)
CAMEL_PART ([A-Z][a-z]+)
CAMEL ({CAMEL_PART}({CAMEL_PART})+)
ACTOR (Actor({CAMEL_PART})+|SUD)
UC (UC{NSFX})
FUR (R{NSFX})
QOS (QOS{NSFX})
ACRONYM ([A-Z]+(\+[A-Z]+)?)
TBD (TBD\(.*?\))
SEE (see|See)
INFINITIVE (\"to{SPACE}+[a-z]+\")
AKA (\(aka{SPACE}+\"\+[A-Z]\"\))
ATTRIBS (\[[a-z0-9]+(,[ ]*[a-z0-9]+)*\])
INCLUDES ((","{SPACE}*)?(including|includes?|has|contains?){SPACE}*":")
PRODUCES ((","{SPACE}*)?(producing|produces?|relates?{SPACE}+to|is{SPACE}+related{SPACE}+to){SPACE}*":")

    /* singular after entity or actor */
%x SINGULAR

    /* who is on the left side of the statement? */
    /* it's important to have in REGULAR state, not EXCLUSIVE */
%s LHS_FUR LHS_ENTITY LHS_QOS LHS_INFINITIVE

    /* what we should expect on the right side? */
%s RHS_INHERITANCE RHS_PARTS RHS_ACTIONS RHS_INFORMAL

    /* informal text for entity part */
%s PARTS_INFORMAL

%%

<INITIAL>#.* { /* ignore comments */ }

    /* who is on the left side of the statement? */
<INITIAL>{FUR} { BEGIN(LHS_FUR); rq.log(Rqdql::debug, "LHS_FUR"); REJECT; }
<INITIAL>{QOS} { BEGIN(LHS_QOS); rq.log(Rqdql::debug, "LHS_QOS"); REJECT; }
<INITIAL>{CAMEL} { BEGIN(LHS_ENTITY); rq.log(Rqdql::debug, "LHS_ENTITY"); REJECT; }
<INITIAL>{SEE} { rq.log(Rqdql::debug, "SEE"); return SEE; }
<INITIAL>{INFINITIVE} { yylval.name = strdup(yytext); 
	rq.log(Rqdql::debug, "INFINITIVE: %s", yytext); 
	BEGIN(LHS_INFINITIVE); rq.log(Rqdql::debug, "LHS_INFINITIVE"); 
	return INFINITIVE; 
}

    /* LHS modifiers */
<LHS_ENTITY>is{SPACE}a: { BEGIN(RHS_INHERITANCE); rq.log(Rqdql::debug, "RHS_INHERITANCE"); return IS_A; }
<LHS_ENTITY>{INCLUDES} { BEGIN(RHS_PARTS); rq.log(Rqdql::debug, "INCLUDES, RHS_PARTS"); return INCLUDES; }
<LHS_ENTITY>{PRODUCES} { BEGIN(RHS_PARTS); rq.log(Rqdql::debug, "PRODUCES, RHS_PARTS"); return PRODUCES; }
<LHS_FUR>{ATTRIBS} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "ATTRIBS: %s", yytext); return ATTRIBS; }
<LHS_FUR>":" { BEGIN(RHS_ACTIONS); rq.log(Rqdql::debug, "RHS_ACTIONS"); REJECT; }
<LHS_ENTITY>":" { BEGIN(RHS_INFORMAL); rq.log(Rqdql::debug, "RHS_INFORMAL"); REJECT; }
<LHS_QOS>":" { BEGIN(RHS_INFORMAL); rq.log(Rqdql::debug, "RHS_INFORMAL"); REJECT; }

	/* LHS infinitive */
<LHS_INFINITIVE>{AKA} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "AKA: %s", yytext); return AKA; }
<LHS_INFINITIVE>"means" { rq.log(Rqdql::debug, "MEANS"); return MEANS; }
<LHS_INFINITIVE>":" { BEGIN(RHS_INFORMAL); rq.log(Rqdql::debug, "RHS_INFORMAL"); REJECT; }

    /* informal text on the right part of entity */
<RHS_INFORMAL>[^\.]+ { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "INFORMAL"); return INFORMAL; }

    /* parts */
<RHS_PARTS>({INCLUDES}|{PRODUCES}) { rq.log(Rqdql::debug, "PARTS INCLUDE"); return INCLUDES; }
<RHS_PARTS>":" { BEGIN(PARTS_INFORMAL); rq.log(Rqdql::debug, "PARTS_INFORMAL"); REJECT; }
<PARTS_INFORMAL>[^\.;]+ {
    yylval.name = strdup(yytext); 
    rq.log(Rqdql::debug, "PART INFORMAL: '%s'", yytext);
    BEGIN(RHS_PARTS);
    rq.log(Rqdql::debug, "RHS_PARTS");
    return INFORMAL;
}

    /* get back to initial context */
"." { BEGIN(INITIAL); rq.log(Rqdql::debug, "DOT, INITIAL"); return DOT; }

    /* find entities */
{FUR} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "FUR: '%s'", yytext); return FUR; }
{ACTOR} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "ACTOR: '%s'", yytext); return ACTOR; }
{QOS} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "QOS: '%s'", yytext); return QOS; }
{UC} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "UC: '%s'", yytext); return UC; }
{CAMEL} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "ENTITY: '%s'", yytext); return ENTITY; }

<RHS_PARTS>"-s" |
<RHS_ACTIONS>"-s" { rq.log(Rqdql::debug, "PLURAL_MANY"); return PLURAL_MANY; }
<RHS_PARTS>"(s)" |
<RHS_ACTIONS>"(s)" { rq.log(Rqdql::debug, "PLURAL_SOME"); return PLURAL_SOME; }
<RHS_ACTIONS>"?" |
<RHS_PARTS>"?" { rq.log(Rqdql::debug, "PLURAL_ANY"); return PLURAL_ANY; }
    
"/" |
"or" { rq.log(Rqdql::debug, "OR"); return OR; }
":" { rq.log(Rqdql::debug, "COLON"); return COLON; }
";" { rq.log(Rqdql::debug, "SEMICOLON"); return SEMICOLON; }
"," { rq.log(Rqdql::debug, "COMMA"); return COMMA; }
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"can" { rq.log(Rqdql::debug, "CAN"); return CAN; }
"and" { rq.log(Rqdql::debug, "AND"); return AND; }
"of" { rq.log(Rqdql::debug, "OF"); return OF; }
"if" | 
"only" { rq.log(Rqdql::debug, "IF"); return IF; }
"using" { rq.log(Rqdql::debug, "USING"); return USING; }
"himself" | 
"them" | 
"it" | 
"he" |
"him" |
"itself" { rq.log(Rqdql::debug, "THIS"); return THIS; }

	/* NULL words */
"a" |
"the" |
"is" |
"are |
"have" |
"has" |
"an" { /* ignore them */ }

[a-z]+ { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "WORD: '%s'", yytext); return WORD; }
{ACRONYM} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "ACRONYM: '%s'", yytext); return ACRONYM; }
{TBD} { yylval.name = strdup(yytext); rq.log(Rqdql::debug, "TBD: '%s'", yytext); return TBD; }

\n { yycolumn = 1; }
[ \t\r] { /* ignore spaces */ }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
