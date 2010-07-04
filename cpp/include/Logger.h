/**
 * * RQDQL.com, Requirements Definition and Query Language
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

#ifndef __INCLUDE_SCOPE_LOGGER_H
#define __INCLUDE_SCOPE_LOGGER_H

#include <vector>
#include <map>
#include <string>

namespace rqdql {

class Logger {
public:
    
    class Message {
    public:
        Message(const std::vector<int>& v, const std::string& m) : lines(v), message(m) { /* that's it */ }
        const std::vector<int>& getLines() const { return lines; }
        const std::string& getMessage() const { return message; }
    private:
        std::vector<int> lines;
        std::string message;
    };
    
    class Link {
    public:
        Link(const void* l, const void* r) : left(l), right(r) { /* that's it */ }
        const void* getLeft() const { return left; }
        const void* getRight() const { return right; }
        void setLeftLines(std::vector<int> l) { leftLines = l; }
        const std::vector<int>& getLeftLines() const { return leftLines; }
        void setRightLines(std::vector<int> l) { rightLines = l; }
        const std::vector<int>& getRightLines() const { return rightLines; }
    private:
        const void* left;
        const void* right;
        std::vector<int> leftLines;
        std::vector<int> rightLines;
    };
    Logger() : messages() { /* that's it */ }
    void addSubject(const void*, int);
    void addClone(const void*, const void*);
    bool hasSubject(const void*) const;
    void addLink(const void*, const void*);
    template <typename T> void log(const T*, const std::string&); // we know a link to an object
    void log(int, const std::string&); // we know exact line number
    bool empty() const { return messages.empty(); }
    const std::string getReport() const;
    const std::vector<int>& getLinesFor(const void* s) { return subjects[s]; }
    const std::vector<Message>& getMessages() const { return messages; }
    const std::vector<Link>& getLinks();
    void clear() { messages.clear(); }
    size_t size() const { return messages.size(); }
private:
    typedef std::map<const void*, std::vector<int> > Subjects;
    Subjects subjects;
    std::vector<Link> links;
    std::vector<Message> messages;
};

}

#endif
