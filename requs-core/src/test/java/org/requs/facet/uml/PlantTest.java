/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.uml;

import com.jcabi.matchers.XhtmlMatchers;
import java.io.IOException;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.DisabledOnOs;
import org.junit.jupiter.api.condition.OS;

/**
 * Test case for {@link Plant}.
 * @since 1.11
 */
final class PlantTest {

    @Test
    @DisabledOnOs(OS.WINDOWS)
    void buildsSvg() throws IOException {
        MatcherAssert.assertThat(
            "Plant should generate valid SVG diagram from PlantUML markup",
            XhtmlMatchers.xhtml(
                Plant.svg("@startuml\nBob -> Alice : hello\n@enduml\n")
            ),
            XhtmlMatchers.hasXPath("//svg:g")
        );
    }

}
