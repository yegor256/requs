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
INCLUDE = include
CPPFLAGS = -I$(INCLUDE) -I./library -I/usr/include/libxml2 $(shell xml2-config --cflags)
LDFLAGS = $(shell xml2-config --libs)
EXEC = rqdql
SVN = /usr/local/bin/svn
DEPENDS = dependencies.mk
TESTS = test
BUILD = build
LIBS = library/boost-libs
TEST_RUNNER = test-runner

SYMBOLS = include/Scanner/symbols.h
FLEX_SRC = include/Scanner/rqdql.l
FLEX_DEST = include/Scanner/rqdql.l.c
BISON_SRC = include/Scanner/rqdql.y
BISON_DEST = include/Scanner/rqdql.y.c

SOURCES = $(shell find $(INCLUDE) $(TESTS) $(LIBS) -name "*.cpp")
SOURCES += $(BISON_DEST)
SOURCES += $(FLEX_DEST)

# instruct Make NOT to remove intermediate files
.SECONDARY:

# disable built-in implicit rule
%.o: %.cpp

# compile the product and run all tests
all: $(DEPENDS) $(EXEC) test

# clean everything!
clean:
	rm -f \
	$(BISON_DEST) \
	include/Scanner/rqdql.y.output \
	$(FLEX_DEST) \
	$(EXEC) \
	$(OBJS) \
	$(DEPENDS) \
	$(SYMBOLS)

# compilation of all .CPP files into .O files
define oRule
DEST = $(BUILD)/$(patsubst %.cpp,%.o,$(subst /,-,$(1)))
$(DEST): $(1)
	$(CPP) $(CPPFLAGS) -fPIC -o $(DEST) -g -c $(1)
OBJS += $(DEST)
endef
$(foreach s, $(SOURCES), $(eval $(call oRule, $(s))))

# build dependencies
$(DEPENDS):
	$(CPP) $(CPPFLAGS) -M $(SOURCES) > $(DEPENDS)
	
-include $(DEPENDS)

# compile/build the product
$(EXEC): $(BISON_DEST) $(FLEX_DEST) $(OBJS)
	$(CPP) $(LDFLAGS) -o $(EXEC) $(OBJS) \
	-D RQDQL_VERSION="\"$(VERSION)$(shell $(SVN) info | grep "Revision:" | sed "s/Revision: /r/g")\""

$(FLEX_DEST): $(FLEX_SRC) $(HEADERS)
	$(FLEX) -o$(FLEX_DEST) $(FLEX_SRC)

$(BISON_DEST): $(BISON_SRC) $(HEADERS)
	$(BISON) --no-lines --report=all --defines=$(SYMBOLS) --output=$(BISON_DEST) $(BISON_SRC)

# test everything
test: $(TEST_RUNNER)
	$(TEST_RUNNER)

$(TEST_RUNNER): $(OBJS)
	$(CPP) $(LDFLAGS) -o $(TEST_RUNNER) $(OBJS)

