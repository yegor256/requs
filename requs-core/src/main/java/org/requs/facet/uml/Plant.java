/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
