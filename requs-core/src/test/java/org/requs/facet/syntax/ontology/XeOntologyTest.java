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
