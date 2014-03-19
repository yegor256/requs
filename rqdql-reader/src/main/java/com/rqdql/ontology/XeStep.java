/**
 * Copyright (c) 2009-2013, RQDQL.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the RQDQL.com nor
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
package com.rqdql.ontology;

import com.jcabi.aspects.Loggable;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.lang3.Validate;
import org.xembly.Directives;

/**
 * Xembly step.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(callSuper = false, of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeStep implements Step {

    /**
     * Pattern to match variables.
     */
    private static final String VAR = "[a-z]+";

    /**
     * All directives.
     */
    private final transient Directives dirs;

    /**
     * Starting XPath.
     */
    private final transient String start;

    /**
     * Mentioned helper.
     */
    private final transient Mentioned mentioned;

    /**
     * Informal helper.
     */
    private final transient Informal informal;

    /**
     * Ctor.
     * @param directives Directives to extend
     * @param xpath XPath to start with
     */
    XeStep(final Directives directives, final String xpath) {
        this.mentioned = new XeMentioned(directives, xpath);
        this.informal = new XeInformal(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void object(final String variable) {
        Validate.matchesPattern(variable, XeStep.VAR, "bad obj: %s", variable);
        this.dirs.xpath(this.start).add("object").set(variable);
    }

    @Override
    public void result(final String variable) {
        Validate.matchesPattern(variable, XeStep.VAR, "bad var: %s", variable);
        this.dirs.xpath(this.start).add("result").set(variable);
    }

    @Override
    public void arguments(final Iterable<String> vars) {
        assert vars != null;
        this.dirs.xpath(this.start).add("args");
        for (final String var : vars) {
            Validate.matchesPattern(var, XeStep.VAR, "bad argument: %s", var);
            this.dirs.add("arg").set(var).up();
        }
    }

    @Override
    public void signature(final String text) {
        assert text != null;
        this.dirs.xpath(this.start).add("signature").set(text);
    }

    @Override
    public Flow exception(final String text) {
        assert text != null;
        this.dirs.xpath(this.start).addIf("exceptions")
            .xpath(this.start)
            .xpath(String.format("exceptions[not(exception/when='%s' )]", text))
            .add("exception").add("when").set(text)
            .xpath(this.start)
            .xpath(String.format("exceptions[not(exception/when='%s')]", text));
        return new XeFlow(
            this.dirs,
            String.format(
                "%s/exceptions/exception[when='%s']",
                this.start, text
            )
        );
    }

    @Override
    public void explain(final String info) {
        this.informal.explain(info);
    }

    @Override
    public void mention(final int where) {
        this.mentioned.mention(where);
    }
}
