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
 * Xembly step.
 *
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeStep implements Step {

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
     * Signature helper.
     */
    private final transient Signature signature;

    /**
     * Ctor.
     * @param directives Directives to extend
     * @param xpath XPath to start with
     */
    XeStep(final Directives directives, final String xpath) {
        this.mentioned = new XeMentioned(directives, xpath);
        this.signature = new XeSignature(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public Flow exception(final String text) {
        this.dirs.xpath(this.start)
            .strict(1).addIf("exceptions")
            .xpath(this.start)
            .xpath(
                String.format(
                    "exceptions[not(exception/when=%s)]",
                    XeOntology.escapeXPath(text)
                )
            )
            .add("exception").add("when").set(text);
        return new XeFlow(
            this.dirs,
            String.format(
                "%s/exceptions/exception[when=%s ]",
                this.start, XeOntology.escapeXPath(text)
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
    public void input(final String name) {
        this.signature.input(name);
    }

    @Override
    public void mention(final int where) {
        this.mentioned.mention(where);
    }

    @Override
    public void explain(final String informal) {
        this.signature.explain(informal);
    }
}
