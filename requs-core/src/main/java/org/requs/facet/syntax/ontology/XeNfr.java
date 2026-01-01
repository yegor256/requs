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
 * Xembly NFR.
 *
 * @since 1.5
 */
@ToString
@EqualsAndHashCode(of = "dirs")
@Loggable(Loggable.DEBUG)
final class XeNfr implements Nfr {

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
    XeNfr(final Directives directives, final String xpath) {
        this.mentioned = new XeMethod(directives, xpath);
        this.informal = new XeInformal(directives, xpath);
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void mention(final int where) {
        this.mentioned.mention(where);
    }

    @Override
    public void explain(final String info) {
        assert this.dirs != null;
        assert this.start != null;
        this.informal.explain(info);
    }

}
