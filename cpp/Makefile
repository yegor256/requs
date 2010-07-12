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

VERSION = 0.6.1

MAKEFLAGS = -r
SELF = Makefile
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
SVN = /usr/local/bin/svn
CPPFLAGS = -fPIC -g -I$(INCLUDE) -I./library -I/usr/include/libxml2 $(shell xml2-config --cflags) -DBOOST_TEST_DYN_LINK
LDFLAGS = $(shell xml2-config --libs)

EXEC = rqdql
DEPENDS = dependencies.mk
INCLUDE = include
TESTS = test
BUILD = build
LIBS = library/boost-libs library/pugixml
TEST_RUNNER = test-runner

SYMBOLS = include/Scanner/symbols.h
FLEX_SRC = include/Scanner/rqdql.l
FLEX_DEST = include/Scanner/rqdql.l.c
BISON_SRC = include/Scanner/rqdql.y
BISON_DEST = include/Scanner/rqdql.y.c

SOURCES = $(shell find $(INCLUDE) $(TESTS) $(LIBS) -name "*.cpp")
OBJS = $(SOURCES:%.cpp=$(BUILD)/%.o)

# disable implicit rules
%.o: %.cpp

# instruct Make NOT to remove intermediate files
.SECONDARY:

# compile the product and run all tests
all: depends $(EXEC) test

# build dependencies
depends: $(SELF) $(BISON_DEST) $(FLEX_DEST)
	$(CPP) $(CPPFLAGS) -M $(SOURCES) $(BISON_DEST) $(FLEX_DEST) > $(DEPENDS)	
-include $(DEPENDS)

$(BUILD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# compile/build the product
$(EXEC): $(BISON_DEST) $(FLEX_DEST) $(OBJS)
	$(CPP) $(LDFLAGS) -o $(EXEC) $(OBJS) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""

$(SYMBOLS): $(FLEX_DEST) $(BISON_DEST)

$(FLEX_DEST): $(FLEX_SRC)
	$(FLEX) -o$(FLEX_DEST) $(FLEX_SRC)

$(BISON_DEST): $(BISON_SRC) $(FLEX_DEST)
	$(BISON) --no-lines --report=all --defines=$(SYMBOLS) --output=$(BISON_DEST) $(BISON_SRC)

# test everything
test: $(TEST_RUNNER)
	$(TEST_RUNNER)

$(TEST_RUNNER): $(OBJS)
	$(CPP) $(LDFLAGS) -o $(TEST_RUNNER) $(OBJS)

# clean everything!
clean:
	rm -f \
	$(BISON_DEST) \
	include/Scanner/rqdql.y.output \
	$(FLEX_DEST) \
	$(EXEC) \
	$(BUILD)/* \
	$(OBJS) \
	$(DEPENDS) \
	$(SYMBOLS)
