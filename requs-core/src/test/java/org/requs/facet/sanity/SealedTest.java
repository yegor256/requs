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
package org.requs.facet.sanity;

import com.rexsl.test.XhtmlMatchers;
import org.apache.commons.lang3.StringUtils;
import org.junit.Test;
import org.mockito.Mockito;
import org.requs.Doc;
import org.requs.Docs;

/**
 * Test case for {@link Sealed}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
public final class SealedTest {

    /**
     * Sealed can seal use cases.
     * @throws Exception When necessary
     */
    @Test
    public void sealsUseCases() throws Exception {
        final Docs docs = Mockito.mock(Docs.class);
        final Doc doc = Mockito.mock(Doc.class);
        Mockito.doReturn(doc).when(docs).get(Mockito.anyString());
        Mockito.doReturn(
            StringUtils.join(
                "<spec><method><id>test</id>",
                "<attributes>hey</attributes>",
                "<info><informal>a\t\r\n\nff&#x20ac;</informal></info>",
                "<mentioned>1</mentioned></method></spec>"
            )
        ).when(doc).read();
        new Sealed().touch(docs);
        Mockito.verify(doc).write(
            Mockito.argThat(
                XhtmlMatchers.<String>hasXPaths(
                    "/spec/method[@seal='52b5d6']"
                )
            )
        );
    }

    /**
     * Sealed can ignore non-important elements.
     * @throws Exception When necessary
     */
    @Test
    public void ignoresNonImportantElements() throws Exception {
        final Docs docs = Mockito.mock(Docs.class);
        final Doc doc = Mockito.mock(Doc.class);
        Mockito.doReturn(doc).when(docs).get(Mockito.anyString());
        Mockito.doReturn(
            StringUtils.join(
                "<spec><method><id>UC1</id>",
                "<steps><step><number>55</number></step></steps></method>",
                "<method><id>UC2</id>",
                "<attributes>hey</attributes>",
                "<mentioned>1</mentioned>",
                "<steps>\n<step><number>55</number>",
                "<mentioned>3</mentioned>  </step>\n</steps>",
                "</method></spec>"
            )
        ).when(doc).read();
        new Sealed().touch(docs);
        Mockito.verify(doc).write(
            Mockito.argThat(
                XhtmlMatchers.<String>hasXPaths(
                    "/spec[method[id='UC1']/@seal = method[id='UC2']/@seal]",
                    "/spec/method[@seal='b53b3a']"
                )
            )
        );
    }

}
