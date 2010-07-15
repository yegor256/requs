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
DEPENDS = $(BUILD)/dependencies.mk
LIBS = library/boost-libs library/pugixml
TEST_RUNNER = $(BUILD)/test-runner
GENERATED = $(BUILD)/generated

CPPFLAGS = -fPIC -g -I$(INCLUDE) \
	-I./library $(shell xml2-config --cflags) \
	-D BOOST_TEST_DYN_LINK \
	-D RQDQL_GENERATED_DIR=$(GENERATED) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""
LDFLAGS = $(shell xml2-config --libs)

FLEX_SRC = $(shell find $(INCLUDE) -name "*.l")
FLEX_DEST = $(FLEX_SRC:%.l=$(GENERATED)/%.l.c)
BISON_SRC = $(shell find $(INCLUDE) -name "*.y")
BISON_DEST = $(BISON_SRC:%.y=$(GENERATED)/%.y.c)

MAIN_SRC = $(shell find $(INCLUDE) -name "*.cpp")
TEST_SRC = $(shell find $(TESTS) -name "*.cpp")
LIB_SRC = $(shell find $(LIBS) -name "*.cpp")
SOURCES = rqdql.cpp
SOURCES += $(MAIN_SRC)
SOURCES += $(TEST_SRC)
SOURCES += $(LIB_SRC)

MAIN_OBJS = $(MAIN_SRC:%.cpp=$(BUILD)/%.o)
TEST_OBJS = $(TEST_SRC:%.cpp=$(BUILD)/%.o)
LIB_OBJS = $(LIB_SRC:%.cpp=$(BUILD)/%.o)
OBJS = $(MAIN_OBJS)
OBJS += $(TEST_OBJS)
OBJS += $(LIB_OBJS)

# disable implicit rules
%.o: %.cpp

# instruct Make NOT to remove intermediate files
.SECONDARY:

# compile the product and run all tests
all: $(DEPENDS) test $(EXEC) 

# build dependencies
$(DEPENDS): $(BISON_DEST) $(FLEX_DEST) $(SOURCES)
	$(CPP) $(CPPFLAGS) -M $(MAIN_SRC) $(BISON_DEST) $(FLEX_DEST) > $(DEPENDS)	
	
-include $(DEPENDS)

$(BUILD)/%.o: %.cpp $(FLEX_DEST) $(BISON_DEST)
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# compile/build the product
$(EXEC): $(OBJS) $(BUILD)/rqdql.o
	$(CPP) $(LDFLAGS) -o $(EXEC) $(BUILD)/rqdql.o $(MAIN_OBJS) $(LIB_OBJS)

%.l.c: %.l
	$(FLEX) -o$@ $<

%.y.c: %.y
	mkdir -p $(dir $(GENERATED)/$@)
	$(BISON) --no-lines --report=none --defines=$(GENERATED)/$@-symbols.h --output=$@ $<

# test everything
test: $(TEST_RUNNER)
	./$(TEST_RUNNER) --log_level=message

$(TEST_RUNNER): $(OBJS)
	$(CPP) $(LDFLAGS) -o $(TEST_RUNNER) $(OBJS)

# clean everything!
clean:
	rm -rf \
	$(EXEC) \
	$(BUILD)/*
