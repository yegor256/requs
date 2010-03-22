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

PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
CPPFLAGS = -I./include -DRQDQL_DEBUG=true
OBJS = src/global.o src/rqdql.o
HEADERS = include/Scope.hpp \
	include/rqdql.hpp
EXEC = ./rqdql
TESTS = test/ScopeTest.o
EXAMPLES = examples/valid/ex-2.txt

rqdql: bison $(OBJS) Makefile $(EXAMPLES) test
	$(CPP) $(CPPFLAGS) -o $@ $@.tab.c lex.yy.c $(OBJS)
    
bison: lex.yy.c rqdql.tab.c rqdql.tab.h
	$(BISON) --no-lines --report=all -d rqdql.y
	$(FLEX) rqdql.l

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -f lex.yy.c $(EXEC).tab.c $(EXEC).tab.h
	rm -f rqdql.output
	rm -f $(OBJS)
	rm -f $(EXEC)

# compilation of unit tests
test/%.o: test/%.cpp
	$(CPP) $(CPPFLAGS) -o $@ $<

test: $(TESTS) test-all
	test/ScopeTest.o

test-all:	
	$(EXEC) "list" < examples/valid/ex-2.txt

deploy:
	ftp -u ftp://rqdql_deploy%40caybo.ru:uf8Klp7Y2Et4@rqdql.com/public/rqdql.html ../rqdql.com/rqdql.html
	
hook-test: rqdql trac-hook.php trac-hook.sh
	./trac-hook.sh < test/trac-hook/_request.txt
	
up:
	svn up --username yegor256@yahoo.com --password aF41Atlz .

