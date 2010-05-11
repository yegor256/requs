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
 * @version $Id$
 *
 * This file is included ONLY from Logger.h
 */

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
template <typename T> void Logger::log(const T* s, const string& m) {
    int lineNo;
    string str = m;
    if (hasSubject(s)) {
        lineNo = subjects[s];
    } else {
        lineNo = 0;
        str = str + " (" + typeid(*s).name() + ")"; 
    }
    messages.push_back(Message(lineNo, str));
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

