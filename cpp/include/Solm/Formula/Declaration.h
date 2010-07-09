/**
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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_FORMULA_DECLARATION_H
#define __INCLUDE_SOLM_FORMULA_DECLARATION_H

#include <string>
#include "Solm/Formula/Variadic.h"
#include "Solm/Formula/Parametrized.h"

namespace solm {
    
/**
 * Forward declarations
 */
class Chain;
class Context;

/**
 * Declaration of a new predicate
 */
class Declaration : public Variadic, public Parametrized<Declaration> {
public:
    
    /**
     * Declaration of a new predicate
     */
    Declaration(const std::string&);

    /**
     * Return a ref to the name of this declaration
     */
    const std::string& name() { return _name; }

    /**
     * Change name and return it back
     */
    const std::string& name(const std::string& s) { _name = s; return name(); }

    /**
     * Convert it to the user-friendly text
     */
    virtual operator std::string() const;

    /**
     * To resolve this formula on some context
     * and produce a new Chain of Snapshots.
     */
    virtual Chain operator+(const Context&);

private:

    /**
     * Name of the predicate declared
     */
    std::string _name;
    
};

}

#endif
