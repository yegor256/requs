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
    vector<int> lines;
    string str = m;
    if (hasSubject(s)) {
        lines = subjects[s];
    } else {
        str = str + " (" + typeid(*s).name() + ")"; 
    }
    messages.push_back(Message(lines, str));
}

/**
 * Log one line, we know exact line number
 */
void Logger::log(int lineNo, const string& m) {
    vector<int> lines;
    lines.push_back(lineNo);
    messages.push_back(Message(lines, m));
}

/**
 * Build summary report
 */
const string Logger::getReport() const {
    vector<string> msgs;
    for (vector<Message>::const_iterator i = messages.begin(); i != messages.end(); ++i) {
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
        
        // create a message
        msgs.push_back((boost::format("[%s] %s") 
            % boost::algorithm::join(lineNumbers, ", ") 
            % (*i).getMessage()
        ).str());
    }
    return boost::algorithm::join(msgs, "\n");
}

