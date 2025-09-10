/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import java.util.Collection;
import java.util.LinkedList;
import lombok.EqualsAndHashCode;
import lombok.ToString;

/**
 * Indentation rule in a single line.
 *
 * @since 1.14
 */
@Immutable
@ToString
@EqualsAndHashCode
@Loggable(Loggable.DEBUG)
public final class IndentationRule implements LineRule {

    @Override
    public Collection<Violation> check(final String line) {
        int indent;
        for (indent = 0; indent < line.length(); ++indent) {
            if (line.charAt(indent) != ' ') {
                break;
            }
        }
        final Collection<Violation> violations = new LinkedList<>();
        if (indent % 2 != 0) {
            violations.add(
                new Violation.Simple(
                    String.format(
                        "indented for %d spaces, must be either %d or %d: [%s]",
                        indent,
                        indent >> 1 << 1,
                        indent + 1 >> 1 << 1, line
                    ),
                    0, indent
                )
            );
        }
        return violations;
    }
}
