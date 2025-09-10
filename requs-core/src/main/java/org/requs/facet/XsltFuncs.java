/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
