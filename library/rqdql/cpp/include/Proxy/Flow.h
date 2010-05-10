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

Flows* Flow::addAlternative(solm::Formula* f) { 
    return alternatives[f] = new Flows; 
}

const string Flow::toString() const {
    string str = text;
    for (map<solm::Formula*, Flows*>::const_iterator i = alternatives.begin(); i != alternatives.end(); ++i) {
        str = str + "\n\tIf ...\n\t\t" + boost::algorithm::replace_all_copy((*i).second->toString(), "\n", "\n\t\t");
    }
    return str;
}

solm::Formula* Flow::makeFormula() const {
    return new solm::Formula();
}

