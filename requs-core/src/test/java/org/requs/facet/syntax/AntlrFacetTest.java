/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
final class AntlrFacetTest {

    @Test
    void parsesInputAndProducesTypes() throws Exception {
        MatcherAssert.assertThat(
            "Parsed spec should contain types",
            AntlrFacetTest.parse("Sud includes: test."),
            XhtmlMatchers.hasXPaths("/spec/types")
        );
    }

    @Test
    void reportsErrorsFound() throws Exception {
        MatcherAssert.assertThat(
            "Spec with errors should contain error elements",
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
    void compilesComplexSpec() throws Exception {
        MatcherAssert.assertThat(
            "Complex spec should be parsed correctly",
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
    void parsesAllPossibleCases() throws Exception {
        MatcherAssert.assertThat(
            "All possible cases should be parsed without errors",
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
    void parsesAllPossibleErrors() throws Exception {
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
    void parsesAllSamples() throws Exception {
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
                "Sample should be parsed correctly",
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
