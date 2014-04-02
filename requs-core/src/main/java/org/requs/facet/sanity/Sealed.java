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

import com.google.common.base.Functions;
import com.google.common.collect.Iterables;
import com.google.common.collect.Sets;
import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Tv;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.io.IOException;
import org.apache.commons.codec.digest.DigestUtils;
import org.apache.commons.lang3.StringUtils;
import org.requs.Doc;
import org.requs.Docs;
import org.requs.Facet;
import org.w3c.dom.Node;
import org.xembly.Directives;
import org.xembly.ImpossibleModificationException;
import org.xembly.Xembler;

/**
 * Sealed spec.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
@Immutable
public final class Sealed implements Facet {

    @Override
    public void touch(final Docs docs) throws IOException {
        final Doc doc = docs.get("main.xml");
        final XML xml = new XMLDocument(doc.read());
        final Directives dirs = new Directives();
        for (final XML method : xml.nodes("//method[id]")) {
            final String name = method.xpath("id/text()").get(0);
            dirs.xpath(String.format("//method[id='%s']", name)).attr(
                "seal", Sealed.seal(method)
            );
        }
        final Node node = xml.node();
        try {
            new Xembler(dirs).apply(node);
        } catch (final ImpossibleModificationException ex) {
            throw new IllegalStateException(ex);
        }
        doc.write(new XMLDocument(node).toString());
    }

    /**
     * Seal the method.
     * @param xml Xml to seal
     * @return Seal as a string
     */
    private static String seal(final XML xml) {
        return DigestUtils.md5Hex(
            Sets.newHashSet(
                Iterables.transform(
                    xml.nodes(
                        StringUtils.join(
                            "*[not(name()='attributes')",
                            " and not(name()='mentioned')]"
                        )
                    ),
                    Functions.toStringFunction()
                )
            ).toString()
        ).substring(0, Tv.SIX);
    }

}
