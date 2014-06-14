/**
 * Copyright (c) 2009-2014, requs.org
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
import java.util.Collection;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.CharEncoding;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.Assume;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

/**
 * Test case for {@link org.requs.Compiler}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.1
 * @checkstyle MultipleStringLiteralsCheck (500 lines)
 */
public final class CompilerTest {

    /**
     * XSTLPROC binary.
     */
    private static final String BIN = "xsltproc";

    /**
     * Temporary folder.
     * @checkstyle VisibilityModifier (3 lines)
     */
    @Rule
    public transient TemporaryFolder temp = new TemporaryFolder();

    /**
     * Compiler can parse all samples.
     * @throws Exception When necessary
     */
    @Test
    public void parsesAllSamples() throws Exception {
        final String[] files = {
            "samples/all-possible-constructs.xml",
            "samples/all-possible-mistakes.xml",
            "samples/clean-spec.xml",
            "samples/exceptions.xml",
            "samples/order-of-steps.xml",
        };
        for (final String file : files) {
            this.parses(
                IOUtils.toString(
                    CompilerTest.class.getResourceAsStream(file),
                    CharEncoding.UTF_8
                )
            );
        }
    }

    /**
     * Compiler can parse given text.
     * @param text Text to parse
     * @throws Exception When necessary
     */
    private void parses(final String text) throws Exception {
        final XML xml = new XMLDocument(text);
        final File input = this.temp.newFolder();
        final File output = this.temp.newFolder();
        FileUtils.write(
            new File(input, "input.req"),
            xml.xpath("/sample/spec/text()").get(0),
            CharEncoding.UTF_8
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
            XhtmlMatchers.hasXPaths(
                xpaths.toArray(new String[xpaths.size()])
            )
        );
        MatcherAssert.assertThat(
            xsl.transform(srs),
            XhtmlMatchers.hasXPath("//xhtml:body")
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
            Matchers.isEmptyString()
        );
        MatcherAssert.assertThat(
            FileUtils.readFileToString(new File(output, "requs.html")),
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
        Assume.assumeThat(
            ver,
            Matchers.containsString("libxml")
        );
    }

}
