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
import org.apache.commons.lang3.StringUtils;

/**
 * Cascading rule.
 *
 * @since 1.14
 */
@Immutable
@ToString
@EqualsAndHashCode
@Loggable(Loggable.DEBUG)
public final class CascadingRule implements Rule {

    @Override
    @SuppressWarnings("PMD.AvoidInstantiatingObjectsInLoops")
    public Collection<Violation> enforce(final String text) {
        final String[] lines = StringUtils.splitPreserveAllTokens(text, '\n');
        final Collection<Violation> violations = new LinkedList<>();
        int indent = 0;
        for (int idx = 0; idx < lines.length; ++idx) {
            final int next = CascadingRule.indent(lines[idx]);
            if (indent > 0 && next > indent && next != indent + 2) {
                violations.add(
                    new Violation.Simple(
                        String.format(
                            "indented for %d spaces, while %d required: [%s]",
                            next, indent + 2, lines[idx]
                        ),
                        idx + 1, next
                    )
                );
            }
            indent = next;
        }
        return violations;
    }

    /**
     * Calculate indentation of a line.
     * @param line Line
     * @return Indentation
     */
    private static int indent(final String line) {
        int indent;
        for (indent = 0; indent < line.length(); ++indent) {
            if (line.charAt(indent) != ' ') {
                break;
            }
        }
        return indent;
    }
}
