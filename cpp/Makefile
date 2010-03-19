#
# FaZend.com, Fully Automated Zend Framework
# RQDQL.com, Requirements Definition and Query Language
#
# Redistribution and use in source and binary forms, with or 
# without modification, are PROHIBITED without prior written 
# permission from the author. This product may NOT be used 
# anywhere and on any computer except the server platform of 
# FaZend.com. located at www.fazend.com. If you received this 
# code occasionally and without intent to use it, please report 
# this incident to the author by email: team@rqdql.com
#
# @author Yegor Bugayenko <egor@tpc2.com>
# @copyright Copyright (c) rqdql.com, 2010
# @version $Id$

CPP = c++
BISON = bison
FLEX = flex
CPPFLAGS = -I./include 
OBJS = src/Scope.o src/global.o src/rqdql.o
HEADERS = include/Scope.h \
	include/rqdql.h
EXEC = ./rqdql
TESTS = test/ScopeTest.o
EXAMPLES = examples/valid/ex-2.txt

rqdql: $(EXEC).l $(EXEC).y bison $(OBJS) Makefile $(EXAMPLES)
	$(CPP) $(CPPFLAGS) -o $@ $@.tab.c lex.yy.c $(OBJS)
	$(EXEC) "list" < examples/valid/ex-2.txt
    
bison:
	$(BISON) --no-lines --report=all -d rqdql.y
	$(FLEX) rqdql.l

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -f lex.yy.c $(EXEC).tab.c $(EXEC).tab.h
	rm -f rqdql.output
	rm -f $(OBJS)
	rm -f $(EXEC)

test: test/rqdql-test.cpp $(TESTS)
	$(EXEC) "list" < examples/valid/ex-2.txt
	
deploy:
	ftp -u ftp://rqdql_deploy%40caybo.ru:uf8Klp7Y2Et4@rqdql.com/public/rqdql.html ../rqdql.com/rqdql.html
	