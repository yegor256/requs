/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.ClasspathSources;
import com.jcabi.xml.XML;
import com.jcabi.xml.XSLDocument;
import java.net.URL;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.requs.Facet;

/**
 * Transform.
 *
 * @since 0.1
 */
@Immutable
@ToString(includeFieldNames = false)
@EqualsAndHashCode(of = "sheet")
public final class Transform implements Facet {

    /**
     * XSL sheet to apply.
     */
    private final transient String sheet;

    /**
     * Public ctor.
     * @param xsl Name of XSL resource
     */
    public Transform(final String xsl) {
        this.sheet = xsl;
    }

    @Override
    public XML touch(final XML spec) {
        final URL url = Transform.class.getResource(this.sheet);
        if (url == null) {
            throw new IllegalArgumentException(
                String.format("Stylesheet '%s' not found", this.sheet)
            );
        }
        return XSLDocument.make(url)
            .with(new ClasspathSources(this.getClass()))
            .transform(spec);
    }

}
