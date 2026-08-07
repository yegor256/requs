/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.maven;

import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import org.apache.commons.io.FileUtils;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/**
 * Test case for {@link CompileMojo}.
 * @since 1.0
 */
final class CompileMojoTest {

    /**
     * CompileMojo can compile requs sources into XML.
     * @param temp Temp directory
     * @throws Exception If fails
     */
    @Test
    void compiles(@TempDir final Path temp) throws Exception {
        final File input = temp.resolve("input").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(input, "main.req"),
            String.join(
                System.lineSeparator(),
                "",
                "User is a \"human being\".",
                "",
                "File is a \"binary object on disc\".",
                "",
                "UC1 where User validates File: \"we'll define later\".",
                ""
            ),
            StandardCharsets.UTF_8
        );
        final CompileMojo mojo = new CompileMojo();
        mojo.input = input;
        mojo.output = output;
        mojo.execute();
        MatcherAssert.assertThat(
            "CompileMojo should produce requs.xml in the output directory",
            new File(output, "requs.xml").exists(),
            Matchers.is(true)
        );
    }
}
