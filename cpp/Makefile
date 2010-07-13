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
PATH := $(PATH):/usr/local/bin:/usr/bin
CPP = c++
BISON = bison
FLEX = flex
SVN = /usr/local/bin/svn
CPPFLAGS = -fPIC -g -I$(INCLUDE) \
	-I./library $(shell xml2-config --cflags) \
	-DBOOST_TEST_DYN_LINK \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""
LDFLAGS = $(shell xml2-config --libs)

EXEC = rqdql
DEPENDS = $(BUILD)/dependencies.mk
INCLUDE = include
TESTS = test
BUILD = build
LIBS = library/boost-libs library/pugixml
TEST_RUNNER = $(BUILD)/test-runner

SYMBOLS = include/Scanner/symbols.h
FLEX_SRC = include/Scanner/rqdql.l
FLEX_DEST = include/Scanner/rqdql.l.c
BISON_SRC = include/Scanner/rqdql.y
BISON_DEST = include/Scanner/rqdql.y.c

MAIN_SOURCES = $(shell find $(INCLUDE) -name "*.cpp")
TEST_SOURCES = $(shell find $(TESTS) -name "*.cpp")
LIB_SOURCES = $(shell find $(LIBS) -name "*.cpp")
SOURCES = rqdql.cpp
SOURCES += $(MAIN_SOURCES)
SOURCES += $(TEST_SOURCES)
SOURCES += $(LIB_SOURCES)

MAIN_OBJS = $(MAIN_SOURCES:%.cpp=$(BUILD)/%.o)
TEST_OBJS = $(TEST_SOURCES:%.cpp=$(BUILD)/%.o)
LIB_OBJS = $(LIB_SOURCES:%.cpp=$(BUILD)/%.o)
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
$(DEPENDS): $(BISON_DEST) $(FLEX_DEST) $(MAIN_SOURCES)
	$(CPP) $(CPPFLAGS) -M $(MAIN_SOURCES) $(BISON_DEST) $(FLEX_DEST) > $(DEPENDS)	
	
-include $(DEPENDS)

$(BUILD)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

# compile/build the product
$(EXEC): $(OBJS) $(BUILD)/rqdql.o
	$(CPP) $(LDFLAGS) -o $(EXEC) $(BUILD)/rqdql.o $(MAIN_OBJS) $(LIB_OBJS)

$(SYMBOLS): $(FLEX_DEST) $(BISON_DEST)

$(FLEX_DEST): $(FLEX_SRC)
	$(FLEX) -o$(FLEX_DEST) $(FLEX_SRC)

$(BISON_DEST): $(BISON_SRC) $(FLEX_DEST)
	$(BISON) --no-lines --report=all --defines=$(SYMBOLS) --output=$(BISON_DEST) $(BISON_SRC)

# test everything
test: $(TEST_RUNNER)
	./$(TEST_RUNNER) --log_level=message

$(TEST_RUNNER): $(OBJS)
	$(CPP) $(LDFLAGS) -o $(TEST_RUNNER) $(OBJS)

# clean everything!
clean:
	rm -rf \
	$(BISON_DEST) \
	include/Scanner/rqdql.y.output \
	$(FLEX_DEST) \
	$(EXEC) \
	$(BUILD)/* \
	$(OBJS) \
	$(DEPENDS) \
	$(SYMBOLS)
