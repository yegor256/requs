/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.exec;

import com.jcabi.matchers.XhtmlMatchers;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import org.apache.commons.io.FileUtils;
import org.apache.log4j.PropertyConfigurator;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/**
 * Test case for {@link Main}.
 * @since 1.1
 */
final class MainTest {

    @Test
    void displaysVersionNumber() throws IOException {
        MatcherAssert.assertThat(
            "Output should contain version number",
            MainTest.captured(() -> Main.main("-v")),
            Matchers.containsString("-SNAPSHOT")
        );
    }

    @Test
    void rendersHelpMessage() throws IOException {
        MatcherAssert.assertThat(
            "Output should contain help message",
            MainTest.captured(() -> Main.main("-h")),
            Matchers.containsString("Usage:")
        );
    }

    @Test
    void compilesRequsSourcesAndReportsSuccess(@TempDir final Path temp)
        throws IOException {
        final File input = temp.resolve("input").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(input, "employee.req"),
            "Employee is a \"user of the system\".",
            StandardCharsets.UTF_8
        );
        MatcherAssert.assertThat(
            "Output should indicate successful compilation",
            MainTest.captured(
                () -> Main.main(
                    "-i", input.getAbsolutePath(),
                    "-o", output.getAbsolutePath()
                )
            ),
            Matchers.containsString("compiled and saved to")
        );
    }

    @Test
    void compilesRequsSourcesIntoValidXml(@TempDir final Path temp)
        throws IOException {
        final File input = temp.resolve("input").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(input, "employee.req"),
            "Employee is a \"user of the system\".",
            StandardCharsets.UTF_8
        );
        MainTest.captured(
            () -> Main.main(
                "-i", input.getAbsolutePath(),
                "-o", output.getAbsolutePath()
            )
        );
        MatcherAssert.assertThat(
            "Generated XML should contain Employee type",
            XhtmlMatchers.xhtml(
                FileUtils.readFileToString(
                    new File(output, "requs.xml"),
                    StandardCharsets.UTF_8
                )
            ),
            XhtmlMatchers.hasXPaths("/spec/types/type[name='Employee']")
        );
    }

    /**
     * Run action while capturing standard output.
     *
     * <p>Log4j's ConsoleAppender binds to {@code System.out} once, on
     * first use, and never re-reads it; log4j.properties is reloaded
     * around the redirection so log messages land in the capture.</p>
     *
     * @param action Action to run
     * @return Captured output
     * @throws IOException If action fails
     */
    @SuppressWarnings("PMD.CloseResource")
    private static String captured(final Action action) throws IOException {
        final ByteArrayOutputStream out = new ByteArrayOutputStream();
        final PrintStream original = System.out;
        System.setOut(new PrintStream(out, true, StandardCharsets.UTF_8));
        PropertyConfigurator.configure(
            MainTest.class.getResource("/log4j.properties")
        );
        try {
            action.run();
        } finally {
            System.setOut(original);
            PropertyConfigurator.configure(
                MainTest.class.getResource("/log4j.properties")
            );
        }
        return new String(out.toByteArray(), StandardCharsets.UTF_8);
    }

    /**
     * Action that may fail with an I/O error.
     * @since 1.1
     */
    @FunctionalInterface
    private interface Action {

        /**
         * Run it.
         * @throws IOException If fails
         */
        void run() throws IOException;
    }
}
