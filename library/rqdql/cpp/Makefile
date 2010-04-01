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

# compile the product and run all tests
all: rqdql test

# compile/build the product
rqdql: lex.yy.c $(EXEC).tab.h $(EXEC).tab.c $(OBJS) Makefile
	$(CPP) $(CPPFLAGS) -o $@ $(EXEC).tab.c lex.yy.c $(OBJS)
    
lex.yy.c: $(EXEC).l $(HEADERS)
	$(FLEX) $(EXEC).l
	
$(EXEC).tab.h: $(EXEC).tab.c

$(EXEC).tab.c: $(EXEC).y $(HEADERS)
	$(BISON) --no-lines --report=all -d $(EXEC).y

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# test everything
test: $(TESTS) test-examples test-hook
	for i in $(TESTS); do \
		$$i; \
	done

# compilation of unit tests
%.test: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ $< src/rqdql.o

# test the entire mechanism with all test files
test-examples: $(EXEC) $(VALID_EXAMPLES)
	for i in $(VALID_EXAMPLES); do \
		$(EXEC) "//*" < $$i; \
	done

# test PHP Trac hook
test-hook: $(EXEC) hook/trac-hook.php hook/trac-hook.sh
	./hook/trac-hook.sh --silent < test/hook/_request.txt

# update the code from SVN	
up:
	svn up .

# clean everything!
clean:
	rm -f lex.yy.c $(EXEC).tab.c $(EXEC).tab.h
	rm -f $(EXEC).output
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f $(TESTS)

