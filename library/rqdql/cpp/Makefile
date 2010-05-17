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
VERSION = 0.3.3

MAKEFLAGS = -r
SELF = Makefile
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
CPPFLAGS = -I./include -I./library
EXEC = ./rqdql
SVN = /usr/local/bin/svn

SYMBOLS = include/Scanner/symbols.h
FLEX_SRC = include/Scanner/rqdql.l
FLEX_DEST = include/Scanner/rqdql.l.c
BISON_SRC = include/Scanner/rqdql.y
BISON_DEST = include/Scanner/rqdql.y.c

LIB_DIRS = library/pugixml library/boost-libs
LIB_SOURCES = $(shell find $(LIB_DIRS) -name "*.cpp")
LIB_OBJS := $(LIB_SOURCES:.cpp=.obj)

HEADERS := $(shell find include -name "*.h")

TEST_SOURCES := $(shell find test -name "*.cpp")
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
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# test everything
test: $(TESTS)

%.test: %.o
	$<

# compilation of unit tests and any other CPP file AND linking with all libs
%.o: %.cpp $(HEADERS) $(BISON_DEST) $(FLEX_DEST) $(LIB_OBJS)
	$(CPP) $(CPPFLAGS) -o $@ $< $(LIB_OBJS) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""

# clean everything!
clean:
	rm -f \
	$(BISON_DEST) \
	include/Scanner/rqdql.y.output \
	$(FLEX_DEST) \
	$(EXEC) \
	$(LIB_OBJS) \
	$(TESTS) \
	$(SYMBOLS)

