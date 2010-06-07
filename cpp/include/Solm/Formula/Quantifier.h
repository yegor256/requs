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
 * @version $Id: Solm.h 1811 2010-05-10 14:36:27Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Solm.h
 */

template <typename T> const string Quantifier<T>::_toString(const string& t) const {
    if (Unary<T>::getFormulas().size() != 1) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            rqdql::_t("Quantifier shall have exactly one formula inside")
        );
        return "TRUE";
    }
    return t + " " 
    + boost::algorithm::join(Parametrized<T>::getVars(), ", ") 
    + "(" + Unary<T>::getFormula()->toString() + ")";
}

#include "Solm/Formula/Quantifier/Exists.h"
