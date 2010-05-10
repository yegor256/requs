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
#include <boost/algorithm/string/join.hpp>>
using namespace std;

namespace rqdql {

class Logger {
public:
    static Logger& getInstance();
    void addSubject(void* s, int l) { subjects[s] = l; };
    bool hasSubject(void* s) { return subjects.find(s) != subjects.end(); };
    void log(void* s, const string& m);
    bool empty() const { return messages.empty(); }
    const string getReport() const;
private:
    class Message {
    public:
        Message(int l, const string& m) : lineNo(l), message(m) { /* that's it */ }
        const int getLineNo() const { return lineNo; }
        const string getMessage() const { return message; }
    private:
        int lineNo;
        string message;
    };
    map<void*, int> subjects;
    vector<Message> messages;
    Logger() : messages() { /* that's it */ }
};

/**
 * This is a singleton pattern. In order to get an instance
 * of this class you should call getInstance()
 */
Logger& Logger::getInstance() {
    static Logger* logger;
    if (!logger) {
        logger = new Logger();
    }
    return *logger;
}

/**
 * Log one line
 */
void Logger::log(void* s, const string& m) {
    int lineNo;
    if (hasSubject(s)) {
        lineNo = subjects[s];
    } else {
        lineNo = 1;
    }
    messages.push_back(Message(lineNo, m));
}

/**
 * Build summary report
 */
const string Logger::getReport() const {
    vector<string> lines;
    for (vector<Message>::const_iterator i = messages.begin(); i != messages.end(); ++i) {
        lines.push_back((boost::format("[%d] %s") % (*i).getLineNo() % (*i).getMessage()).str());
    }
    return boost::algorithm::join(lines, "\n");
}

}

#endif