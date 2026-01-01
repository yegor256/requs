/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import lombok.EqualsAndHashCode;
import lombok.ToString;

/**
 * Violation.
 *
 * @since 1.10
 */
@Immutable
public interface Violation {

    /**
     * Line number.
     * @return Line (starting with 1)
     */
    int line();

    /**
     * Position in line.
     * @return Position (start from 1)
     */
    int position();

    /**
     * Description of the violation.
     * @return Description
     */
    String details();

    /**
     * Simple implementation.
     *
     * @since 1.0
     */
    @Immutable
    @ToString
    @EqualsAndHashCode
    @Loggable(Loggable.DEBUG)
    final class Simple implements Violation {
        /**
         * Descr.
         */
        private final transient String txt;

        /**
         * Line number.
         */
        private final transient int num;

        /**
         * Position in line.
         */
        private final transient int pos;

        /**
         * Ctor.
         * @param text Description
         * @param line Line number
         * @param position Position in line
         */
        public Simple(final String text, final int line, final int position) {
            this.txt = text;
            this.num = line;
            this.pos = position;
        }

        @Override
        public int line() {
            return this.num;
        }

        @Override
        public int position() {
            return this.pos;
        }

        @Override
        public String details() {
            return this.txt;
        }
    }

}
