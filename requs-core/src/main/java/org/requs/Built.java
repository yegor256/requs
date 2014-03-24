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
package org.requs;

import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.util.Date;
import org.apache.commons.lang3.time.DateFormatUtils;
import org.w3c.dom.Node;
import org.xembly.Directives;
import org.xembly.ImpossibleModificationException;
import org.xembly.Xembler;

/**
 * Built.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
final class Built implements Spec {

    /**
     * Encapsulated original spec.
     */
    private final transient Spec origin;

    /**
     * Ctor.
     * @param spec Original spec
     */
    Built(final Spec spec) {
        this.origin = spec;
    }

    @Override
    public XML xml() {
        final long start = System.currentTimeMillis();
        final Node node = this.origin.xml().node();
        try {
            new Xembler(
                new Directives().xpath("/spec").add("build")
                    .add("duration")
                    .set(Long.toString(System.currentTimeMillis() - start)).up()
                    .add("time")
                    .set(DateFormatUtils.ISO_DATETIME_FORMAT.format(new Date()))
            ).apply(node);
        } catch (final ImpossibleModificationException ex) {
            throw new IllegalStateException(ex);
        }
        return new XMLDocument(new XMLDocument(node).toString());
    }

}
