/**
 * Copyright (c) 2009-2013, RQDQL.com
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

import com.jcabi.manifests.Manifests;

/**
 * Dispatcher of CLI request.
 *
 * <p>The class is instantiated in
 * {@link Main}, in order to dispatch command line interface
 * request and return an output string to be rendered to
 * the requester.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @see Main
 */
final class Dispatcher {

    /**
     * Entry point of the entire JAR.
     * @param args List of command-line arguments
     * @param input Incoming RQDQL stream
     * @return XML produced
     * @see Main#main(String[])
     */
    public String dispatch(final String[] args, final String input) {
        final XmlSummary summary = new XmlSummary(input);
        String output = null;
        for (String arg : args) {
            if (arg.charAt(0) == '-') {
                output = this.option(arg);
                break;
            }
        }
        if (output == null) {
            output = summary.xml();
        }
        return output;
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
            // @checkstyle StringLiteralsConcatenation (5 lines)
            out = "usage: java -jar rqdql-bin.jar [-?v] [reports...]\n"
                + "Options:\n"
                + "  -?\tShows this help message\n"
                + "  -v\tReturns current version of the product\n"
                + "Report bugs to <bugs@rqdql.com>";
        } else if ("-v".equals(arg)) {
            out = Manifests.read("RQDQL-Version");
        } else {
            throw new IllegalArgumentException(
                String.format("Unknown option: %s", arg)
            );
        }
        return out;
    }

}
