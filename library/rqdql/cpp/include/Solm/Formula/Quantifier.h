/**
 *
 * FaZend.com, Fully Automated Zend Framework
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * FaZend.com. located at www.fazend.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#ifndef __INCLUDE_SOLM_FORMULA_QUANTIFIER_H
#define __INCLUDE_SOLM_FORMULA_QUANTIFIER_H

#include <string>
#include "Solm/Formula/Unary.h"
#include "Solm/Formula/Parametrized.h"

namespace solm {

template <typename T> class Quantifier : public Unary<T>, public Parametrized<T> {
public:
    const std::string _toString(const std::string& t) const;
};

}

#endif
