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
package org.requs.facet.syntax;

import com.jcabi.matchers.XhtmlMatchers;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.nio.charset.StandardCharsets;
import java.util.Collection;
import javax.xml.transform.Source;
import org.apache.commons.io.IOUtils;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.requs.XeFacet;
import org.requs.facet.syntax.ontology.Flow;
import org.xembly.Directives;
import org.xembly.Xembler;

/**
 * Test case for {@link AntlrFacet}.
 * @since 0.1
 */
public final class AntlrFacetTest {

    @Test
    public void parsesInputAndProducesTypes() throws Exception {
        MatcherAssert.assertThat(
            AntlrFacetTest.parse("Sud includes: test."),
            XhtmlMatchers.hasXPaths("/spec/types")
        );
    }

    @Test
    public void reportsErrorsFound() throws Exception {
        MatcherAssert.assertThat(
            AntlrFacetTest.parse(
                "User is ?. Site is ?. Employee is a User."
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/types[count(type) = 2]",
                "//type[name='User']",
                "//type[name='Employee' and parents/type='User']",
                "/spec/errors[count(error)>2]",
                "/spec/errors/error[@type='syntax' and @line='1']"
            )
        );
    }

    @Test
    public void compilesComplexSpec() throws Exception {
        MatcherAssert.assertThat(
            AntlrFacetTest.parse(
                IOUtils.toString(
                    this.getClass().getResourceAsStream("example.req"),
                    StandardCharsets.UTF_8
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[not(error)]",
                "/spec/types[count(type)=2]",
                "/spec/types/type[name='User']",
                "/spec/types/type[name='Fraction']",
                "//type[name='Fraction']/slots/slot[name='numerator']",
                "//type[name='Fraction']/slots/slot[name='denominator']",
                "//type[name='Fraction']/info[informal='a math calculator']",
                "/spec[count(//method)=1]",
                "//method[id='UC1']/attributes[attribute='must']",
                String.format(
                    "//method[id='UC1']/bindings/binding[name='%s']",
                    Flow.SELF
                )
            )
        );
    }

    @Test
    public void parsesAllPossibleCases() throws Exception {
        MatcherAssert.assertThat(
            AntlrFacetTest.parse(
                IOUtils.toString(
                    this.getClass().getResourceAsStream("all-cases.req"),
                    StandardCharsets.UTF_8
                )
            ),
            XhtmlMatchers.hasXPath("/spec[not(errors/error)]")
        );
    }

    @Test
    public void parsesAllPossibleErrors() throws Exception {
        final String[] specs = {
            "\"alpha",
            "BrokenA is a 'file'.",
            "User is a",
            "User needs: a as",
            "UC1 where",
            "UC1 where User",
            "UC1 where User sends using",
            "UC1 where User sends using File and",
            "UC4/2 when \"hello\": 1. \"test\".",
            "UC4/2 when \"some problem\": ",
            "UC4/2 when \"",
            "UC9.9.2/PERF must",
            "UC9.9.2/PERF must \"work\".",
        };
        for (final String spec : specs) {
            MatcherAssert.assertThat(
                String.format("The spec can't be parsed: \"%s\"", spec),
                AntlrFacetTest.parse(spec),
                XhtmlMatchers.hasXPath("/spec/errors")
            );
        }
    }

    @Test
    @SuppressWarnings("PMD.AvoidInstantiatingObjectsInLoops")
    public void parsesAllSamples() throws Exception {
        final String[] files = {
            "samples/nfr.xml",
            "samples/method.xml",
            "samples/types.xml",
            "samples/pages.xml",
            "samples/informals.xml",
            "samples/all-possible-mistakes.xml",
        };
        for (final String file : files) {
            final XML xml = new XMLDocument(
                this.getClass().getResourceAsStream(file)
            );
            final Collection<String> xpaths = xml.xpath(
                "/sample/xpaths/xpath/text()"
            );
            MatcherAssert.assertThat(
                AntlrFacetTest.parse(xml.xpath("/sample/spec/text()").get(0)),
                XhtmlMatchers.hasXPaths(
                    xpaths.toArray(new String[0])
                )
            );
        }
    }

    /**
     * Parse input.
     * @param input Input syntax
     * @return XML output
     * @throws Exception If fails
     */
    private static Source parse(final String input) throws Exception {
        return XhtmlMatchers.xhtml(
            new XeFacet.Wrap(new AntlrFacet()).touch(
                new XMLDocument(
                    new Xembler(
                        new Directives().add("spec").add("input").set(input)
                    ).xml()
                )
            )
        );
    }

}
