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
package org.requs.facet.ambiguity;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.io.IOException;
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
 * Overall.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.2
 */
@Immutable
@ToString(of = { })
@EqualsAndHashCode
public final class Overall implements Facet {

    @Override
    public void touch(final Docs docs) throws IOException {
        final XML main = new XMLDocument(docs.get("main.xml").read());
        final int crud = main.nodes(
            // @checkstyle LineLength (1 line)
            "//signature[.='creates' or .='reads' or .='updates' or .='deletes']"
        ).size();
        final int informal = main.nodes(
            "//signature[starts-with(.,'&quot;')]"
        ).size();
        final int total = crud + informal;
        final double overall;
        if (total == 0) {
            overall = 0.0d;
        } else {
            overall = (double) informal / (double) total;
        }
        final Directives dirs = new Directives()
            .xpath("/")
            .pi(
                "xml-stylesheet",
                "href='ambiguity.xsl' type='text/xsl'"
            )
            .add("metrics")
            .add("metric")
            .attr("id", "overall").set(Double.toString(overall));
        final Doc index = docs.get("ambiguity.xml");
        try {
            index.write(new Xembler(dirs).xml());
        } catch (final ImpossibleModificationException ex) {
            throw new IllegalStateException(ex);
        }
        index.name("ambiguity", "Ambiguity Analysis");
        // @checkstyle MultipleStringLiteralsCheck (1 line)
        docs.get("ambiguity.xsl").write(
            IOUtils.toString(
                this.getClass().getResourceAsStream("ambiguity.xsl"),
                CharEncoding.UTF_8
            )
        );
    }

}
