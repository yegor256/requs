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
CPPFLAGS = -I./include -I./library -DRQDQL_DEBUG=true
EXEC = ./rqdql

SOURCES := $(shell find src -name "*.cpp")
OBJS := $(SOURCES:.cpp=.o)
HEADERS := $(shell find include -name "*.h")
TEST_SOURCES := $(shell find test -name "*.cpp")
TESTS := $(TEST_SOURCES:.cpp=.test)
VALID_EXAMPLES = $(shell find examples/valid -name "*.txt")

all: rqdql test

rqdql: lex.yy.c rqdql.tab.h rqdql.tab.c $(OBJS) Makefile
	$(CPP) $(CPPFLAGS) -o $@ rqdql.tab.c lex.yy.c $(OBJS)
    
lex.yy.c: rqdql.l $(HEADERS)
	$(FLEX) rqdql.l
	
rqdql.tab.h: rqdql.tab.c

rqdql.tab.c: rqdql.y $(HEADERS)
	$(BISON) --no-lines --report=all -d rqdql.y

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# clean everything!
clean:
	rm -f lex.yy.c rqdql.tab.c rqdql.tab.h
	rm -f rqdql.output
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f $(TESTS)

test: rqdql $(TESTS) test-all $(HEADERS)
	for i in $(TESTS); do \
		$$i; \
	done

# compilation of unit tests
%.test: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ $< src/rqdql.o

# test the entire mechanism with all test files
test-all: $(EXEC) $(VALID_EXAMPLES)
	for i in $(VALID_EXAMPLES); do \
		$(EXEC) "list" < $$i; \
	done

# test PHP Trac hook
hook-test: rqdql trac-hook.php trac-hook.sh
	./trac-hook.sh < test/trac-hook/_request.txt

# update the code from SVN	
up:
	svn up --username yegor256@yahoo.com --password aF41Atlz .

