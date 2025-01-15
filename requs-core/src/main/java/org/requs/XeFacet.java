/*
 * Copyright (c) 2009-2025, Yegor Bugayenko
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
import com.jcabi.aspects.Loggable;
import com.jcabi.immutable.Array;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.io.IOException;
import java.util.Collections;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.w3c.dom.Node;
import org.xembly.Directive;
import org.xembly.ImpossibleModificationException;
import org.xembly.Xembler;

/**
 * Xembly producing facet.
 *
 * @since 1.9
 */
@Immutable
public interface XeFacet {

    /**
     * Touch the spec from this facet.
     * @param spec Spec in XML
     * @return Directives
     * @throws IOException If fails on I/O operation
     * @since 1.9
     */
    Iterable<Directive> touch(XML spec) throws IOException;

    /**
     * Wrap into Facet.
     *
     * @since 1.9
     */
    @Immutable
    @ToString
    @EqualsAndHashCode(of = "origin")
    @Loggable(Loggable.DEBUG)
    final class Wrap implements Facet {
        /**
         * Original facet.
         */
        private final transient XeFacet origin;

        /**
         * Ctor.
         * @param fct Original facet
         */
        public Wrap(final XeFacet fct) {
            this.origin = fct;
        }

        @Override
        public XML touch(final XML spec) throws IOException {
            final Node node = spec.node();
            final Iterable<Directive> dirs = this.origin.touch(spec);
            try {
                new Xembler(dirs).apply(node);
            } catch (final ImpossibleModificationException ex) {
                throw new IllegalStateException(
                    String.format("failed to apply: %s", dirs), ex
                );
            }
            return new XMLDocument(node);
        }
    }

    /**
     * Always returns the same.
     *
     * @since 1.9
     */
    @Immutable
    @ToString(of = { })
    @EqualsAndHashCode(of = "dirs")
    @Loggable(Loggable.DEBUG)
    final class Fixed implements XeFacet {
        /**
         * Dirs.
         */
        private final transient Array<Directive> dirs;

        /**
         * Ctor.
         * @param list List of directives
         */
        public Fixed(final Iterable<Directive> list) {
            this.dirs = new Array<Directive>(list);
        }

        @Override
        public Iterable<Directive> touch(final XML spec) {
            return Collections.unmodifiableCollection(this.dirs);
        }
    }

}
