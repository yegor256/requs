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
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/join.hpp> // join()
#include <boost/algorithm/string/replace.hpp> // replace_all_copy()
#include "Solm/Formula/Variadic.h"
#include "Solm/Chain.h"
#include "Solm/Context.h"

solm::Variadic::Variadic(solm::Variadic::Operand op) : 
    solm::Formula(), _operand(op), _formulas() { 
    /* that's it */ 
}

solm::Variadic& solm::Variadic::operator+=(const boost::shared_ptr<solm::Formula>& f) {
    _formulas.push_back(f);
    return *this;
}

solm::Variadic& solm::Variadic::operator+=(const solm::Variadic& s) {
    for (Formulas::const_iterator i = s._formulas.begin(); i != s._formulas.end(); ++i) {
        _formulas.push_back(*i);
    }
    return *this;
}

solm::Chain solm::Variadic::operator+(const solm::Context& ctx) const {
    Chain c;
    // switch (_operand) {
    //     /**
    //      * We should align all formulas in a long VERTICAL list
    //      * of facts. We do it by means of Outcome::operator+().
    //      */
    //     case OP_TO:
    //     case OP_SEMICOLON:
    //     case OP_AND:
    //         for (Formulas::const_iterator i = _formulas.begin(); i != _formulas.end(); ++i) {
    //             // if the outcome is FALSE already, we can't add any more
    //             // formulas to it, we just give up and return it as is
    //             if (!c) {
    //                 break;
    //             }
    //             c = c + (*i + (Context)c);
    //         }
    //         break;
    //         
    //     /**
    //      * Positive final of any formula, or a total false final of
    //      * all formulas together.
    //      * @todo make sure it works, I'm not sure for now... :(
    //      */
    //     case OP_OR:
    //         Chain totalFalse;
    //         for (Formulas::const_iterator i = _formulas.begin(); i != _formulas.end(); ++i) {
    //             Chain t = (*i + (Context)c);
    //             if (t) {
    //                 c << t;
    //             } else {
    //                 totalFalse = totalFalse + t;
    //             }
    //         }
    //         c << totalFalse;
    //         break;
    // }
    return c;
}

solm::Variadic::operator std::string() const {
    // using namespace std;
    // 
    // vector<string> lines;
    // for (Formulas::const_iterator i = _formulas.begin(); i != _formulas.end(); ++i) {
    //     lines.push_back((string)*i);
    // }
    // string separator;
    // switch (operand) {
    //     case OP_AND:
    //         separator = "\\vee";
    //         break;
    //     case OP_OR:
    //         separator = "\\wedge";
    //         break;
    //     case OP_TO:
    //         separator = "\\to";
    //         break;
    //     case OP_SEMICOLON:
    //         separator = ";";
    //         break;
    // }
    // return "(\n\t" + boost::algorithm::replace_all_copy(
    //     boost::algorithm::join(lines, " " + separator + " \n"), 
    //     "\n", 
    //     "\n\t"
    // ) + "\n)";
    return "stub";
}


