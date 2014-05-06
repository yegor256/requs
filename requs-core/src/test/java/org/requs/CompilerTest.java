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
import java.io.File;
import org.apache.commons.io.FileUtils;
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
     * Compiler can compile.
     * @throws Exception When necessary
     */
    @Test
    public void compilesRequsSources() throws Exception {
        final File input = this.temp.newFolder();
        final File output = this.temp.newFolder();
        FileUtils.write(
            new File(input, "input.req"),
            "Employee is a \"user of the system\"."
        );
        new Compiler(input, output).compile();
        final XML srs = new XMLDocument(new File(output, "main.xml"));
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(srs.toString()),
            XhtmlMatchers.hasXPaths(
                "processing-instruction('xml-stylesheet')",
                "/spec/types/type[name='Employee']"
            )
        );
    }

    /**
     * Compiler can produce renderable XML+XSL resources.
     * @throws Exception When necessary
     */
    @Test
    @SuppressWarnings("PMD.AvoidInstantiatingObjectsInLoops")
    public void producesRenderableXml() throws Exception {
        CompilerTest.assumeXsltproc();
        final File input = this.temp.newFolder();
        final File output = this.temp.newFolder();
        FileUtils.write(
            new File(input, "a.req"),
            "Employee is a \"user of this perfect system\"."
        );
        new Compiler(input, output).compile();
        final String[] names = {"main", "tbds", "index", "nfrs", "markdown"};
        for (final String name : names) {
            final String html = String.format("%s.html", name);
            MatcherAssert.assertThat(
                new VerboseProcess(
                    new ProcessBuilder()
                        .directory(output)
                        .command(
                            CompilerTest.BIN,
                            "-o",
                            html,
                            String.format("%s.xml", name)
                        )
                        .start()
                ).stdout(),
                Matchers.isEmptyString()
            );
            MatcherAssert.assertThat(
                FileUtils.readFileToString(new File(output, html)),
                XhtmlMatchers.hasXPath("//xhtml:body")
            );
        }
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
