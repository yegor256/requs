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
 * @version $Id: Silent.h 2095 2010-05-28 07:26:19Z yegor256@yahoo.com $
 */
 
#include "Solm/Formula/Parametrized.h"

#include "boost/format.hpp"

/**
 * Get argument and validate its existense, beforehand
 */
template <typename T> const std::string& Parametrized<T>::getVar(size_t i) const {
    if (i >= vars.size()) {
        throw rqdql::Exception(
            boost::format(rqdql::_t("Var[%d] is out of range")) % i
        );
    }
    return vars[i];
}

