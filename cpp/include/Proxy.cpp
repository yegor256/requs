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
 *
 * This file is included ONLY from Proxy.h
 */

#include <vector>
#include <map>
#include <typeinfo>
#include <boost/format.hpp>
#include "Proxy.h"
#include "Proxy/Entity.h"
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Solm.h"
#include "Solm/Formula/Declaration.h"
#include "Logger.h"

proxy::Proxy::Proxy() : _entities() {
}

void proxy::Proxy::inject() {
    /**
     * We inject all entities, converting them into definitions
     * of new functions (declarations)
     */
    for (Entities::const_iterator i = _entities.begin(); i != _entities.end(); ++i) {
        /**
         * Convert the entity found into solm::Declaration, without
         * a name for now. Type casting is happening here.
         */
        solm::Declaration d = (solm::Declaration)(*(i->second));
        /**
         * Setting the name of the declaration
         */
        d.name(i->first);
        /** 
         * Now we're adding this declaration to SOLM
         */
        rqdql::get<solm::Solm>() += d;
    }
}

template<typename T> const std::vector<std::string> proxy::Proxy::names() const {
    using namespace std;
    vector<string> v;
    for (Entities::const_iterator i = _entities.begin(); i != _entities.end(); ++i) {
        // if (type_info(T) == type_info(i->second)) {
            v.push_back(i->first);
        // }
    }
    return v;
}

boost::shared_ptr<proxy::Entity>& proxy::Proxy::entity(const std::string& n) {
    if (_entities.find(n) == _entities.end()) {
        throw rqdql::Exception(
            boost::format(rqdql::_t("Entity '%s' not found in Proxy")) % n
        );
    }
    return _entities.find(n)->second;
}

const std::string& proxy::Proxy::find(const boost::shared_ptr<Entity>& e) const {
    for (Entities::const_iterator i = _entities.begin(); i != _entities.end(); ++i) {
        if (i->second == e) {
            return i->first;
        }
    }
    throw rqdql::Exception(
        rqdql::_t("The entity doesn't have a system-wide name")
    );
}

