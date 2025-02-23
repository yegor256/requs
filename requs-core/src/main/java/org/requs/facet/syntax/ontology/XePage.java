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
 * Xembly page.
 *
 * @since 1.7
 */
@ToString
@EqualsAndHashCode
@Loggable(Loggable.DEBUG)
final class XePage implements Page {

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
    XePage(final Directives directives, final String xpath) {
        this.mentioned = new XeMentioned(directives, xpath);
        this.informal = new XeInformal(directives, xpath);
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
