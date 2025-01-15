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
package org.requs;

import com.jcabi.log.VerboseProcess;
import com.jcabi.matchers.XhtmlMatchers;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import com.jcabi.xml.XSL;
import com.jcabi.xml.XSLDocument;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.util.Collection;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/**
 * Test case for {@link org.requs.Compiler}.
 * @since 1.1
 * @checkstyle MultipleStringLiteralsCheck (500 lines)
 */
@SuppressWarnings("PMD.AvoidDuplicateLiterals")
public final class CompilerTest {

    /**
     * XSTLPROC binary.
     */
    private static final String BIN = "xsltproc";

    @Test
    public void parsesAllSamples(@TempDir final Path temp) throws Exception {
        final String[] files = {
            "samples/empty-input.xml",
            "samples/all-possible-constructs.xml",
            "samples/all-possible-mistakes.xml",
            "samples/clean-spec.xml",
            "samples/exceptions.xml",
            "samples/order-of-steps.xml",
            "samples/wrong-steps-numbering.xml",
        };
        for (final String file : files) {
            this.parses(
                temp,
                file,
                IOUtils.toString(
                    CompilerTest.class.getResourceAsStream(file),
                    StandardCharsets.UTF_8
                )
            );
        }
    }

    @Test
    public void combinesMultipleFiles(@TempDir final Path temp) throws Exception {
        final File input = temp.resolve("input").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(input, "b.req"),
            "\n\nUser is a \"good human being\".",
            StandardCharsets.UTF_8
        );
        FileUtils.write(
            new File(input, "a.req"),
            "\n\nUser is a \"human being\".",
            StandardCharsets.UTF_8
        );
        FileUtils.write(
            new File(input, "c.req"),
            "\n\n\nUser is a \"very good human being\". bug",
            StandardCharsets.UTF_8
        );
        new Compiler(input, output).compile();
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new XMLDocument(new File(output, "requs.xml"))),
            XhtmlMatchers.hasXPaths(
                "/spec/files/file[@id='0' and @line='1']",
                "/spec/files/file[@id='1' and @line='4']",
                "/spec/files/file[@id='2' and @line='7']",
                "//mentioned/where[.='0:3']",
                "//mentioned/where[.='1:3']",
                "//mentioned/where[.='2:4']",
                "/spec/errors/error[@file='2' and @line='4']"
            )
        );
    }

    /**
     * Compiler can parse given text.
     * @param temp Temp file
     * @param file File we're parsing
     * @param text Text to parse
     * @throws Exception When necessary
     */
    private void parses(final Path temp, final String file,
        final String text) throws Exception {
        final XML xml = new XMLDocument(text);
        final File input = temp.resolve("input").toFile();
        final File output = temp.resolve("output").toFile();
        FileUtils.write(
            new File(input, "input.req"),
            xml.xpath("/sample/spec/text()").get(0),
            StandardCharsets.UTF_8
        );
        new Compiler(input, output).compile();
        final XML srs = new XMLDocument(new File(output, "requs.xml"));
        final XSL xsl = new XSLDocument(
            new XMLDocument(new File(output, "requs.xsl"))
        );
        final Collection<String> xpaths = xml.xpath(
            "/sample/xpaths/xpath/text()"
        );
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(srs.toString()),
            Matchers.describedAs(
                file,
                XhtmlMatchers.hasXPaths(
                    xpaths.toArray(new String[0])
                )
            )
        );
        MatcherAssert.assertThat(
            xsl.applyTo(srs),
            Matchers.describedAs(
                file,
                XhtmlMatchers.hasXPath("//xhtml:body")
            )
        );
        CompilerTest.assumeXsltproc();
        MatcherAssert.assertThat(
            new VerboseProcess(
                new ProcessBuilder()
                    .directory(output)
                    .command(
                        CompilerTest.BIN,
                        "-o",
                        "requs.html",
                        "requs.xml"
                    )
                    .start()
            ).stdout(),
            Matchers.describedAs(
                file,
                Matchers.is(Matchers.emptyString())
            )
        );
        MatcherAssert.assertThat(
            FileUtils.readFileToString(
                new File(output, "requs.html"),
                StandardCharsets.UTF_8
            ),
            XhtmlMatchers.hasXPath("//xhtml:body")
        );
    }

    /**
     * Assume that it is installed.
     */
    private static void assumeXsltproc() {
        String ver;
        try {
            ver = new VerboseProcess(
                new ProcessBuilder()
                    .command(CompilerTest.BIN, "-version")
                    .redirectErrorStream(true)
            ).stdoutQuietly();
        } catch (final IllegalStateException ex) {
            ver = "";
        }
        Assumptions.assumeTrue(
            ver.contains("libxml")
        );
    }

}
