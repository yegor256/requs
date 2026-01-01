/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.matchers.XhtmlMatchers;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.xembly.Directives;
import org.xembly.Xembler;

/**
 * Test case for {@link XeSlot}.
 * @since 1.1
 */
final class XeSlotTest {

    @Test
    void manipulatesWithProperty() throws Exception {
        final Directives dirs = new Directives().add("p");
        final Slot slot = new XeSlot(dirs, "/p");
        slot.explain("first text");
        slot.explain("second text");
        slot.assign("Employee");
        slot.mention(2);
        slot.mention(1);
        MatcherAssert.assertThat(
            "Slot should contain proper info and mentions",
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/p/info",
                "/p/info[informal='first text']",
                "/p/info[informal='second text']",
                "/p[type='Employee']",
                "/p/mentioned[where='2']",
                "/p/mentioned[where='1']"
            )
        );
    }

}
