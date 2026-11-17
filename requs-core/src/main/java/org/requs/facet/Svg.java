/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import java.io.IOException;
import net.sf.saxon.expr.XPathContext;
import net.sf.saxon.lib.ExtensionFunctionCall;
import net.sf.saxon.lib.ExtensionFunctionDefinition;
import net.sf.saxon.om.Sequence;
import net.sf.saxon.om.StructuredQName;
import net.sf.saxon.trans.XPathException;
import net.sf.saxon.value.SequenceType;
import net.sf.saxon.value.StringValue;
import org.requs.facet.uml.Plant;

/**
 * Saxon extension function that renders a PlantUML diagram into SVG.
 *
 * @since 2.0
 */
final class Svg extends ExtensionFunctionDefinition {

    @Override
    public StructuredQName getFunctionQName() {
        return new StructuredQName("", "org.requs.facet.uml.Plant", "svg");
    }

    @Override
    public SequenceType[] getArgumentTypes() {
        return new SequenceType[] {SequenceType.SINGLE_STRING};
    }

    @Override
    public SequenceType getResultType(final SequenceType[] arguments) {
        return SequenceType.SINGLE_STRING;
    }

    @Override
    public ExtensionFunctionCall makeCallExpression() {
        return new ExtensionFunctionCall() {
            @Override
            public Sequence call(
                final XPathContext context,
                final Sequence[] arguments
            ) throws XPathException {
                try {
                    return new StringValue(
                        Plant.svg(arguments[0].head().getStringValue())
                    );
                } catch (final IOException ex) {
                    throw new XPathException(
                        "failed to render PlantUML diagram",
                        ex
                    );
                }
            }
        };
    }
}
