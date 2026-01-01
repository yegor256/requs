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
 * Test case for {@link XeStep}.
 * @since 1.1
 */
final class XeStepTest {

    @Test
    void manipulatesWithSteps() throws Exception {
        final Directives dirs = new Directives().add("s");
        final Step step = new XeStep(dirs, "/s");
        step.result("data");
        step.sign("\"do something\"");
        step.object("boom");
        step.input("file");
        step.input("document");
        step.exception("division by zero").step(1).sign("hey!");
        step.mention(2);
        step.mention(1);
        MatcherAssert.assertThat(
            "Step manipulation should generate correct XML structure",
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/s[result='data']",
                "/s[object='boom']",
                "/s/args[count(arg)=2]",
                "/s/args[arg='file']",
                "/s/args[arg='document']",
                "/s[signature='\"do something\"']",
                "/s/exceptions/exception[when='division by zero']",
                "/s/exceptions/exception/steps/step[signature='hey!']"
            )
        );
    }

}
