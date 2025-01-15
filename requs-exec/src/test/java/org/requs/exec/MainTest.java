/*
 * Copyright (c) 2009-2025, Yegor Bugayenko
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
public final class MainTest {

    /**
     * Output stream for tests.
     */
    private transient ByteArrayOutputStream out;

    @BeforeEach
    public void changeSystemOutputSteam() throws Exception {
        this.out = new ByteArrayOutputStream();
        System.setOut(new PrintStream(this.out, true));
    }

    @AfterEach
    public void revertChangedSystemOutputStream() throws Exception {
        System.setOut(null);
    }

    @Test
    public void displaysVersionNumber() throws Exception {
        Main.main(new String[]{"-v"});
        MatcherAssert.assertThat(
            this.out.toString(),
            Matchers.containsString("-SNAPSHOT")
        );
    }

    @Test
    public void rendersHelpMessage() throws Exception {
        Main.main(new String[] {"-h"});
        MatcherAssert.assertThat(
            this.out.toString(),
            Matchers.containsString("Usage:")
        );
    }

    @Test
    public void compilesRequsSources(@TempDir final Path temp) throws Exception {
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
            this.out.toString(),
            Matchers.containsString("compiled and saved to")
        );
        MatcherAssert.assertThat(
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
