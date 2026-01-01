/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import com.jcabi.xml.XML;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.requs.XeFacet;
import org.xembly.Directive;
import org.xembly.Directives;

/**
 * Static analysis rules.
 *
 * @since 1.10
 */
@Immutable
@ToString
@EqualsAndHashCode
@Loggable(Loggable.DEBUG)
public final class Rules implements XeFacet {

    @Override
    public Iterable<Directive> touch(final XML spec) {
        final Rule[] rules = {
            new LineRule.Wrap(
                new RegexRule(
                    "[^ ] +$",
                    "trailing space(s) at the end of line"
                )
            ),
            new LineRule.Wrap(
                new RegexRule(
                    "[^ ] {2,}",
                    "avoid two or more consecutive spaces"
                )
            ),
            new LineRule.Wrap(
                new RegexRule(
                    ".{81,}",
                    "avoid lines longer than 80 characters"
                )
            ),
            new LineRule.Wrap(
                new RegexRule(
                    "\t",
                    "avoid TAB characters, use four spaces instead"
                )
            ),
            new LineRule.Wrap(
                new RegexRule(
                    "\r",
                    "don't use Windows line-endings"
                )
            ),
            new LineRule.Wrap(
                new RegexRule(
                    ",[^$ \n\r]",
                    "always use space after comma"
                )
            ),
            new LineRule.Wrap(
                new RegexRule(
                    ";[^$ ]",
                    "always use space after semicolon"
                )
            ),
            new LineRule.Wrap(new IndentationRule()),
            new CascadingRule(),
        };
        final String input;
        if (spec.nodes("/spec/input[.!='']").isEmpty()) {
            input = "";
        } else {
            input = spec.xpath("/spec/input/text()").get(0);
        }
        final Directives dirs = new Directives().xpath("/spec").addIf("errors");
        for (final Rule rule : rules) {
            for (final Violation violation : rule.enforce(input)) {
                dirs.add("error")
                    .attr("pos", Integer.toString(violation.position()))
                    .attr("line", Integer.toString(violation.line()))
                    .set(violation.details()).up();
            }
        }
        return dirs;
    }
}
