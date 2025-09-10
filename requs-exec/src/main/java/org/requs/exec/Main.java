/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.exec;

import com.jcabi.manifests.Manifests;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import joptsimple.OptionParser;
import joptsimple.OptionSet;
import org.apache.commons.io.IOUtils;

/**
 * Entry point of the JAR.
 *
 * @since 1.1
 * @checkstyle MultipleStringLiteralsCheck (500 lines)
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
    @SuppressWarnings({"PMD.ProhibitPublicStaticMethods", "PMD.CloseResource"})
    public static void main(final String... args) throws IOException {
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
                out,
                StandardCharsets.UTF_8
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
