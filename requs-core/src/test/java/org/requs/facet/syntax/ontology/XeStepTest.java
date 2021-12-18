/**
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
 * Test case for {@link XeStep}.
 * @author Yegor Bugayenko (yegor256@gmail.com)
 * @version $Id$
 * @since 1.1
 */
public final class XeStepTest {

    @Test
    public void manipulatesWithSteps() throws Exception {
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
