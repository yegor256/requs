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

#include <string>
#include <map>
#include <boost/shared_ptr.hpp> // boost::shared_ptr<>
#include <boost/format.hpp> // boost::format()
#include <boost/algorithm/string/case_conv.hpp> // boost::algorithm::to_lower_copy()
#include <boost/algorithm/string/regex.hpp> // boost::algorithm::replace_all_regex_copy()
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Proxy/Signature.h"

void proxy::Signature::explain(const std::string& n, const boost::shared_ptr<proxy::Signature::Explanation>& e) { 
    // maybe this place is just absent?
    if (!_hasPlace(n)) {
        throw rqdql::Exception(
            boost::format("There is no place '%s' in '%s', can't explain") 
            % n 
            % _text
        );
    }
    // maybe this place is already explained?
    if (_explanations.find(n) != _explanations.end()) {
        throw rqdql::Exception(
            boost::format("The place '%s' in '%s' is already explained") 
            % n 
            % _text
        );
    }
    _explanations[n] = e;
}

bool proxy::Signature::operator==(const proxy::Signature& s) const {
    // first we simplity them both and then compare as strings
    return _simplified() == s._simplified();
}

bool proxy::Signature::isFormula() const {
    try {
        makeFormula();
    } catch (...) {
        return false;
    }
    return true;
}

boost::shared_ptr<solm::Formula> proxy::Signature::makeFormula() const {
    using namespace std;
    
    string t = _simplified();
    // if (regex_match(t, regex("\\{...\\} reads? \\{...\\}"))) {
    //     return (new Read())->arg(_getPlaceName(0))->arg(_getPlaceName(1));
    // }
    // if (regex_match(t, regex("\\{...\\} creates? \\{...\\}"))) {
    //     return (new Created())->arg(_getPlaceName(0))->arg(_getPlaceName(1));
    // }
    // if (regex_match(t, regex("\\{...\\} deletes? \\{...\\}"))) {
    //     return (new Deleted())->arg(_getPlaceName(0))->arg(_getPlaceName(1));
    // }
    // if (regex_match(t, regex("\\{...\\} updates? \\{...\\}"))) {
    //     return (new Updated())->arg(getPlaceName(0))->arg(getPlaceName(1));
    // }
    // if (regex_match(t, regex("\\{...\\} turns? into \\{...\\}"))) {
    //     return new Info("'not implemented yet: " + t);
    // }
    // if (regex_match(t, regex("failure"))) {
    //     return (new Throw())->arg("'not implemented yet");
    // }
    // if (regex_match(t, regex("if failure"))) {
    //     return (new Caught())->arg("'not implemented yet");
    // }
    throw rqdql::Exception(
        boost::format(rqdql::_t("Signature '%s' is not a formula")) % _text
    );
}

std::string proxy::Signature::_getPlaceName(size_t i) const {
    if (!_hasPlaces()) {
        throw rqdql::Exception(
            boost::format(rqdql::_t("No places found in signature '%s'")) % _text
        );
    }
    if (i >= _getPlaces().size()) {
        throw rqdql::Exception(
            boost::format(rqdql::_t("Places no.%d is absent in signature '%s'")) % i % _text
        );
    }
    return _getPlaces().at(i);
}

bool proxy::Signature::_hasPlaces() const {
    return !_getPlaces().empty();
}

bool proxy::Signature::_hasPlace(const std::string& n) const {
    std::vector<std::string> places = _getPlaces();
    return (places.end() != find(places.begin(), places.end(), n));
}

std::vector<std::string> proxy::Signature::_getPlaces() const {
    using namespace std;
    
    vector<string> places;
    string::const_iterator begin = _text.begin();
    string::const_iterator end = _text.end();
    boost::match_results<string::const_iterator> what;
    while (boost::regex_search(begin, end, what, boost::regex("\\{(.*?)\\}"))) {
        places.push_back(string(what[1].first, what[2].second-1));
        begin = what[0].second;
    }
    // for (vector<string>::const_iterator i = places.begin(); i != places.end(); ++i) {
    //     cout << *i << endl;
    // }
    // terminate();
    return places;
}

const std::string proxy::Signature::_simplified() const {
    using namespace std;
    
    typedef map<string, string> Reps;
    Reps reps;
    reps["\\{.*?\\}"] = "{...}";
    reps["[ \\t\\n\\r]+"] = " ";

    string n = boost::algorithm::to_lower_copy(_text);
    for (Reps::const_iterator i = reps.begin(); i != reps.end(); ++i) {
        n = boost::algorithm::replace_all_regex_copy(
            n, // source string
            boost::regex((*i).first), // what to find
            (*i).second // what to replace to
        );
    }
    return n;
}

