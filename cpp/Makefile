#
# rqdql.com, Fully Automated Zend Framework
# RQDQL.com, Requirements Definition and Query Language
#
# Redistribution and use in source and binary forms, with or 
# without modification, are PROHIBITED without prior written 
# permission from the author. This product may NOT be used 
# anywhere and on any computer except the server platform of 
# rqdql.com. located at www.rqdql.com. If you received this 
# code occasionally and without intent to use it, please report 
# this incident to the author by email: team@rqdql.com
#
# @author Yegor Bugayenko <egor@tpc2.com>
# @copyright Copyright (c) rqdql.com, 2010
# @version $Id$

VERSION = 0.6

MAKEFLAGS = -r
SELF = Makefile
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
INCLUDE = ./include
CPPFLAGS = -I$(INCLUDE) -I./library -I/usr/include/libxml2 $(shell xml2-config --cflags)
LDFLAGS = $(shell xml2-config --libs)
EXEC = ./rqdql
SVN = /usr/local/bin/svn
DEPENDS = dependencies.mk

SOURCES = $(shell find $(INCLUDE) -name "*.cpp")
OBJS := $(SOURCES:.cpp=.o)

SYMBOLS = include/Scanner/symbols.h
FLEX_SRC = include/Scanner/rqdql.l
FLEX_DEST = include/Scanner/rqdql.l.c
BISON_SRC = include/Scanner/rqdql.y
BISON_DEST = include/Scanner/rqdql.y.c

LIB = library/all-externals.so
LIB_DIRS = library/boost-libs
LIB_SOURCES = $(shell find $(LIB_DIRS) -name "*.cpp")
LIB_OBJS := $(LIB_SOURCES:.cpp=.o)

TEST_DIR = ./test
TEST_RUNNER = $(TEST_DIR)/runner
TEST_SOURCES := $(shell find $(TEST_DIR) -name "*.cpp")
TEST_OBJS := $(TEST_SOURCES:.cpp=.o)

# instruct Make NOT to remove intermediate files
.SECONDARY:

# disable built-in implicit rule
%.o: %.cpp

# compile the product and run all tests
all: depends $(EXEC) test

# build dependencies
$(DEPENDS): $(FLEX_DEST) $(BISON_DEST) $(SELF)
	$(CPP) $(CPPFLAGS) -M $(TEST_SOURCES) $(SOURCES) > $(DEPENDS)
	
-include $(DEPENDS)

# objects, we just compile them, NO linking
%.o: %.cpp $(DEPENDS)
	$(CPP) $(CPPFLAGS) -fPIC -o $@ -g -c $<

# compile/build the product
$(EXEC): $(BISON_DEST) $(FLEX_DEST) $(LIB)
	$(CPP) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIB) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""

$(FLEX_DEST): $(FLEX_SRC) $(HEADERS) $(SELF)
	$(FLEX) -o$(FLEX_DEST) $(FLEX_SRC)

$(BISON_DEST): $(BISON_SRC) $(HEADERS) $(SELF)
	$(BISON) --no-lines --report=all --defines=$(SYMBOLS) --output=$(BISON_DEST) $(BISON_SRC)

$(LIB): $(LIB_OBJS)
	ar -r $(LIB) $(LIB_OBJS)

# test everything
test: $(TEST_RUNNER)
	$(TEST_RUNNER)

$(TEST_RUNNER): $(LIB) $(TEST_OBJS) $(OBJS)
	$(CPP) $(LDFLAGS) -o $(TEST_RUNNER) $(TEST_OBJS) $(LIB) $(OBJS)

# clean everything!
clean:
	rm -f \
	$(BISON_DEST) \
	include/Scanner/rqdql.y.output \
	$(FLEX_DEST) \
	$(EXEC) \
	$(LIB_OBJS) \
	$(TEST_OBJS) \
	$(OBJS) \
	$(LIB) \
	$(DEPENDS) \
	$(SYMBOLS)

