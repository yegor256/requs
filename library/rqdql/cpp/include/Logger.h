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

#ifndef __INCLUDE_SCOPE_LOGGER_H
#define __INCLUDE_SCOPE_LOGGER_H

#include <vector>
#include <map>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/join.hpp>
using namespace std;

namespace rqdql {
class Logger {
public:
    class Message {
    public:
        Message(const vector<int>& v, const string& m) : lines(v), message(m) { /* that's it */ }
        const vector<int>& getLines() const { return lines; }
        const string& getMessage() const { return message; }
    private:
        vector<int> lines;
        string message;
    };
    class Link {
    public:
        Link(const void* l, const void* r) : left(l), right(r) { /* that's it */ }
        const void* getLeft() const { return left; }
        const void* getRight() const { return right; }
        void setLeftLines(vector<int> l) { leftLines = l; }
        const vector<int>& getLeftLines() const { return leftLines; }
        void setRightLines(vector<int> l) { rightLines = l; }
        const vector<int>& getRightLines() const { return rightLines; }
    private:
        const void* left;
        const void* right;
        vector<int> leftLines;
        vector<int> rightLines;
    };
    Logger() : messages() { /* that's it */ }
    void addSubject(const void*, int);
    void addClone(const void*, const void*);
    bool hasSubject(const void*) const;
    void addLink(const void*, const void*);
    template <typename T> void log(const T*, const string&); // we know a link to an object
    void log(int, const string&); // we know exact line number
    bool empty() const { return messages.empty(); }
    const string getReport() const;
    const vector<int>& getLinesFor(const void* s) { return subjects[s]; }
    const vector<Message>& getMessages() const { return messages; }
    const vector<Link>& getLinks();
    void clear() { messages.clear(); }
    size_t size() const { return messages.size(); }
private:
    typedef map<const void*, vector<int> > Subjects;
    Subjects subjects;
    vector<Link> links;
    vector<Message> messages;
};

#include "Logger/LoggerImpl.h"

}

#endif
