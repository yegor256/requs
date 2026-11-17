/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import com.jcabi.xml.XMLDocument;
import net.sf.saxon.Configuration;
import net.sf.saxon.expr.XPathContext;
import net.sf.saxon.om.Item;
import net.sf.saxon.om.NodeInfo;
import net.sf.saxon.om.Sequence;
import net.sf.saxon.s9api.Processor;
import net.sf.saxon.s9api.SaxonApiException;
import net.sf.saxon.s9api.Serializer;
import net.sf.saxon.s9api.XdmNode;
import net.sf.saxon.trans.XPathException;
import org.w3c.dom.Node;

/**
 * Saxon processor with requs extension functions registered.
 *
 * @since 2.0
 */
final class SaxonFunctions {

    /**
     * Utility class.
     */
    private SaxonFunctions() {
    }

    static Processor processor() {
        final Processor processor = new Processor(false);
        final Configuration config = processor.getUnderlyingConfiguration();
        config.registerExtensionFunction(new Seal());
        config.registerExtensionFunction(new Print());
        config.registerExtensionFunction(new Html());
        config.registerExtensionFunction(new Svg());
        config.registerExtensionFunction(new Md5Hex());
        return processor;
    }

    static String xml(final XPathContext context, final Sequence sequence)
        throws XPathException {
        final Item item = sequence.head();
        if (!(item instanceof NodeInfo)) {
            throw new XPathException("a node is expected as the argument");
        }
        final Serializer serializer =
            new Processor(context.getConfiguration()).newSerializer();
        serializer.setOutputProperty(Serializer.Property.METHOD, "xml");
        serializer.setOutputProperty(Serializer.Property.OMIT_XML_DECLARATION, "yes");
        serializer.setOutputProperty(Serializer.Property.INDENT, "no");
        try {
            return serializer.serializeNodeToString(new XdmNode((NodeInfo) item));
        } catch (final SaxonApiException ex) {
            throw new XPathException("failed to convert node to text", ex);
        }
    }

    static Node node(final XPathContext context, final Sequence sequence)
        throws XPathException {
        return new XMLDocument(SaxonFunctions.xml(context, sequence)).inner();
    }
}
