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

# 0.3.2: added signature matching to find manipulators
# 0.3.3: TURNS INTO is parseable
# 0.3.4: Plurality introduced into BISON
# 0.4: Test cases are generated
# 0.5: OMF library injected, MOF/XMI started to be used for test cases
VERSION = 0.5

MAKEFLAGS = -r
SELF = Makefile
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
INCLUDE = ./include
TESTS = ./test
CPPFLAGS = -I$(INCLUDE) -I./library -I/usr/include/libxml2 $(shell xml2-config --cflags)
LDFLAGS = $(shell xml2-config --libs)
EXEC = ./rqdql
SVN = /usr/local/bin/svn

SOURCES = $(shell find $(INCLUDE) -name "*.cpp")
HEADERS := $(shell find $(INCLUDE) -name "*.h")
OBJS := $(SOURCES:.cpp=.obj)

SYMBOLS = include/Scanner/symbols.h
FLEX_SRC = include/Scanner/rqdql.l
FLEX_DEST = include/Scanner/rqdql.l.c
BISON_SRC = include/Scanner/rqdql.y
BISON_DEST = include/Scanner/rqdql.y.c

LIB = library/all-externals.so
LIB_DIRS = library/boost-libs
LIB_SOURCES = $(shell find $(LIB_DIRS) -name "*.cpp")
LIB_OBJS := $(LIB_SOURCES:.cpp=.obj)

TEST_SOURCES := $(shell find $(TESTS) -name "*Test.cpp")
TESTS := $(TEST_SOURCES:.cpp=.test)
VALID_EXAMPLES = $(shell find examples/valid -name "*.txt")

# compile the product and run all tests
all: $(EXEC) test

# instruct Make NOT to remove intermediate files
.SECONDARY:

# disable built-in implicit rule
%.o: %.cpp

# compile/build the product
$(EXEC): $(EXEC).o
	mv $(EXEC).o $(EXEC)

$(FLEX_DEST): $(FLEX_SRC) $(HEADERS) $(SELF)
	$(FLEX) -o$(FLEX_DEST) $(FLEX_SRC)

$(BISON_DEST): $(BISON_SRC) $(HEADERS) $(SELF)
	$(BISON) --no-lines --report=all --defines=$(SYMBOLS) --output=$(BISON_DEST) $(BISON_SRC)

# library objects, we just compile them, NO linking
%.obj: %.cpp
	$(CPP) $(CPPFLAGS) -fPIC -o $@ -g -c $<

$(LIB): $(LIB_OBJS)
	ar -r $(LIB) $(LIB_OBJS)

# test everything
test: $(TESTS)
	echo "Testing finished, everything OK"

%.test: %.o
	$<

# compilation of any other CPP file AND linking with all libs
%.o: %.cpp $(HEADERS) $(BISON_DEST) $(FLEX_DEST) $(LIB)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $@ $< $(LIB) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""

# clean everything!
clean:
	rm -f \
	$(BISON_DEST) \
	include/Scanner/rqdql.y.output \
	$(FLEX_DEST) \
	$(EXEC) \
	$(LIB_OBJS) \
	$(OBJS) \
	$(LIB) \
	$(TESTS) \
	$(SYMBOLS)

