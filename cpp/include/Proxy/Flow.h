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
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 */

#include <map>
#include <boost/shared_ptr.hpp>
#include "Solm/Formula.h"

namespace proxy {
    
/** 
 * Forward declarations
 */
class Flows;
class Signature;

/** 
 * One action-flow in a list of flows
 */
class Flow {
public:

    /** 
     * Public constructor
     */
    Flow(const std::string& t, const boost::shared_ptr<Signature>& s) : _text(t), _signature(s) { /* that's it */ }

    /** 
     * Public constructor
     */
    Flow(const std::string& t) : _text(t), _signature() { /* that's it */ }

    /** 
     * Public constructor
     */
    Flow() : _text(), _signature() { /* that's it */ }

    /** 
     * Add new alternative to the flow
     */
    boost::shared_ptr<Flows>& add(const boost::shared_ptr<solm::Formula>&);

    /** 
     * Find an alternative by an indexed char, or add it if not found
     */
    boost::shared_ptr<Flows>& find(char);

    /** 
     * Convert this flow to a user-friendly string
     */
    const std::string toString() const;

    /** 
     * Convert the flow to the SOLM formula
     */
    boost::shared_ptr<solm::Formula> makeFormula() const;

private:

    /** 
     * Public constructor
     */
    typedef std::map<boost::shared_ptr<solm::Formula>, boost::shared_ptr<Flows> > Alternatives;

    /** 
     * Textual image of the flow
     */
    std::string _text;

    /** 
     * Public constructor
     */
    boost::shared_ptr<Signature> signature;

    /** 
     * List of named alternatives
     */
    Alternatives _alternatives;

    /** 
     * get Formula which is called by this signature
     */
    boost::shared_ptr<solm::Formula>& target() const;

};

}

#endif
