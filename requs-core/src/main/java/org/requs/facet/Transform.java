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
