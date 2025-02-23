/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.aspects.Loggable;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.xembly.Directives;

/**
 * Xembly signature.
 *
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeSignature implements Signature {

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
    XeSignature(final Directives directives, final String xpath) {
        this.dirs = directives;
        this.start = xpath;
        this.informal = new XeInformal(directives, xpath);
    }

    @Override
    public void sign(final String text) {
        this.dirs.xpath(this.start).strict(1)
            .add("signature").set(text);
    }

    @Override
    public void object(final String name) {
        this.dirs.xpath(this.start).strict(1)
            .add("object").set(name);
    }

    @Override
    public void result(final String name) {
        this.dirs.xpath(this.start).strict(1)
            .add("result").set(name);
    }

    @Override
    public void input(final String name) {
        this.dirs.xpath(this.start).strict(1)
            .addIf("args").add("arg").set(name);
    }

    @Override
    public void explain(final String info) {
        this.informal.explain(info);
    }

}
