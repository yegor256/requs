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
 * Xembly use case.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(callSuper = false, of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeMethod implements Method {

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
     * Flow helper.
     */
    private final transient Flow flow;

    /**
     * Ctor.
     * @param directives Directives to extend
     * @param xpath XPath to start with
     */
    XeMethod(final Directives directives, final String xpath) {
        this.mentioned = new XeMentioned(directives, xpath);
        this.flow = new XeFlow(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void signature(final String text) {
        Validate.matchesPattern(text, ".+", "invalid: %s", text);
        this.dirs.xpath(this.start).add("signature").set(text);
    }

    @Override
    public Step step(final int number) {
        return this.flow.step(number);
    }

    @Override
    public void variable(final Flow.Kind kind,
        final String name, final String type) {
        this.flow.variable(kind, name, type);
    }

    @Override
    public void explain(final String info) {
        this.flow.explain(info);
    }

    @Override
    public void mention(final int where) {
        this.mentioned.mention(where);
    }
}
