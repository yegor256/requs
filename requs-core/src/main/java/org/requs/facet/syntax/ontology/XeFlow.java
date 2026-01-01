/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
