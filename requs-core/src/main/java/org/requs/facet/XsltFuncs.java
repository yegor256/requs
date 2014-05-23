/**
 * Copyright (c) 2009-2014, requs.org
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

import com.google.common.base.Function;
import com.google.common.collect.Collections2;
import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Tv;
import com.jcabi.xml.XMLDocument;
import com.petebevin.markdown.MarkdownProcessor;
import java.util.Collection;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.codec.digest.DigestUtils;
import org.apache.commons.lang3.StringEscapeUtils;
import org.apache.commons.lang3.StringUtils;

/**
 * XSLT functions (utility class, but this is the only option with Saxon).
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.9
 */
@Immutable
@ToString
@EqualsAndHashCode
public final class XsltFuncs {

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
    public static String toHtml(final String markdown) {
        return new MarkdownProcessor().markdown(markdown);
    }

    /**
     * Seal the method.
     * @param xml Xml to seal
     * @return Seal as a string
     */
    public static String seal(final String xml) {
        final Collection<String> parts = Collections2.transform(
            new XMLDocument(xml).xpath("//*/text()"),
            new Function<String, String>() {
                @Override
                public String apply(final String input) {
                    return StringEscapeUtils.escapeJava(
                        input.replaceAll("\\s+", " ")
                    );
                }
            }
        );
        return DigestUtils.md5Hex(
            StringUtils.join(parts, "")
        ).substring(0, Tv.SIX);
    }

}
