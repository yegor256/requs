/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.aspects.Tv;
import com.jcabi.matchers.XhtmlMatchers;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.xembly.Directives;
import org.xembly.Xembler;

/**
 * Test case for {@link XeFlow}.
 * @since 1.8
 */
public final class XeFlowTest {

    @Test
    public void manipulatesWithBindings() throws Exception {
        final Directives dirs = new Directives().add("f");
        final Flow flow = new XeFlow(dirs, "/f");
        flow.binding("emp", "Employee");
        flow.binding("one", "One");
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/f/bindings/binding[name='emp' and type='Employee']",
                "/f/bindings/binding[name='one' and type='One']"
            )
        );
    }

    @Test
    public void avoidsDuplicateBindings() throws Exception {
        final Directives dirs = new Directives().add("f1");
        final Flow flow = new XeFlow(dirs, "/f1");
        for (int idx = 0; idx < Tv.FIVE; ++idx) {
            flow.binding("a", "alpha");
        }
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/f1/bindings[count(binding)=1]",
                "/f1/bindings/binding[name='a' and type='alpha']"
            )
        );
    }

}
