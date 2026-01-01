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
 * Xembly mentioned.
 *
 * @since 1.1
 */
@ToString
@EqualsAndHashCode(of = { "dirs", "start" })
@Loggable(Loggable.DEBUG)
final class XeMentioned implements Mentioned {

    /**
     * All directives.
     */
    private final transient Directives dirs;

    /**
     * Starting XPath.
     */
    private final transient String start;

    /**
     * Ctor.
     * @param directives Directives to extend
     * @param xpath XPath to start with
     */
    XeMentioned(final Directives directives, final String xpath) {
        this.dirs = directives;
        this.start = xpath;
    }

    @Override
    public void mention(final int where) {
        this.dirs.xpath(this.start).strict(1).addIf("mentioned")
            .strict(1)
            .add("where").set(Integer.toString(where));
    }
}
