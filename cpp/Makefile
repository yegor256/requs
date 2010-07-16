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

VERSION = 0.2

.DEFAULT_GOAL := all
MAKEFLAGS = -r
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
SVN = /usr/local/bin/svn
EXEC = rqdql
INCLUDE = include
TESTS = test
BUILD = build
DEPENDS = $(BUILD)/dependencies
LIBS = library/boost-libs library/pugixml
TEST_RUNNER = $(BUILD)/test-runner
GENERATED = $(BUILD)/generated

CPPFLAGS = -fPIC -g \
	-I $(INCLUDE) \
	-I ./library \
	$(shell xml2-config --cflags) \
	-D BOOST_TEST_DYN_LINK \
	-I $(GENERATED)/$(INCLUDE) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""
LDFLAGS = $(shell xml2-config --libs)

FLEX_SRC = $(shell find $(INCLUDE) -name "*.l")
FLEX_DEST = $(FLEX_SRC:%.l=$(GENERATED)/%.l.c)
BISON_SRC = $(shell find $(INCLUDE) -name "*.y")
BISON_DEST = $(BISON_SRC:%.y=$(GENERATED)/%.y.c)

GENERATED_SRC = $(FLEX_DEST) $(BISON_DEST)

MAIN_SRC = $(shell find $(INCLUDE) -name "*.cpp")
TEST_SRC = $(shell find $(TESTS) -name "*.cpp")
LIB_SRC = $(shell find $(LIBS) -name "*.cpp")
SOURCES = rqdql.cpp $(MAIN_SRC) $(TEST_SRC) $(LIB_SRC)

MAIN_OBJS = $(MAIN_SRC:%.cpp=$(BUILD)/%.o)
TEST_OBJS = $(TEST_SRC:%.cpp=$(BUILD)/%.o)
LIB_OBJS = $(LIB_SRC:%.cpp=$(BUILD)/%.o)
OBJS = $(MAIN_OBJS) $(TEST_OBJS) $(LIB_OBJS)

# instruct Make NOT to remove intermediate files
.SECONDARY:

# compile the product and run all tests
all: test $(EXEC) 

# build dependencies
$(DEPENDS)/%.d: %.cpp $(GENERATED_SRC)
	@set -e; rm -f $@; \
	mkdir -p $(dir $@); \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\(.*\.o\)[ :]*,$(patsubst %.cpp,$(BUILD)/%.o,$<) $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(MAIN_SRC:%.cpp=$(DEPENDS)/%.d) $(TEST_SRC:%.cpp=$(DEPENDS)/%.d)

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# compile/build the product
$(EXEC): $(OBJS) $(BUILD)/rqdql.o
	$(CPP) $(LDFLAGS) -o $(EXEC) $(BUILD)/rqdql.o $(MAIN_OBJS) $(LIB_OBJS)

$(GENERATED)/%.l.c: %.l
	@mkdir -p $(dir $@)
	$(FLEX) -o$@ $<

$(GENERATED)/%.y.c: %.y
	@mkdir -p $(dir $@)
	$(BISON) --no-lines --report=none --defines=$@-symbols.h --output=$@ $<

# test everything
test: $(TEST_RUNNER)
	./$(TEST_RUNNER) --log_level=message

$(TEST_RUNNER): $(OBJS)
	$(CPP) $(LDFLAGS) -o $(TEST_RUNNER) $(OBJS)

# clean everything!
.PHONY: clean
clean:
	-rm -rf \
	$(EXEC) \
	$(BUILD)/*
