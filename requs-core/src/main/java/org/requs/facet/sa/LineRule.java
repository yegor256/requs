/**
 * Copyright (c) 2009-2017, requs.org
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
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
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
            final Collection<Violation> violations =
                new LinkedList<Violation>();
            final AtomicInteger number = new AtomicInteger(1);
            for (final String line
                : StringUtils.splitPreserveAllTokens(spec, '\n')) {
                final int num = number.getAndIncrement();
                violations.addAll(
                    Collections2.transform(
                        this.origin.check(line),
                        new Function<Violation, Violation>() {
                            @Override
                            public Violation apply(final Violation violation) {
                                return new Violation.Simple(
                                    violation.details(),
                                    num, violation.position()
                                );
                            }
                        }
                    )
                );
            }
            return violations;
        }
    }

}
