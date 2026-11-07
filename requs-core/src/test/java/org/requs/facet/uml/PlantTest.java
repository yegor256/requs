/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.uml;

import com.jcabi.matchers.XhtmlMatchers;
import com.jcabi.xml.XMLDocument;
import java.io.IOException;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.DisabledOnOs;
import org.junit.jupiter.api.condition.OS;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.requs.facet.Transform;

/**
 * Test case for {@link Plant}.
 *
 * @since 1.11
 */
final class PlantTest {

    @Test
    @DisabledOnOs(OS.WINDOWS)
    void buildsSvg() throws IOException {
        MatcherAssert.assertThat(
            "Plant should generate valid SVG diagram from PlantUML markup",
            XhtmlMatchers.xhtml(
                Plant.svg(
                    String.format("@startuml%nBob -> Alice : hello%n@enduml%n")
                )
            ),
            XhtmlMatchers.hasXPath("//svg:g")
        );
    }

    @ParameterizedTest
    @CsvSource({
        "class-diagrams, User",
        "use-case-diagrams, UC1",
        "sequence-diagrams, login"
    })
    @DisabledOnOs(OS.WINDOWS)
    void rendersSpecDiagrams(final String sheet, final String label) {
        MatcherAssert.assertThat(
            "UML facets should render diagram labels rather than an error image",
            XhtmlMatchers.xhtml(
                new Transform(String.format("uml/%s.xsl", sheet)).touch(
                    new XMLDocument(
                        String.join(
                            "",
                            "<spec><types><type><name>User</name>",
                            "<actor>true</actor></type></types><methods><method>",
                            "<id>UC1</id><signature>login</signature><bindings>",
                            "<binding><name>_self</name><type>User</type></binding>",
                            "<binding><name>user</name><type>User</type></binding>",
                            "</bindings><steps><step><object>user</object>",
                            "<signature>login</signature></step></steps>",
                            "</method></methods></spec>"
                        )
                    )
                ).xpath("/spec//diagram/svg/text()").get(0)
            ),
            XhtmlMatchers.hasXPath(
                String.format("//svg:text[.='%s']", label)
            )
        );
    }
}
