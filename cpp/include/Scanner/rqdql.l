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

%option noyywrap
%option yylineno
%option nodefault
/* %option case-insensitive */

SPACE ([ \t\r\n]+)
NSFX ([1-8](\.[1-8])?)
CAMEL_PART ([A-Z][a-z]+)
CAMEL ({CAMEL_PART}({CAMEL_PART})+)
UC (UC{NSFX})
QOS (QOS{NSFX})

    /* singular after entity or actor */
%x SINGULAR

    /* informal text */
%x READING_QUOTED

%%

#.* { /* ignore comments */ }

    /* find entities */
{QOS} { yySet(yylval.name, yytext); log(format("QOS: '%s'") % yytext); return QOS; }
{UC} { yySet(yylval.name, yytext); log(format("UC: '%s'") % yytext); return UC; }
{CAMEL} { yySet(yylval.name, yytext); log(format("CAMEL: '%s'") % yytext); return CAMEL; }

"-s" { log("PLURAL_MANY"); return PLURAL_MANY; }
"(s)" { log("PLURAL_SOME"); return PLURAL_SOME; }
"?" { log("PLURAL_ANY"); return PLURAL_ANY; }
    
":" { log("COLON"); return COLON; }
"." { log("DOT"); return DOT; }
";" { log("SEMICOLON"); return SEMICOLON; }
"*" { log("STAR"); return STAR; }
"," { log("COMMA"); return COMMA; }
"(" { log("OPEN_BRACE"); return OPEN_BRACE; }
")" { log("CLOSE_BRACE"); return CLOSE_BRACE; }
"is"([ \t\r\n]+)"a" |
"is"([ \t\r\n]+)"an" { log("IS_A"); return IS_A; }

"are" |
"is" { log("IS"); return IS; }

[Ww]"here" { log("WHERE"); return WHERE; }
"/" |
[Oo]"r" { log("OR"); return OR; }
[Aa]"nd" { log("AND"); return AND; }
[Oo]"f" { log("OF"); return OF; }
[Tt]"he" { log("THE"); return THE; }
[Ii]"ncludes" { log("INCLUDES"); return INCLUDES; }
[Tt]"o" | 
[Ww]"ith" |
[Ii]"nto" |
[Ii]"n" |
[Ff]"rom" |
[Aa]"t" { log("PREPOSITION"); return PREPOSITION; }

[Hh]"mself" | 
[Ii]"tself" { log("SELF"); return SELF; }

	/* SUD */
[Ww]"e" | 
[Th]"he"[ \t\n\r]+[Ss]"ystem" | 
"SUD" | 
[Uu]"s" { log("SUD"); return SUD; }

[Ss]"omebody" { log("SOMEBODY"); return SOMEBODY; }
[Ss]"omething" { log("SOMETHING"); return SOMETHING; }

	/* numbers and words */
[0-9]+ { yylval.num, atoi(yytext); log(format("NUMBER: '%s'") % yytext); return NUMBER; }
[a-zA-Z]/[^a-zA-Z] { yySet(yylval.name, yytext); log(format("LETTER: '%s'") % yytext); return LETTER; }
[a-zA-Z]+ { yySet(yylval.name, yytext); log(format("WORD: '%s'") % yytext); return WORD; }

	/* quoted informal texts */
(\") { BEGIN(READING_QUOTED); yySet(yylval.name, format()); }
<READING_QUOTED>(\") { BEGIN(INITIAL); log(format("QUOTED: '%s'") % *yylval.name); return QUOTED; }
<READING_QUOTED>([\n\t\r]|.) { *yylval.name += yytext; }
<READING_QUOTED><<EOF>> { yyerror("unclosed informal text"); }

\n { yycolumn = 1; }
[ \t\r] { /* ignore spaces */ }
. { yyerror("unknown symbol %c", yytext[0]); }

%%
