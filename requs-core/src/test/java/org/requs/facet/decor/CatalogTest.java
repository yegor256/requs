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
package org.requs.facet.decor;

import com.rexsl.test.XhtmlMatchers;
import java.io.IOException;
import org.apache.commons.lang3.StringUtils;
import org.hamcrest.MatcherAssert;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.requs.Doc;
import org.requs.Docs;

/**
 * Test case for {@link Catalog}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @checkstyle MultipleStringLiteralsCheck (500 lines)
 */
public final class CatalogTest {

    /**
     * Temporary folder.
     * @checkstyle VisibilityModifier (3 lines)
     */
    @Rule
    public transient TemporaryFolder temp = new TemporaryFolder();

    /**
     * Catalog can generate facets.
     * @throws IOException If fails
     */
    @Test
    public void generatesFacets() throws IOException {
        final Docs docs = new Docs.InDir(this.temp.newFolder());
        docs.get("index.xml").write(
            StringUtils.join(
                "<index><facets><facet id='abc'>",
                "<file>first.xml</file>",
                "<description>the text</description></facet>",
                "<facet id='fff'><file>second.xml</file>",
                "<description>oops</description></facet></facets></index>"
            )
        );
        final Doc main = docs.get("main.xml");
        main.write("<spec/>");
        new Catalog().touch(docs);
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(main.read()),
            XhtmlMatchers.hasXPaths(
                "/spec/facets[count(facet)=2]",
                "/spec/facets/facet[@id='abc']",
                "/spec/facets/facet[@id='fff']",
                "/spec/facets/facet[@file='first.xml' and .='the text']",
                "/spec/facets/facet[@file='second.xml' and .='oops']"
            )
        );
    }

}
