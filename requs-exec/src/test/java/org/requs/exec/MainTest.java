/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.exec;

import com.jcabi.matchers.XhtmlMatchers;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import org.apache.commons.io.FileUtils;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/**
 * Test case for {@link Main}.
 * @since 1.1
 */
final class MainTest {

    /**
     * Output stream for tests.
     */
    private transient ByteArrayOutputStream out;

    @BeforeEach
    void changeSystemOutputSteam() throws Exception {
        this.out = new ByteArrayOutputStream();
        System.setOut(new PrintStream(this.out, true));
    }

    @AfterEach
    void revertChangedSystemOutputStream() throws Exception {
        System.setOut(null);
    }

    @Test
    void displaysVersionNumber() throws Exception {
        Main.main(new String[]{"-v"});
        MatcherAssert.assertThat(
            "Output should contain version number",
            this.out.toString(),
            Matchers.containsString("-SNAPSHOT")
        );
    }

    @Test
    void rendersHelpMessage() throws Exception {
        Main.main(new String[] {"-h"});
        MatcherAssert.assertThat(
            "Output should contain help message",
            this.out.toString(),
            Matchers.containsString("Usage:")
        );
    }

    @Test
    void compilesRequsSources(@TempDir final Path temp) throws Exception {
        final File input = temp.resolve("input").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(input, "employee.req"),
            "Employee is a \"user of the system\".",
            StandardCharsets.UTF_8
        );
        Main.main(
            new String[] {
                "-i", input.getAbsolutePath(),
                "-o", output.getAbsolutePath(),
            }
        );
        MatcherAssert.assertThat(
            "Output should indicate successful compilation",
            this.out.toString(),
            Matchers.containsString("compiled and saved to")
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

}
