/**
 * Copyright (c) 2009-2011, RQDQL.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the RQDQL.com nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package com.rqdql.cli;

// processor
import com.rqdql.reporter.XmlSummary;

/**
 * Dispatcher of CLI request. The class is instantiated in
 * {@link Main}, in order to dispatch command line interface
 * request and return an output string to be rendered to
 * the requester.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 * @see Main
 */
public final class Dispatcher {

    /**
     * Entry point of the entire JAR.
     * @param args List of command-line arguments
     * @param input Incoming RQDQL stream
     * @return XML produced
     * @see Main#main(String[])
     */
    public String dispatch(final String[] args, final String input) {
        final XmlSummary summary = new XmlSummary(input);
        for (String arg : args) {
            if (arg.charAt(0) == '-') {
                return this.option(arg);
            } else {
                // add new report to the summary
            }
        }
        return summary.xml();
    }

    /**
     * Parse the argument and return output.
     * @param arg The argument
     * @return Output
     * @see #dispatch(String[], String)
     */
    private String option(final String arg) {
        String out;
        if ("-?".equals(arg)) {
            out = "usage: java -jar rqdql-bin.jar [-?v] [reports...]\n"
                + "Options:\n"
                + "  -?\tShows this help message\n"
                + "  -v\tReturns current version of the product\n"
                + "Report bugs to <bugs@rqdql.com>";
        } else if ("-v".equals(arg)) {
            out = this.version();
        } else {
            throw new IllegalArgumentException("Unknown option: " + arg);
        }
        return out;
    }

    /**
     * Get current version of the package.
     * @return The version of the package
     * @see #option(String)
     * @todo #3! This is just a stub for now and has to be
     *           refactored in order to implement properly. We
     *           should grab version number from JAR MANIFEST.MF file,
     *           where it is stored by buildnumber-maven-plugin during
     *           packaging of the JAR.
     */
    private String version() {
        return "2.0";
    }

}
