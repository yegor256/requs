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
 * Test case for {@link XeMethod}.
 * @since 1.1
 */
final class XeMethodTest {

    @Test
    void manipulatesWithMethod() throws Exception {
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
            "Method should create correct XML with signature, result, object, bindings and mentions",
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
    void avoidsDuplicateSteps() throws Exception {
        final Directives dirs = new Directives().add("mtd");
        final Method method = new XeMethod(dirs, "/mtd");
        method.step(1);
        method.step(1);
        MatcherAssert.assertThat(
            "Method should avoid creating duplicate steps with same number",
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPath("/mtd/steps[count(step)=1]")
        );
    }

    @Test
    void setsAttributes() throws Exception {
        final Directives dirs = new Directives().add("x");
        final Method method = new XeMethod(dirs, "/x");
        final String name = "attr-1";
        method.attribute(name, "");
        method.attribute(name, "ffa7ed");
        method.attribute("another", "123456");
        MatcherAssert.assertThat(
            "Method should correctly set attributes with seals",
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/x/attributes[count(attribute)=2]",
                "/x/attributes[attribute='attr-1' and attribute='another']",
                "/x/attributes/attribute[.='attr-1' and @seal='ffa7ed']"
            )
        );
    }

    @Test
    void createsNfr() throws Exception {
        final Directives dirs = new Directives().add("xx");
        final Method method = new XeMethod(dirs, "/xx");
        final String name = "PERF";
        method.nfr(name).explain("how are you?");
        method.nfr(name).explain("very good");
        method.nfr("UX");
        MatcherAssert.assertThat(
            "Method should create non-functional requirements with correct IDs",
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/xx/nfrs[count(nfr)=2]",
                "/xx/nfrs/nfr[id='PERF']",
                "/xx/nfrs/nfr[id='UX']"
            )
        );
    }

}
