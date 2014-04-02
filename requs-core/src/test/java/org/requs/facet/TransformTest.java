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
package org.requs.facet;

import com.rexsl.test.XhtmlMatchers;
import java.io.IOException;
import javax.xml.transform.Source;
import org.apache.commons.lang3.StringUtils;
import org.hamcrest.MatcherAssert;
import org.junit.Test;
import org.mockito.ArgumentCaptor;
import org.mockito.Mockito;
import org.requs.Doc;
import org.requs.Docs;

/**
 * Test case for {@link Transform}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
public final class TransformTest {

    /**
     * Transform can check seals.
     */
    @Test
    public void checksSeals() throws IOException {
        MatcherAssert.assertThat(
            TransformTest.transform(
                StringUtils.join(
                    "<spec><method seal='a12ef4'><id>UC5</id><attributes>",
                    "<attribute seal='b89e4e'>invalid</attribute>",
                    "<attribute seal='a12ef4'>valid</attribute>",
                    "</attributes></method><errors/></spec>"
                ),
                "sanity/seals-check.xsl"
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1]",
                "/spec/errors/error[contains(.,'a12ef4')]"
            )
        );
    }

    /**
     * Transform can check seals.
     */
    @Test
    public void checksTypes() throws IOException {
        MatcherAssert.assertThat(
            TransformTest.transform(
                StringUtils.join(
                    "<spec><types><type><name>User</name>",
                    "<slots><slot><type>Alpha</type></slot></slots>",
                    "</type></types><methods><method><bindings>",
                    "<binding><type>Beta</type></binding>",
                    "</bindings></method></methods><errors/></spec>"
                ),
                "sanity/types-check.xsl"
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=2]",
                "/spec/errors/error[contains(.,'Alpha')]"
            )
        );
    }

    /**
     * Transform can check signatures.
     */
    @Test
    public void checksSignatures() throws IOException {
        MatcherAssert.assertThat(
            TransformTest.transform(
                StringUtils.join(
                    "<spec><methods><method><signature>abc</signature>",
                    "</method><method><steps><step><signature>cde",
                    "</signature></step></steps></method></methods>",
                    "<errors/></spec>"
                ),
                "sanity/signatures-check.xsl"
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1 ]",
                "/spec/errors/error[contains(.,'cde')]"
            )
        );
    }

    /**
     * Transform input.
     * @param input Input syntax
     * @param xsl XSL stylesheet resource
     * @return XML output
     * @throws IOException If fails
     */
    private static Source transform(final String input,
        final String xsl) throws IOException {
        final Docs docs = Mockito.mock(Docs.class);
        final Doc doc = Mockito.mock(Doc.class);
        Mockito.doReturn(doc).when(docs).get(Mockito.anyString());
        Mockito.doReturn(input).when(doc).read();
        new Transform(xsl).touch(docs);
        final ArgumentCaptor<String> arg =
            ArgumentCaptor.forClass(String.class);
        Mockito.verify(doc).write(arg.capture());
        return XhtmlMatchers.xhtml(arg.getValue());
    }
}
