/**
 * Copyright (c) 2009-2017, requs.org
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
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
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
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
