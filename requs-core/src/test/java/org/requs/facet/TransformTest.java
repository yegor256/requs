/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import com.jcabi.matchers.XhtmlMatchers;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import org.apache.commons.lang3.StringUtils;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;

/**
 * Test case for {@link Transform}.
 *
 * @since 0.1
 */
final class TransformTest {

    @Test
    void checksSeals() {
        MatcherAssert.assertThat(
            "Transform should detect seal mismatches between methods and attributes",
            XhtmlMatchers.xhtml(
                new Transform("sanity/seals-check.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><method seal='a12ef4'>",
                            "<id>UC5</id><attributes>",
                            "<attribute seal='b89e4e'>invalid</attribute>",
                            "<attribute seal='a12ef4'>valid</attribute>",
                            "</attributes></method><errors/></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1]",
                "/spec/errors/error[contains(.,'a12ef4')]"
            )
        );
    }

    @Test
    void checksTypes() {
        MatcherAssert.assertThat(
            "Transform should detect undefined types in slots and bindings",
            XhtmlMatchers.xhtml(
                new Transform("sanity/types-check.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><types><type><name>User</name>",
                            "<slots><slot><type>Alpha</type></slot></slots>",
                            "</type></types><methods><method><bindings>",
                            "<binding><type>Beta</type></binding>",
                            "</bindings></method></methods><errors/></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=2]",
                "/spec/errors/error[contains(.,'Alpha')]"
            )
        );
    }

    @Test
    void computesSeals() {
        MatcherAssert.assertThat(
            "Transform should compute a six-character seal for every method",
            new Transform("seal-methods.xsl").touch(
                new XMLDocument(TransformTest.specWithMethods())
            ).xpath("/spec/method/@seal"),
            Matchers.hasSize(3)
        );
    }

    @Test
    void computesIdenticalSeals() {
        final XML first = new Transform("seal-methods.xsl").touch(
            new XMLDocument(TransformTest.specWithMethods())
        );
        MatcherAssert.assertThat(
            "Transform should produce identical seals for identical method bodies",
            first.xpath("/spec/method[id='UC1']/@seal").get(0),
            Matchers.equalTo(first.xpath("/spec/method[id='UC2']/@seal").get(0))
        );
    }

    @Test
    void computesDifferentSeals() {
        final XML first = new Transform("seal-methods.xsl").touch(
            new XMLDocument(TransformTest.specWithMethods())
        );
        MatcherAssert.assertThat(
            "Transform should produce different seals for different method bodies",
            first.xpath("/spec/method[id='UC1']/@seal").get(0),
            Matchers.not(
                Matchers.equalTo(first.xpath("/spec/method[id='UC3']/@seal").get(0))
            )
        );
    }

    @Test
    void keepsSealsStable() {
        MatcherAssert.assertThat(
            "Transform should keep seals stable across transformations",
            new Transform("seal-methods.xsl").touch(
                new XMLDocument(TransformTest.specWithMethods())
            ).xpath("/spec/method/@seal"),
            Matchers.equalTo(
                new Transform("seal-methods.xsl").touch(
                    new XMLDocument(TransformTest.specWithMethods())
                ).xpath("/spec/method/@seal")
            )
        );
    }

    @Test
    void generatesMarkdown() {
        MatcherAssert.assertThat(
            "Transform should print method details as Markdown and render HTML",
            XhtmlMatchers.xhtml(
                new Transform("methods-in-markdown.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><method>",
                            "<id>UC1</id><signature>do()</signature>",
                            "<bindings>",
                            "<binding><name>_self</name><type>User</type></binding>",
                            "<binding><name>db</name><type>Database</type></binding>",
                            "</bindings>",
                            "<info><informal>User does something",
                            "<informal>User does more</informal>",
                            "</informal></info>",
                            "</method></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/method/markdown[contains(.,'technical details')]",
                "/spec/method/markdown[contains(.,'do()')]",
                "/spec/method/markdown[contains(.,'\"User does somethingUser does more\"')]",
                "/spec/method/html[contains(.,'<table>')]",
                "/spec/method/html[contains(.,'User does something')]"
            )
        );
    }

    @Test
    void rendersPages() {
        MatcherAssert.assertThat(
            "Transform should render informal page text as HTML",
            XhtmlMatchers.xhtml(
                new Transform("pages-in-html.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><page><name>home</name>",
                            "<info><informal>User is a \"human\" being",
                            "&lt;now&gt;</informal></info>",
                            "</page></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/page/html[contains(.,'<p>')]",
                "/spec/page/html[contains(.,'User is a &quot;human&quot; being')]",
                "/spec/page/html[contains(.,'<now>')]"
            )
        );
    }

    @Test
    void checksSignatures() {
        MatcherAssert.assertThat(
            "Transform should detect invalid signatures in methods and steps",
            XhtmlMatchers.xhtml(
                new Transform("sanity/signatures-check.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><methods><method><signature>abc</signature>",
                            "</method><method><steps><step><signature>cde",
                            "</signature></step></steps></method></methods>",
                            "<errors/></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1 ]",
                "/spec/errors/error[contains(.,'cde')]"
            )
        );
    }

    private static String specWithMethods() {
        return StringUtils.join(
            "<spec><method><id>UC1</id><signature>do()</signature></method>",
            "<method><id>UC2</id><signature>do()</signature></method>",
            "<method><id>UC3</id><signature>stop()</signature></method>",
            "</spec>"
        );
    }
}
