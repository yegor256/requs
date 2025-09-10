/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.aspects.Loggable;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.xembly.Directives;

/**
 * Xembly type.
 *
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeType implements Type {

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
    XeType(final Directives directives, final String xpath) {
        this.mentioned = new XeMentioned(directives, xpath);
        this.informal = new XeInformal(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void parent(final String type) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("parents").add("type").set(type);
    }

    @Override
    public void actor(final boolean act) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("actor").set(Boolean.toString(act));
    }

    @Override
    public Slot slot(final String name) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("slots").add("slot").add("name").set(name);
        return new XeSlot(
            this.dirs,
            String.format(
                "%s/slots/slot[name=%s]", this.start,
                XeOntology.escapeXPath(name)
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
