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
QOS (QOS{NSFX})
INCLUDES ((","{SPACE}*)?(including|includes?|has|contains?){SPACE}*":")

    /* singular after entity or actor */
%x SINGULAR

    /* informal text */
%x INFORMAL

%%

#.* { /* ignore comments */ }

    /* find entities */
{ACTOR} { yySet(yylval.name, yytext); log(format("ACTOR: '%s'") % yytext); return ACTOR; }
{QOS} { yySet(yylval.name, yytext); log(format("QOS: '%s'") % yytext); return QOS; }
{UC} { yySet(yylval.name, yytext); log(format("UC: '%s'") % yytext); return UC; }
{CAMEL} { yySet(yylval.name, yytext); log(format("ENTITY: '%s'") % yytext); return CLASS; }

"-s" { log("PLURAL_MANY"); return PLURAL_MANY; }
"(s)" { log("PLURAL_SOME"); return PLURAL_SOME; }
"?" { log("PLURAL_ANY"); return PLURAL_ANY; }
    
"/" |
"or" { log("OR"); return OR; }
":" { log("COLON"); return COLON; }
"." { log("DOT"); return DOT; }
";" { log("SEMICOLON"); return SEMICOLON; }
"," { log("COMMA"); return COMMA; }
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"is a" |
"is an" | 
"is" | { log("IS_A"); return IS_A; }
"and" { log("AND"); return AND; }
"of" { log("OF"); return OF; }
"if" { log("IF"); return IF; }
"the" { log("THE"); return THE; }

"himself" | 
"itself" { log("THIS"); return THIS; }

[a-z]+ { yySet(yylval.name, yytext); log(format("WORD: '%s'") % yytext); return WORD; }

(\") { BEGIN(INFORMAL); }
<INFORMAL>([\n\t.]) { *yylval.name << yytext; }
<INFORMAL>(\") { BEGIN(INITIAL); yySet(yylval.name, yytext); return INFORMAL; }

\n { yycolumn = 1; }
[ \t\r] { /* ignore spaces */ }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
