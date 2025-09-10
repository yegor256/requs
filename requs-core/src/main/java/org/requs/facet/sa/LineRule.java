/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.google.common.base.Function;
import com.google.common.collect.Collections2;
import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import java.util.Collection;
import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicInteger;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.lang3.StringUtils;

/**
 * Rule of one line.
 *
 * @since 1.10
 */
@Immutable
public interface LineRule {

    /**
     * Validate incoming line.
     * @param line One line
     * @return Violations
     */
    Collection<Violation> check(String line);

    /**
     * Wrap.
     *
     * @since 1.10
     */
    @Immutable
    @ToString
    @EqualsAndHashCode(of = "origin")
    @Loggable(Loggable.DEBUG)
    final class Wrap implements Rule {
        /**
         * Original rule.
         */
        private final transient LineRule origin;

        /**
         * Ctor.
         * @param rule Original rule
         */
        public Wrap(final LineRule rule) {
            this.origin = rule;
        }

        @Override
        public Collection<Violation> enforce(final String spec) {
            final Collection<Violation> violations = new LinkedList<>();
            final AtomicInteger number = new AtomicInteger(1);
            for (final String line
                : StringUtils.splitPreserveAllTokens(spec, '\n')) {
                final int num = number.getAndIncrement();
                violations.addAll(
                    Collections2.transform(
                        this.origin.check(line),
                        // @checkstyle LineLength (1 line)
                        (Function<Violation, Violation>) vln -> new Violation.Simple(
                            vln.details(),
                            num, vln.position()
                        )
                    )
                );
            }
            return violations;
        }
    }

}
