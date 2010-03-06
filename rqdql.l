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

%option noyywrap nodefault yylineno

NSFX ([1-9]+(\.[1-9]+)?)
CAMEL ([A-Z][a-z]+)

%s SINGULAR

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

%%

#.* { /* ignore comments */ }

":" { return COLON; }
";" { return SEMICOLON; }
"." { return DOT; }
"," { return COMMA; }
"(" { return OPEN_BRACE; }
")" { return CLOSE_BRACE; }
"can" { return CAN; }
"and" { return AND; }
"of" { return OF; }
"if"|"only" { return IF; }
"using" { return USING; }
"himself"|"them"|"it"|"itself" { return THIS; }

[a-z]+ { yylval.name = strdup(yytext); return WORD; }

R{NSFX} { yylval.name = strdup(yytext); return ENTITY_FUR; }
"SUD" { yylval.name = strdup(yytext); return ENTITY_ACTOR; }
"Actor"{CAMEL} { yylval.name = strdup(yytext); BEGIN(SINGULAR); return ENTITY_ACTOR; }
{CAMEL}{CAMEL} { yylval.name = strdup(yytext); BEGIN(SINGULAR); return ENTITY; }
<SINGULAR>"-s" { BEGIN(INITIAL); return PLURAL_MANY; }
<SINGULAR>"(s)" { BEGIN(INITIAL); return PLURAL_SOME; }
<SINGULAR>"?" { BEGIN(INITIAL); return PLURAL_ANY; }

[\t\r ] { /* ignore spaces */ }
\n { yycolumn = 1; }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
