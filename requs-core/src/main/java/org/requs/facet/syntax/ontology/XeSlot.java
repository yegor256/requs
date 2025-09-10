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
 * Xembly slot in a type.
 *
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(of = "dirs")
@Loggable(Loggable.DEBUG)
final class XeSlot implements Slot {

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
    XeSlot(final Directives directives, final String xpath) {
        this.mentioned = new XeMethod(directives, xpath);
        this.informal = new XeInformal(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void assign(final String type) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("type").set(type);
    }

    @Override
    public void arity(final Slot.Arity arity) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("arity").set(arity.mnemo());
    }

    @Override
    public void composition(final boolean cmp) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("composition").set(Boolean.toString(cmp));
    }

    @Override
    public void mention(final int where) {
        this.mentioned.mention(where);
    }

    @Override
    public void explain(final String info) {
        this.informal.explain(info);
    }

}
