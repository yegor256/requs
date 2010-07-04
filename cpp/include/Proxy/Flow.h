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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#include <map>
#include "Solm/Formula.h"

namespace proxy {
    
/** 
 * Forward declarations
 */
class Flows;
class Signature;

class Flow {
public:
    Flow(const std::string& t, Signature* s) : text(t), signature(s) { /* that's it */ }
    Flow(const std::string& t) : text(t), signature(0) { /* that's it */ }
    Flow() : text(), signature(0) { /* that's it */ }
    Flows* addAlternative(solm::Formula*);
    Flows* findAlternative(char); // find alternative by letter or add it if not found
    const std::string toString() const;
    solm::Formula* makeFormula() const;
private:
    typedef std::map<solm::Formula*, Flows*> Alternatives;
    std::string text;
    Signature* signature;
    Alternatives alternatives;
    solm::Formula* getTarget() const; // get Formula which is called by this signature
};

}

#endif
