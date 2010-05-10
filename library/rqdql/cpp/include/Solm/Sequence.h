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
 */

const string Sequence::toString() const {
    vector<string> lines;
    for (vector<Formula*>::const_iterator i = subs.begin(); i != subs.end(); ++i) {
        lines.push_back((*i)->toString());
    }
    string separator;
    switch (operand) {
        case OP_AND:
            separator = "\\vee";
            break;
        case OP_OR:
            separator = "\\wedge";
            break;
        case OP_TO:
            separator = "\\to";
            break;
    }
    return "(\n\t" + boost::algorithm::replace_all_copy(
        boost::algorithm::join(lines, " " + separator + " \n"), 
        "\n", 
        "\n\t"
    ) + "\n)";
}

