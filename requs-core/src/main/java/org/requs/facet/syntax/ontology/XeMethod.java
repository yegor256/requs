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
@EqualsAndHashCode(of = { "mentioned", "flow", "signature" })
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
     * Signature helper.
     */
    private final transient Signature signature;

    /**
     * Ctor.
     * @param directives Directives to extend
     * @param xpath XPath to start with
     */
    XeMethod(final Directives directives, final String xpath) {
        this.mentioned = new XeMentioned(directives, xpath);
        this.flow = new XeFlow(directives, xpath);
        this.signature = new XeSignature(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void attribute(final String name, final String seal) {
        this.dirs.xpath(this.start)
            .strict(1)
            .addIf("attributes")
            .xpath(
                String.format(
                    "%s/attributes[not(attribute=%s)]",
                    this.start, XeOntology.escapeXPath(name)
                )
            )
            .add("attribute").set(name)
            .xpath(
                String.format(
                    "%s/attributes/attribute[.=%s]",
                    this.start, XeOntology.escapeXPath(name)
                )
            )
            .strict(1)
            .attr("seal", seal);
    }

    @Override
    public Nfr nfr(final String name) {
        this.dirs.xpath(this.start)
            .strict(1).addIf("nfrs").strict(1)
            .xpath(
                String.format(
                    "%s/nfrs[not(nfr/id=%s)]",
                    this.start, XeOntology.escapeXPath(name)
                )
            )
            .add("nfr").add("id").set(name);
        return new XeNfr(
            this.dirs,
            String.format(
                "%s/nfrs/nfr[id=%s]", this.start,
                XeOntology.escapeXPath(name)
            )
        );
    }

    @Override
    public void sign(final String text) {
        this.signature.sign(text);
    }

    @Override
    public void object(final String name) {
        this.signature.object(name);
    }

    @Override
    public void result(final String name) {
        this.signature.result(name);
    }

    @Override
    public Step step(final int number) {
        return this.flow.step(number);
    }

    @Override
    public void binding(final String name, final String type) {
        this.flow.binding(name, type);
    }

    @Override
    public void input(final String name) {
        this.signature.input(name);
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
