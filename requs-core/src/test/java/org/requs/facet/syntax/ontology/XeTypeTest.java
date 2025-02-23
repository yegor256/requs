/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.matchers.XhtmlMatchers;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.xembly.Directives;
import org.xembly.Xembler;

/**
 * Test case for {@link XeType}.
 * @since 1.1
 */
public final class XeTypeTest {

    @Test
    public void manipulatesWithType() throws Exception {
        final Directives dirs = new Directives().add("t");
        final Type type = new XeType(dirs, "/t");
        type.explain("first text");
        type.explain("second text");
        type.parent("Root");
        type.slot("'one").assign("Emp");
        type.mention(2);
        type.mention(1);
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/t/info",
                "/t/info[informal='first text']",
                "/t/info[informal='second text']",
                "/t/parents[type='Root']",
                "/t/mentioned[where='2']",
                "/t/mentioned[where='1']",
                "/t/slots/slot[type='Emp']"
            )
        );
    }

}
