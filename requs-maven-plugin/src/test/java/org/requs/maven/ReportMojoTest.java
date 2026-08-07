/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.maven;

import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import org.apache.commons.io.FileUtils;
import org.apache.maven.doxia.sink.impl.SinkAdapter;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/**
 * Test case for {@link ReportMojo}.
 * @since 1.0
 */
final class ReportMojoTest {

    /**
     * ReportMojo can generate a site report.
     * @param temp Temp directory
     * @throws Exception If fails
     */
    @Test
    void generates(@TempDir final Path temp) throws Exception {
        final File source = temp.resolve("source").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(source, "main.req"),
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
        final ReportMojo mojo = new ReportMojo();
        mojo.source = source;
        mojo.output = output;
        mojo.generate(new SinkAdapter(), null, null);
        MatcherAssert.assertThat(
            "ReportMojo should produce requs.xml in the requs report directory",
            new File(new File(output, "requs"), "requs.xml").exists(),
            Matchers.is(true)
        );
    }
}
