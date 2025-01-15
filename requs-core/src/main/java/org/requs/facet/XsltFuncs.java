/*
 * Copyright (c) 2009-2025, Yegor Bugayenko
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
package org.requs.facet;

import com.google.common.collect.Collections2;
import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Tv;
import com.jcabi.xml.XMLDocument;
import com.vladsch.flexmark.html.HtmlRenderer;
import com.vladsch.flexmark.parser.Parser;
import com.vladsch.flexmark.util.data.DataHolder;
import com.vladsch.flexmark.util.data.MutableDataSet;
import java.util.Collection;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.codec.digest.DigestUtils;
import org.apache.commons.lang3.StringUtils;
import org.apache.commons.text.StringEscapeUtils;
import org.w3c.dom.Node;

/**
 * XSLT functions (utility class, but this is the only option with Saxon).
 *
 * @since 1.9
 */
@Immutable
@ToString
@EqualsAndHashCode
public final class XsltFuncs {

    /**
     * Pattern for printing.
     */
    private static final Pattern PTN = Pattern.compile(
        "<x>(.*)</x>", Pattern.DOTALL | Pattern.MULTILINE
    );

    /**
     * Utility class.
     */
    private XsltFuncs() {
        // empty intentionally
    }

    /**
     * Convert markdown to HTML.
     * @param markdown Markdown
     * @return HTML
     */
    @SuppressWarnings("PMD.ProhibitPublicStaticMethods")
    public static String html(final String markdown) {
        final DataHolder options = new MutableDataSet();
        final Parser parser = Parser.builder(options).build();
        final HtmlRenderer renderer = HtmlRenderer.builder(options).build();
        final com.vladsch.flexmark.util.ast.Node document =
            parser.parse(markdown);
        return renderer.render(document);
    }

    /**
     * Seal the method.
     * @param xml Xml to seal
     * @return Seal as a string
     */
    @SuppressWarnings("PMD.ProhibitPublicStaticMethods")
    public static String seal(final Node xml) {
        final Collection<String> parts = Collections2.transform(
            new XMLDocument(xml).xpath("//*/text()"),
            input -> StringEscapeUtils.escapeJava(
                input.replaceAll("\\s+", " ")
            )
        );
        return DigestUtils.md5Hex(
            StringUtils.join(parts, "")
        ).substring(0, Tv.SIX);
    }

    /**
     * Print node content into string.
     * @param node Node
     * @return XML
     */
    @SuppressWarnings("PMD.ProhibitPublicStaticMethods")
    public static String print(final Node node) {
        final String txt = new XMLDocument(node).nodes("/*").get(0).toString();
        final Matcher matcher = XsltFuncs.PTN.matcher(txt);
        if (!matcher.matches()) {
            throw new IllegalStateException(
                String.format("invalid XML node: %s", txt)
            );
        }
        return matcher.group(1);
    }

}
