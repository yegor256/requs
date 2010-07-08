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

#ifndef __INCLUDE_SCOPE_LOGGER_LINK_H
#define __INCLUDE_SCOPE_LOGGER_LINK_H

#include <vector>

namespace rqdql {
namespace logger {

class Link {
public:
    Link(const void* l, const void* r) : left(l), right(r) { /* that's it */ }
    const void* getLeft() const { return left; }
    const void* getRight() const { return right; }
    void setLeftLines(std::vector<int> l) { leftLines = l; }
    const std::vector<int>& getLeftLines() const { return leftLines; }
    void setRightLines(std::vector<int> l) { rightLines = l; }
    const std::vector<int>& getRightLines() const { return rightLines; }
private:
    const void* left;
    const void* right;
    std::vector<int> leftLines;
    std::vector<int> rightLines;
};

}
}

#endif
