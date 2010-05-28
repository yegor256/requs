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

/**
 * Create an outcome of this formula, list of facts
 */
Outcome Sequence::getOutcome() const { 
    Outcome out;
    switch (operand) {
        case OP_TO:
        case OP_SEMICOLON:
        case OP_AND:
            for (Formulas::const_iterator i = getFormulas().begin(); i != getFormulas().end(); ++i) {
                out = out + (*i)->getOutcome();
            }
            break;
            
        case OP_OR:
            Outcome totalFalse;
            for (Formulas::const_iterator i = getFormulas().begin(); i != getFormulas().end(); ++i) {
                Outcome t = (*i)->getOutcome();
                if (t) {
                    out << t;
                } else {
                    totalFalse = totalFalse + t;
                }
            }
            out << totalFalse;
            break;
    }
    return out;
}

/**
 * Convert the sequence to PREDICATES in LaTeX
 */
const string Sequence::toString() const {
    vector<string> lines;
    for (Formulas::const_iterator i = getFormulas().begin(); i != getFormulas().end(); ++i) {
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
        case OP_SEMICOLON:
            separator = ";";
            break;
    }
    return "(\n\t" + boost::algorithm::replace_all_copy(
        boost::algorithm::join(lines, " " + separator + " \n"), 
        "\n", 
        "\n\t"
    ) + "\n)";
}

/**
 * Append sequence to sequence
 */
void Sequence::append(const Sequence* s) {
    for (Formulas::const_iterator i = s->getFormulas().begin(); i != s->getFormulas().end(); ++i) {
        addFormula(*i);
    }
}

#include "Solm/Formula/Sequence/And.h"
#include "Solm/Formula/Sequence/Or.h"
