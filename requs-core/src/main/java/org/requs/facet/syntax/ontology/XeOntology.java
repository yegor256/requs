/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.aspects.Loggable;
import com.jcabi.aspects.Tv;
import java.util.Iterator;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.xembly.Directive;
import org.xembly.Directives;

/**
 * Xembly Ontology.
 *
 * @since 1.1
 * @checkstyle MultipleStringLiterals (500 lines)
 */
@ToString
@EqualsAndHashCode
@Loggable(Loggable.DEBUG)
@SuppressWarnings("PMD.AvoidDuplicateLiterals")
public final class XeOntology implements Ontology {

    /**
     * All directives.
     */
    private final transient Directives dirs = new Directives()
        .xpath("/").addIf("spec");

    @Override
    public Type type(final String name) {
        this.root("types")
            .xpath(
                String.format(
                    "/spec/types[not(type/name=%s)]",
                    XeOntology.escapeXPath(name)
                )
            )
            .add("type").add("name").set(name);
        return new XeType(
            this.dirs,
            String.format(
                "/spec/types/type[name=%s]",
                XeOntology.escapeXPath(name)
            )
        );
    }

    @Override
    public Method method(final String name) {
        this.root("methods")
            .xpath(
                String.format(
                    "/spec/methods[not(method/id=%s)]",
                    XeOntology.escapeXPath(name)
                )
            )
            .add("method").add("id").set(name);
        return new XeMethod(
            this.dirs,
            String.format(
                "/spec/methods/method[id=%s]",
                XeOntology.escapeXPath(name)
            )
        );
    }

    @Override
    public Page page(final String name) {
        this.root("pages")
            .xpath(
                String.format(
                    "/spec/pages[not(page/title=%s)]",
                    XeOntology.escapeXPath(name)
                )
            )
            .add("page").add("title").set(name);
        return new XePage(
            this.dirs,
            String.format(
                "/spec/pages/page[title=%s]",
                XeOntology.escapeXPath(name)
            )
        );
    }

    @Override
    public Acronym acronym(final String name) {
        this.root("acronyms")
            .xpath(
                String.format(
                    "/spec/acronyms[not(acronym/name=%s)]",
                    XeOntology.escapeXPath(name)
                )
            )
            .add("acronym").add("name").set(name);
        return new XeAcronym(
            this.dirs,
            String.format(
                "/spec/acronyms/acronym[name=%s]",
                XeOntology.escapeXPath(name)
            )
        );
    }

    @Override
    public Iterator<Directive> iterator() {
        return this.dirs.iterator();
    }

    /**
     * Escape XPath string.
     * @param text Text to escape
     * @return Escaped
     * @link https://issues.apache.org/jira/browse/LANG-1019
     */
    @SuppressWarnings("PMD.ProhibitPublicStaticMethods")
    public static String escapeXPath(final String text) {
        final String escaped;
        if (text.indexOf('\'') == -1) {
            escaped = new StringBuilder(text.length() + 2)
                .append('\'').append(text).append('\'').toString();
        } else {
            final int len = text.length() + Tv.FIFTY;
            escaped = new StringBuilder(len)
                .append("concat('")
                .append(text.replace("'", "', \"'\", '"))
                .append("')")
                .toString();
        }
        return escaped;
    }

    /**
     * Get root.
     * @param node Node name
     * @return Directives
     */
    private Directives root(final String node) {
        return this.dirs.xpath("/spec").strict(1).addIf(node);
    }

}
