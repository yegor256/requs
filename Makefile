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

CPP = c++
BISON = bison
FLEX = flex
CPPFLAGS = -I./include 
OBJS = src/Scope.o
HEADERS = include/Scope.h

rqdql: rqdql.l rqdql.y $(OBJS)
	$(BISON) -d $@.y
	$(FLEX) $@.l
	$(CPP) $(CPPFLAGS) -o $@ $@.tab.c lex.yy.c $(OBJS) -lfl
    
%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean:
	rm lex.yy.c rqdql.tab.c rqdql.tab.h
	rm $(OBJS)
