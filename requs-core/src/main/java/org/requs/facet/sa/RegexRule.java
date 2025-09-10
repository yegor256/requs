/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import java.util.Collection;
import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import lombok.EqualsAndHashCode;
import lombok.ToString;

/**
 * Regular expression rule.
 *
 * @since 1.10
 */
@Immutable
@ToString
@EqualsAndHashCode(of = { "regex", "text" })
@Loggable(Loggable.DEBUG)
public final class RegexRule implements LineRule {

    /**
     * Regular expression.
     */
    private final transient String regex;

    /**
     * Description of violation.
     */
    private final transient String text;

    /**
     * Ctor.
     * @param rgx Regular expression
     * @param txt Description
     */
    public RegexRule(final String rgx, final String txt) {
        this.regex = rgx;
        this.text = txt;
    }

    @Override
    @SuppressWarnings("PMD.AvoidInstantiatingObjectsInLoops")
    public Collection<Violation> check(final String line) {
        final Pattern ptn = Pattern.compile(this.regex);
        final Matcher matcher = ptn.matcher(line);
        final Collection<Violation> violations = new LinkedList<>();
        while (matcher.find()) {
            violations.add(
                new Violation.Simple(
                    String.format("%s: [%s]", this.text, line),
                    0, matcher.start() + 1
                )
            );
        }
        return violations;
    }
}
