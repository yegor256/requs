/**
 *

 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

/**
 * Creates a new slot when all params are provided
 */
Slot::Slot(const string& n, const Cardinality& c, solm::Formula* f, Type* t) :
    name(n), cardinality(c), formula(f), type(t) {
    /* nothing for now */
}

/**
 * Creates a new slot with just one name provided
 */
Slot::Slot(const string& n) :
    name(n), 
    cardinality("1..n -> 1"), 
    formula(new solm::Constant(true)), 
    type(new Type())
{
    /* nothing for now */
}

