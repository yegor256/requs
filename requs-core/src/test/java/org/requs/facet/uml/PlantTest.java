/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
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
public final class PlantTest {

    @Test
    @DisabledOnOs(OS.WINDOWS)
    public void buildsSvg() throws IOException {
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(
                Plant.svg("@startuml\nBob -> Alice : hello\n@enduml\n")
            ),
            XhtmlMatchers.hasXPath("//svg:g")
        );
    }

}
