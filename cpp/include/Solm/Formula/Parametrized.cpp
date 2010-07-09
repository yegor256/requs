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
 * @version $Id$
 */
 
#include <string>
#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join()
#include "Solm/Formula/Parametrized.h"

template <typename T> const std::string& solm::Parametrized<T>::arg(size_t i = 0) const {
    if (i >= _arguments.size()) {
        throw rqdql::Exception(
            boost::format(rqdql::_t("Var[%d] is out of range")) % i
        );
    }
    return _arguments[i];
}

solm::Declaration::operator std::string() const { 
    return boost::algorithm::join(_arguments, ", ");
}
