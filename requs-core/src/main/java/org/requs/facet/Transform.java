/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.ClasspathSources;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamSource;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import net.sf.saxon.lib.ResourceResolverWrappingURIResolver;
import net.sf.saxon.s9api.DOMDestination;
import net.sf.saxon.s9api.Processor;
import net.sf.saxon.s9api.SaxonApiException;
import net.sf.saxon.s9api.XsltCompiler;
import net.sf.saxon.s9api.XsltExecutable;
import net.sf.saxon.s9api.XsltTransformer;
import org.requs.Facet;
import org.w3c.dom.Document;

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
     * Saxon processor with requs extension functions registered.
     */
    private static final Processor PROCESSOR = SaxonFunctions.processor();

    /**
     * XSL sheet to apply.
     */
    private final transient String sheet;

    /**
     * Public ctor.
     *
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
        return Transform.transformed(Transform.PROCESSOR, url, spec);
    }

    private static XML transformed(
        final Processor processor,
        final URL url,
        final XML spec
    ) {
        try (InputStream stream = url.openStream()) {
            final XsltCompiler compiler = processor.newXsltCompiler();
            compiler.setResourceResolver(
                new ResourceResolverWrappingURIResolver(
                    new ClasspathSources(Transform.class)
                )
            );
            final XsltExecutable executable = compiler.compile(
                new StreamSource(stream, url.toExternalForm())
            );
            final XsltTransformer transformer = executable.load();
            transformer.setSource(new DOMSource(spec.inner()));
            final Document target = DocumentBuilderFactory.newInstance()
                .newDocumentBuilder()
                .newDocument();
            transformer.setDestination(new DOMDestination(target));
            transformer.transform();
            return new XMLDocument(target);
        } catch (final SaxonApiException ex) {
            throw new IllegalArgumentException(
                String.format("Failed to apply stylesheet '%s'", url),
                ex
            );
        } catch (final IOException ex) {
            throw new IllegalStateException(
                String.format("Failed to read stylesheet '%s'", url),
                ex
            );
        } catch (final ParserConfigurationException ex) {
            throw new IllegalStateException(
                String.format("Failed to create document builder for '%s'", url),
                ex
            );
        }
    }
}
