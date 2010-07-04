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
 * @version $Id: Solm.h 1811 2010-05-10 14:36:27Z yegor256@yahoo.com $
 *
 * This file is included ONLY from Solm.h
 */

const string Math::toString() const {
    if (getVars().size() != 2) {
        rqdql::get<rqdql::Logger>().log(
            this, 
            (boost::format(rqdql::_t("MATH('%s') primitive shall have exactly two arguments")) % operand).str()
        );
        return "TRUE";
    }
    return getVars().at(0) + " " + operand + " " + getVars().at(1);
}
