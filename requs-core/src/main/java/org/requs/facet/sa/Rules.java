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
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
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
