/**
 * Copyright (c) 2009-2021, Yegor Bugayenko
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
package org.requs.facet.uml;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.XMLDocument;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import net.sourceforge.plantuml.FileFormat;
import net.sourceforge.plantuml.FileFormatOption;
import net.sourceforge.plantuml.SourceStringReader;
import org.apache.commons.lang3.SystemUtils;

/**
 * Plant UML compiler.
 *
 * @author Yegor Bugayenko (yegor256@gmail.com)
 * @version $Id$
 * @since 1.11
 */
@Immutable
@ToString(of = { })
@EqualsAndHashCode
public final class Plant {

    /**
     * Utility class.
     */
    private Plant() {
        // empty
    }

    /**
     * Make a diagram, in SVG.
     * @param src PlantUML source
     * @return SVG as a text
     * @throws IOException If fails
     */
    @SuppressWarnings("PMD.ProhibitPublicStaticMethods")
    public static String svg(final String src) throws IOException {
        final String svg;
        if (SystemUtils.IS_OS_WINDOWS) {
            svg = "<p>SVG can't be rendered in Windows</p>";
        } else {
            final SourceStringReader reader = new SourceStringReader(src);
            final ByteArrayOutputStream baos = new ByteArrayOutputStream();
            reader.generateImage(baos, new FileFormatOption(FileFormat.SVG));
            svg = new XMLDocument(
                new String(baos.toByteArray())
            ).nodes("/*").get(0).toString().replace("xmlns=\"\"", "");
        }
        return svg;
    }

}
