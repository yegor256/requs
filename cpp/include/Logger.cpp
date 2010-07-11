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
#include <vector>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/join.hpp>
#include "Logger.h"
#include "Logger/Message.h"
#include "Logger/Link.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

rqdql::Logger::Logger() : _subjects(), _links(), _messages() { 
    /* that's it */ 
}

namespace rqdql {
template<> void Logger::log(const void* s, const std::string& m) {
    using namespace std;
    vector<int> lines;
    string str = m;
    if (hasSubject(s)) {
        lines = _subjects[s];
    }
    _messages.push_back(logger::Message(lines, str));
}
}

template <typename T> void rqdql::Logger::log(const T* s, const std::string& m) {
    using namespace std;
    string str = m;
    if (!hasSubject(s)) {
        str = str + " (" + typeid(*s).name() + ")"; 
    }
    log(static_cast<const void*>(s), str);
}

void rqdql::Logger::log(int lineNo, const std::string& m) {
    using namespace std;
    vector<int> lines;
    lines.push_back(lineNo);
    _messages.push_back(logger::Message(lines, m));
}

const std::string rqdql::Logger::getReport() const {
    using namespace std;
    vector<string> msgs;
    for (vector<logger::Message>::const_iterator i = _messages.begin(); i != _messages.end(); ++i) {
        // sort them in proper order
        vector<int> lines = (*i).getLines();
        sort(lines.begin(), lines.end());
        
        // leave only unique elements
        vector<int>::const_iterator end = unique(lines.begin(), lines.end());
        
        // convert them to strings
        vector<string> lineNumbers;
        for (vector<int>::const_iterator j = lines.begin(); j != end; ++j) {
            lineNumbers.push_back((boost::format("%d") % *j).str());
        }
        
        // if no lines founds, show at least ZERO
        if (lineNumbers.empty()) {
            lineNumbers.push_back("0");
        }
        
        // create a message
        msgs.push_back((boost::format("[%s] %s") 
            % boost::algorithm::join(lineNumbers, ", ") 
            % (*i).getMessage()
        ).str());
    }
    return boost::algorithm::join(msgs, "\n");
}

const std::vector<rqdql::logger::Link>& rqdql::Logger::getLinks() {
    using namespace std;
    for (vector<logger::Link>::iterator i = _links.begin(); i != _links.end(); ++i) {
        const void* left = (*i).getLeft();
        const void* right = (*i).getRight();
        if (!hasSubject(left)) {
            throw rqdql::Exception(
                rqdql::_t("LEFT subject not found when reporting _links")
            );
        }
        if (!hasSubject(right)) {
            throw rqdql::Exception(
                rqdql::_t("RIGHT subject not found when reporting _links")
            );
        }
        (*i).setLeftLines(_subjects[left]);
        (*i).setRightLines(_subjects[right]);
    }
    return _links;
}

void rqdql::Logger::addSubject(const void* s, int l) { 
    _subjects[s].push_back(l);
}

bool rqdql::Logger::hasSubject(const void* s) const { 
    return _subjects.find(s) != _subjects.end(); 
}

void rqdql::Logger::addLink(const void* l, const void* r) { 
    // validate for duplicated _links!
    _links.push_back(logger::Link(l, r)); 
}

void rqdql::Logger::addClone(const void* existing, const void* n) {
    using namespace std;
    if (!hasSubject(existing)) {
        throw rqdql::Exception(
            rqdql::_t("EXISTING subject not found when cloning")
        );
    }
    if (!_subjects[existing].size()) {
        throw rqdql::Exception(
            rqdql::_t("No lines were reported yet for EXISTING subject")
        );
    }
    addSubject(n, *(_subjects[existing].end()-1));
}

