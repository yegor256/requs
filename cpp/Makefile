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

SELF = Makefile
DEBUG_FLAG = -DRQDQL_DEBUG=true
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
CPPFLAGS = -I./include -I./library $(DEBUG_FLAG)
EXEC = ./rqdql
SYMBOLS = include/symbols.h

SOURCES := $(shell find src -name "*.cpp")
OBJS := $(SOURCES:.cpp=.o) $(LIBS:.cpp=.o)

LIB_DIRS = library/pugixml library/boost-libs
LIB_SOURCES = $(shell find $(LIB_DIRS) -name "*.cpp")
LIB_OBJS := $(LIB_SOURCES:.cpp=.obj)

HEADERS := $(shell find include -name "*.h")

TEST_SOURCES := $(shell find test -name "*.cpp")
TESTS := $(TEST_SOURCES:.cpp=.test)
VALID_EXAMPLES = $(shell find examples/valid -name "*.txt")

# compile the product and run all tests
all: rqdql test

# compile/build the product
rqdql: lex.yy.c $(EXEC).tab.c $(OBJS) $(LIB_OBJS) $(SELF)
	$(CPP) $(CPPFLAGS) -o $@ $(EXEC).tab.c lex.yy.c $(OBJS) $(LIB_OBJS)
    
lex.yy.c: $(EXEC).l $(HEADERS) $(SELF)
	$(FLEX) $(EXEC).l
	
$(EXEC).tab.h: $(EXEC).tab.c

$(EXEC).tab.c: $(EXEC).y $(HEADERS) $(SELF)
	$(BISON) --no-lines --report=all --defines=$(SYMBOLS) $(EXEC).y

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# library objects
%.obj: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# test everything
test: $(TESTS) test-examples
	@for i in $(TESTS); do \
		echo "testing with '$$i':"; \
		$$i; \
	done

# compilation of unit tests
%.test: %.cpp
	$(CPP) $(CPPFLAGS) $(DEBUG_FLAG) -o $@ $< $(subst src/global.o, "", $(OBJS)) $(LIB_OBJS)

# test the entire mechanism with all test files
test-examples: $(EXEC) $(VALID_EXAMPLES)
	@for i in $(VALID_EXAMPLES); do \
		echo "testing with valid example '$$i':"; \
		$(EXEC) "//*" < $$i; \
	done

# clean everything!
clean:
	rm -f lex.yy.c $(EXEC).tab.c $(EXEC).tab.h \
	$(EXEC).output \
	$(OBJS) \
	$(LIB_OBJS) \
	$(EXEC) \
	$(TESTS) \
	$(SYMBOLS)

