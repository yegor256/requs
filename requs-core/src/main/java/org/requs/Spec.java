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

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.util.Arrays;
import org.requs.syntax.AntlrSpec;

/**
 * Spec.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
@Immutable
public interface Spec {

    /**
     * Get XML.
     * @return XML
     */
    XML xml();

    /**
     * Fixed.
     */
    @Immutable
    final class Fixed implements Spec {
        /**
         * Encapsulated XML.
         */
        private final transient String xml;
        /**
         * Ctor.
         * @param doc XML to use
         */
        public Fixed(final String doc) {
            this.xml = doc;
        }
        @Override
        public XML xml() {
            return new XMLDocument(this.xml);
        }
    }

    /**
     * All inclusive.
     */
    @Immutable
    final class Ultimate implements Spec {
        /**
         * Encapsulated Requs source.
         */
        private final transient String src;
        /**
         * Ctor.
         * @param req Requs source
         */
        public Ultimate(final String req) {
            this.src = req;
        }
        @Override
        public XML xml() {
            return new Validated(
                new Built(
                    new Transformed(
                        new Sealed(
                            new AntlrSpec(this.src)
                        ),
                        Arrays.asList(
                            "metrics.xsl", "seals-check.xsl",
                            "types-check.xsl", "signatures-check.xsl"
                        )
                    )
                )
            ).xml();
        }
    }
}
