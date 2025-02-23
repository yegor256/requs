/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.matchers.XhtmlMatchers;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.xembly.Xembler;

/**
 * Test case for {@link XeOntology}.
 * @since 1.1
 */
public final class XeOntologyTest {

    @Test
    public void manipulatesWithTypesAndUseCases() throws Exception {
        final XeOntology onto = new XeOntology();
        final Type type = onto.type("First");
        type.explain("first text");
        type.parent("Root");
        type.slot("one").assign("Emp");
        onto.type("Second").explain("second text");
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(onto).xml()),
            XhtmlMatchers.hasXPaths(
                "/spec",
                "/spec/types/type[name='First']",
                "/spec/types/type[name='Second']"
            )
        );
    }

    @Test
    public void avoidsDuplication() throws Exception {
        final XeOntology onto = new XeOntology();
        final String name = "Alpha";
        onto.type(name);
        onto.type(name);
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(onto).xml()),
            XhtmlMatchers.hasXPath("/spec/types[count(type)=1]")
        );
    }

    @Test
    public void avoidsDuplicationOfMethods() throws Exception {
        final XeOntology onto = new XeOntology();
        final String name = "UC3";
        onto.method(name);
        onto.method(name);
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(onto).xml()),
            XhtmlMatchers.hasXPath("/spec/methods[count(method)=1]")
        );
    }

}
