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
 *
 * This file is included ONLY from Proxy.h
 */

/**
 * Simplify the signature before matching
 * @see match()
 */
const string Signature::simplify(const string& s) const {
    using namespace boost::algorithm;
    string n = replace_regex_copy(
        s, // source string
        boost::regex("\\{.*?\\}"), // what to find
        string("{...}") // what to replace to
    );
    n = to_lower_copy(n);
    return n;
}

/**
 * Compare two signatures and match them. Returns TRUE if
 * two signatures look identical or very similar.
 */
bool Signature::match(const Signature* s) const {
    return simplify(text) == simplify(s->text);
}

/**
 * Convert one explanation to string
 */
const string Signature::Explanation::toString() const {
    if (type) {
        return type->getName();
    }
    if (!slot.empty() && !object.empty()) {
        return slot + " (the " + object + ")"; 
    }
    return "itself"; 
}

