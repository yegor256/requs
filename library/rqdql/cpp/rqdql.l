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
	using namespace rqdql;
	using boost::format;
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
NSFX ([1-8](\.[1-8])?)
CAMEL_PART ([A-Z][a-z]+)
CAMEL ({CAMEL_PART}({CAMEL_PART})+)
ACTOR (Actor({CAMEL_PART})+|SUD)
UC (UC{NSFX})
FUR (R{NSFX})
QOS (QOS{NSFX})
ACRONYM ([A-Z]{2,}(\+[A-Z]+)?)
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
<INITIAL>{FUR} { BEGIN(LHS_FUR); log("LHS_FUR"); REJECT; }
<INITIAL>{QOS} { BEGIN(LHS_QOS); log("LHS_QOS"); REJECT; }
<INITIAL>{CAMEL} { BEGIN(LHS_ENTITY); log("LHS_ENTITY"); REJECT; }
<INITIAL>{SEE} { log("SEE"); return SEE; }
<INITIAL>{INFINITIVE} { 
	yySet(yylval.name, yytext); 
	log(format("INFINITIVE: %s") % yytext); 
	BEGIN(LHS_INFINITIVE); log("LHS_INFINITIVE"); 
	return INFINITIVE; 
}

    /* LHS modifiers */
<LHS_ENTITY>is{SPACE}a: { BEGIN(RHS_INHERITANCE); log("RHS_INHERITANCE"); return IS_A; }
<LHS_ENTITY>{INCLUDES} { BEGIN(RHS_PARTS); log("INCLUDES, RHS_PARTS"); return INCLUDES; }
<LHS_ENTITY>{PRODUCES} { BEGIN(RHS_PARTS); log("PRODUCES, RHS_PARTS"); return PRODUCES; }
<LHS_FUR>{ATTRIBS} { yySet(yylval.name, yytext); log(format("ATTRIBS: %s") % yytext); return ATTRIBS; }
<LHS_FUR>":" { BEGIN(RHS_ACTIONS); log("RHS_ACTIONS"); REJECT; }
<LHS_ENTITY>":" { BEGIN(RHS_INFORMAL); log("RHS_INFORMAL"); REJECT; }
<LHS_QOS>":" { BEGIN(RHS_INFORMAL); log("RHS_INFORMAL"); REJECT; }

	/* LHS infinitive */
<LHS_INFINITIVE>{AKA} { yySet(yylval.name, yytext); log(format("AKA: %s") % yytext); return AKA; }
<LHS_INFINITIVE>"means" { log("MEANS"); return MEANS; }
<LHS_INFINITIVE>":" { BEGIN(RHS_INFORMAL); log("RHS_INFORMAL"); REJECT; }

    /* informal text on the right part of entity */
<RHS_INFORMAL>[^\.]+ { yySet(yylval.name, yytext); log("INFORMAL"); return INFORMAL; }

    /* parts */
<RHS_PARTS>({INCLUDES}|{PRODUCES}) { log("PARTS INCLUDE"); return INCLUDES; }
<RHS_PARTS>":" { BEGIN(PARTS_INFORMAL); log("PARTS_INFORMAL"); REJECT; }
<PARTS_INFORMAL>[^\.;]+ {
    yySet(yylval.name, yytext); 
    log(format("PART INFORMAL: '%s'") % yytext);
    BEGIN(RHS_PARTS);
    log("RHS_PARTS");
    return INFORMAL;
}

    /* get back to initial context */
"." { BEGIN(INITIAL); log("DOT, INITIAL"); return DOT; }

    /* find entities */
{FUR} { yySet(yylval.name, yytext); log(format("FUR: '%s'") % yytext); return FUR; }
{ACTOR} { yySet(yylval.name, yytext); log(format("ACTOR: '%s'") % yytext); return ACTOR; }
{QOS} { yySet(yylval.name, yytext); log(format("QOS: '%s'") % yytext); return QOS; }
{UC} { yySet(yylval.name, yytext); log(format("UC: '%s'") % yytext); return UC; }
{CAMEL} { yySet(yylval.name, yytext); log(format("ENTITY: '%s'") % yytext); return ENTITY; }

<RHS_PARTS>"-s" |
<RHS_ACTIONS>"-s" { log("PLURAL_MANY"); return PLURAL_MANY; }
<RHS_PARTS>"(s)" |
<RHS_ACTIONS>"(s)" { log("PLURAL_SOME"); return PLURAL_SOME; }
<RHS_ACTIONS>"?" |
<RHS_PARTS>"?" { log("PLURAL_ANY"); return PLURAL_ANY; }
    
"/" |
"or" { log("OR"); return OR; }
":" { log("COLON"); return COLON; }
";" { log("SEMICOLON"); return SEMICOLON; }
"," { log("COMMA"); return COMMA; }
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"can" { log("CAN"); return CAN; }
"and" { log("AND"); return AND; }
"of" { log("OF"); return OF; }
"if" | 
"only" { log("IF"); return IF; }
"using" { log("USING"); return USING; }
"himself" | 
"them" | 
"it" | 
"he" |
"him" |
"itself" { log("THIS"); return THIS; }

	/* NULL words */
"a" |
"the" |
"is" |
"are" |
"have" |
"has" |
"an" { /* ignore them */ }

[a-z]+ { yySet(yylval.name, yytext); log(format("WORD: '%s'") % yytext); return WORD; }
{ACRONYM} { yySet(yylval.name, yytext); log(format("ACRONYM: '%s'") % yytext); return ACRONYM; }
{TBD} { yySet(yylval.name, yytext); log(format("TBD: '%s'") % yytext); return TBD; }

\n { yycolumn = 1; }
[ \t\r] { /* ignore spaces */ }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
