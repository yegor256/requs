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
 *
 * This file has to be included ONLY from Analytics.h
 */

/**
 * Show it as string
 */
// const string TestCase::toString() const {
//     vector<string> lines;
//     for (vector<TestCase*>::const_iterator i = predecessors.begin(); i != predecessors.end(); ++i) {
//         lines.push_back("gain success in " + (*i)->getName());
//     }
//     lines.push_back(after.toString());
//     return boost::algorithm::join(lines, "\n");
// }

/**
 * Parse the fact path and produce the MOF
 * @todo Implement it, it's a stub now
 */
const string TestCase::getXmi() const {
    // initialize the libraries (I don't know what is it for...)
    // OMF::init();
    // Model::init();
    
    // create new model to fill with data
    OMF::Model model;

    // create new UML class to add
    UML::Class p;
    
    // add this element to the model
    model.addElement(&p);
    
    OMF::XmiWriter writer;
    writer.write(&model, "-");
    return "...";
}
