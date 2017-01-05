/**
 * Copyright (c) 2009-2017, requs.org
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
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
package org.requs.exec;

import com.jcabi.manifests.Manifests;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import joptsimple.OptionParser;
import joptsimple.OptionSet;
import org.apache.commons.io.IOUtils;

/**
 * Entry point of the JAR.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @checkstyle MultipleStringLiteralsCheck (500 lines)
 * @since 1.1
 */
public final class Main {

    /**
     * Private ctor, to avoid instantiation of this class.
     */
    private Main() {
        // intentionally empty
    }

    /**
     * Entry point of the entire JAR.
     * @param args List of command-line arguments
     * @throws IOException If something goes wrong inside
     */
    public static void main(final String[] args) throws IOException {
        final OptionParser parser = new OptionParser("h*vi:o:");
        final PrintStream out = System.out;
        parser.posixlyCorrect(true);
        final OptionSet options = parser.parse(args);
        if (options.has("v")) {
            IOUtils.write(
                String.format(
                    "%s/%s",
                    Manifests.read("Requs-Version"),
                    Manifests.read("Requs-Revision")
                ),
                out
            );
        } else if (options.has("i") && options.has("o")) {
            new org.requs.Compiler(
                new File(options.valueOf("i").toString()),
                new File(options.valueOf("o").toString())
            ).compile();
        } else {
            out.println("Usage: java -jar requs-exec.jar [options]");
            out.println("where options include:\n");
            parser.printHelpOn(out);
        }
    }

}
