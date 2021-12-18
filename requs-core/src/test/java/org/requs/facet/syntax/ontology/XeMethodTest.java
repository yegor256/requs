/*
 * Copyright (c) 2009-2021, Yegor Bugayenko
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
import org.xembly.Directives;
import org.xembly.Xembler;

/**
 * Test case for {@link XeMethod}.
 * @since 1.1
 */
public final class XeMethodTest {

    @Test
    public void manipulatesWithMethod() throws Exception {
        final Directives dirs = new Directives().add("m");
        final Method method = new XeMethod(dirs, "/m");
        method.sign("\"informal one\"");
        method.binding("emp", "Employee");
        method.binding("one", "One");
        method.result("emp1");
        method.object("myself");
        method.mention(2);
        method.mention(1);
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/m[signature='\"informal one\"']",
                "/m[result='emp1']",
                "/m[object='myself']",
                "/m/bindings/binding[name='emp' and type='Employee']",
                "/m/bindings/binding[name='one' and type='One']",
                "/m/mentioned[where='2']",
                "/m/mentioned[where='1']"
            )
        );
    }

    @Test
    public void avoidsDuplicateSteps() throws Exception {
        final Directives dirs = new Directives().add("mtd");
        final Method method = new XeMethod(dirs, "/mtd");
        method.step(1);
        method.step(1);
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPath("/mtd/steps[count(step)=1]")
        );
    }

    @Test
    public void setsAttributes() throws Exception {
        final Directives dirs = new Directives().add("x");
        final Method method = new XeMethod(dirs, "/x");
        final String name = "attr-1";
        method.attribute(name, "");
        method.attribute(name, "ffa7ed");
        method.attribute("another", "123456");
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/x/attributes[count(attribute)=2]",
                "/x/attributes[attribute='attr-1' and attribute='another']",
                "/x/attributes/attribute[.='attr-1' and @seal='ffa7ed']"
            )
        );
    }

    @Test
    public void createsNfr() throws Exception {
        final Directives dirs = new Directives().add("xx");
        final Method method = new XeMethod(dirs, "/xx");
        final String name = "PERF";
        method.nfr(name).explain("how are you?");
        method.nfr(name).explain("very good");
        method.nfr("UX");
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/xx/nfrs[count(nfr)=2]",
                "/xx/nfrs/nfr[id='PERF']",
                "/xx/nfrs/nfr[id='UX']"
            )
        );
    }

}
