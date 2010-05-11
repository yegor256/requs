/**
 *
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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SCOPE_SCANNER_H
#define __INCLUDE_SCOPE_SCANNER_H

typedef union {
    string* name;
    int num;
    void* ptr;
} YYSTYPE;

// bison/flex file
// this define will protect us against BISON default YYSTYPE
#define YYSTYPE_IS_DECLARED 1
#define YYSTYPE_IS_TRIVIAL 1
#include "Scanner/symbols.h"

extern int yyparse();
extern int yylex(void);
extern int yylineno;

#include "Logger.h"
#include "Scanner/supplementary.h"
#include "Scanner/rqdql.y.c"
#include "Scanner/rqdql.l.c"

namespace rqdql {
class Scanner {
public:
    static Scanner& getInstance(); // singleton pattern
    void scan(const string&); // scan input string
};
#include "Scanner/ScannerImpl.h"
}

#endif
