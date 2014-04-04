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
package org.requs.facet.markdown;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import com.jcabi.xml.XSL;
import com.jcabi.xml.XSLDocument;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.CharEncoding;
import org.requs.Doc;
import org.requs.Docs;
import org.requs.Facet;
import org.xembly.Directives;
import org.xembly.ImpossibleModificationException;
import org.xembly.Xembler;

/**
 * Markdown for every method.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.2
 */
@Immutable
@ToString(of = { })
@EqualsAndHashCode
public final class MdMethods implements Facet {

    /**
     * XSL for rendering.
     */
    private static final XSL SHEET = XSLDocument.make(
        MdMethods.class.getResourceAsStream("methods.xsl")
    );

    /**
     * Pattern to match markdown node.
     */
    private static final Pattern PTN = Pattern.compile(
        "<text>(.*)</text>", Pattern.DOTALL | Pattern.MULTILINE
    );

    @Override
    public void touch(final Docs docs) throws IOException {
        final XML pages = MdMethods.SHEET.transform(
            new XMLDocument(docs.get("main.xml").read())
        );
        final Directives dirs = new Directives()
            .xpath("/")
            .pi(
                "xml-stylesheet",
                "href='markdown.xsl' type='text/xsl'"
            )
            .add("pages").add("methods");
        for (final XML method : pages.nodes("/pages/methods/method")) {
            final Matcher matcher = MdMethods.PTN.matcher(
                method.nodes("text").get(0).toString()
            );
            if (!matcher.matches()) {
                throw new IllegalStateException("internal trouble");
            }
            final String name = method.xpath("id/text()").get(0);
            final String path = String.format("md/methods/%s.md", name);
            docs.get(path).write(matcher.group(1));
            dirs.add("method").attr("id", name).set(path).up();
        }
        final Doc index = docs.get("markdown.xml");
        try {
            index.write(new Xembler(dirs).xml());
        } catch (final ImpossibleModificationException ex) {
            throw new IllegalStateException(ex);
        }
        index.name("md", "Use Cases and Entities in Markdown");
        // @checkstyle MultipleStringLiteralsCheck (1 line)
        docs.get("markdown.xsl").write(
            IOUtils.toString(
                this.getClass().getResourceAsStream("markdown.xsl"),
                CharEncoding.UTF_8
            )
        );
    }

}
