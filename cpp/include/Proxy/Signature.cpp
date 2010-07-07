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
#include <map>
#include <boost/shared_ptr.hpp> // boost::shared_ptr<>
#include <boost/format.hpp> // boost::format()
#include <boost/algorithm/string/case_conv.hpp> // boost::algorithm::to_lower_copy()
#include <boost/algorithm/string/regex.hpp> // boost::algorithm::replace_all_regex_copy()
#include "rqdql.h"
#include "rqdql/Exception.h"
#include "Proxy/Signature.h"

proxy::Signature(const std::string& t) : _text(), _places() {
    using namespace std;
    
    /**
     * To find all places in the signature
     */
    string::const_iterator begin = _text.begin();
    string::const_iterator end = _text.end();
    boost::match_results<string::const_iterator> what;
    while (boost::regex_search(begin, end, what, boost::regex("\\{(.*?)\\}"))) {
        _places[string(what[1].first, what[2].second-1)] = Place();
        begin = what[0].second;
    }

    /**
     * To simplify the signature to leave just placeholders inside,
     * for example this signature will be converted like that:
     * "{ActorUser} reads {files}" -> "{...} reads {...}"
     */
    typedef map<string, string> Replacers;
    Replacers replacers;
    replacers["\\{.*?\\}"] = "{...}";
    replacers["[ \\t\\n\\r]+"] = " ";
    _text = boost::algorithm::to_lower_copy(s);
    for (Replacers::const_iterator i = reps.begin(); i != reps.end(); ++i) {
        _text = boost::algorithm::replace_all_regex_copy(
            _text, // source string
            boost::regex((*i).first), // what to find
            (*i).second // what to replace to
        );
    }
}

size_t proxy::Signature::size() const {
    return _places.size();
}

Place& proxy::Signature::place(const std::string& n) { 
    /**
     * Maybe this place is just absent?
     */
    if (!_places.find(n) == _places.end()) {
        throw exAbsentPlace(
            boost::format("There is no place '%s' in '%s'") 
            % n 
            % _text
        );
    }
    return _places.find(n);
}

bool proxy::Signature::operator==(const proxy::Signature& s) const {
    return _text == s._text;
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
