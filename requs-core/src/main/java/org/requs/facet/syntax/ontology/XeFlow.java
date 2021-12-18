/*
 * Copyright (c) 2009-2021, Yegor Bugayenko
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
package org.requs.facet.syntax.ontology;

import com.jcabi.aspects.Loggable;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.xembly.Directives;

/**
 * Xembly use case.
 *
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeFlow implements Flow {

    /**
     * All directives.
     */
    private final transient Directives dirs;

    /**
     * Starting XPath.
     */
    private final transient String start;

    /**
     * Informal helper.
     */
    private final transient Informal informal;

    /**
     * Ctor.
     * @param directives Directives to extend
     * @param xpath XPath to start with
     */
    XeFlow(final Directives directives, final String xpath) {
        this.informal = new XeInformal(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public Step step(final int number) {
        this.dirs.xpath(this.start).strict(1).addIf("steps")
            .xpath(this.start)
            .xpath(String.format("steps[not(step/number=%d)]", number))
            .add("step").add("number").set(Integer.toString(number));
        return new XeStep(
            this.dirs,
            String.format("%s/steps/step[number=%d]", this.start, number)
        );
    }

    @Override
    public void binding(final String name, final String type) {
        this.dirs.xpath(this.start).strict(1).addIf("bindings").up().xpath(
            String.format(
                "bindings[not(binding[name='%s' and type=%s])]",
                name, XeOntology.escapeXPath(type)
            )
        ).add("binding").add("name").set(name).up().add("type").set(type);
    }

    @Override
    public void explain(final String info) {
        this.informal.explain(info);
    }

}
