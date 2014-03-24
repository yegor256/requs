/**
 * Copyright (c) 2009-2014, requs.org
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
package org.requs.syntax;

import com.rexsl.test.XhtmlMatchers;
import org.apache.commons.io.IOUtils;
import org.hamcrest.MatcherAssert;
import org.junit.Test;

/**
 * Test case for {@link AntlrSpec}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
public final class AntlrSpecTest {

    /**
     * AntlrSpec can parse input text and produce clauses.
     * @throws Exception When necessary
     */
    @Test
    public void parsesInputAndProducesTypes() throws Exception {
        MatcherAssert.assertThat(
            new AntlrSpec("Sud includes: test.").xml(),
            XhtmlMatchers.hasXPaths("/spec/types")
        );
    }

    /**
     * AntlrSpec can report syntax/grammar errors found.
     * @throws Exception When necessary
     */
    @Test
    public void reportsErrorsFound() throws Exception {
        MatcherAssert.assertThat(
            new AntlrSpec("User is ?. Site is ?. Employee is a User.").xml(),
            XhtmlMatchers.hasXPaths(
                "/spec/types[count(type) = 3]",
                "//type[name='User']",
                "//type[name='Employee' and parents/parent='User']",
                "/spec/errors[count(error)=2]",
                "/spec/errors/error[@type='syntax' and @line='1']"
            )
        );
    }

    /**
     * AntlrSpec can compile a complex document.
     * @throws Exception When necessary
     */
    @Test
    public void compilesComplexSpec() throws Exception {
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(
                new AntlrSpec(
                    IOUtils.toString(
                        this.getClass().getResourceAsStream("example.req")
                    )
                ).xml().node()
            ),
            XhtmlMatchers.hasXPath(
                "/spec/errors[not(error)]",
                "/spec/types[count(type)=3]",
                "/spec/types/type[name='User']",
                "//type[name='User']/slots/slot[name='photo' and arity='ANY']",
                "//type[name='User']/slots/slot[name='SSN' and arity='OPT']",
                "/spec/types/type[name='Fraction']",
                "//type[name='Fraction']/info[informal='math calculator']",
                "/spec[count(//method)=1]",
                "//method[id='UC1']/attributes[attribute='must']"
            )
        );
    }

    /**
     * AntlrSpec can parse all possible cases.
     * @throws Exception When necessary
     */
    @Test
    public void parsesAllPossibleCases() throws Exception {
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(
                new AntlrSpec(
                    IOUtils.toString(
                        this.getClass().getResourceAsStream("all-cases.req")
                    )
                ).xml().node()
            ),
            XhtmlMatchers.hasXPath("/spec[not(errors/error)]")
        );
    }

}
