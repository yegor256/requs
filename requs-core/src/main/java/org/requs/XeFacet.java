/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
            final Node node = spec.inner();
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
