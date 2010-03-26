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
TESTS = test/ScopeTest.test
EXAMPLES = examples/valid/ex-2.txt

all: rqdql test

rqdql: lex.yy.c rqdql.tab.h rqdql.tab.c $(OBJS) Makefile $(EXAMPLES)
	$(CPP) $(CPPFLAGS) -o $@ rqdql.tab.c lex.yy.c $(OBJS)
    
lex.yy.c: rqdql.l include/rqdql.h
	$(FLEX) rqdql.l
	
rqdql.tab.h: rqdql.tab.c

rqdql.tab.c: rqdql.y include/rqdql.h
	$(BISON) --no-lines --report=all -d rqdql.y

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# clean everything!
clean:
	rm -f lex.yy.c $(EXEC).tab.c $(EXEC).tab.h
	rm -f rqdql.output
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f $(TESTS)

# compilation of unit tests
%.test: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ $< src/rqdql.o

test: rqdql $(TESTS) test-all $(HEADERS)
	test/ScopeTest.test

# test the entire mechanism with a test file
test-all: $(EXEC)
	$(EXEC) "list" < examples/valid/ex-2.txt

# deploy the HTML to the target hosting platform
deploy:
	ftp -u ftp://rqdql_deploy%40caybo.ru:uf8Klp7Y2Et4@rqdql.com/public/rqdql.html ../rqdql.com/rqdql.html
	
# test PHP Trac hook
hook-test: rqdql trac-hook.php trac-hook.sh
	./trac-hook.sh < test/trac-hook/_request.txt

# update the code from SVN	
up:
	svn up --username yegor256@yahoo.com --password aF41Atlz .

