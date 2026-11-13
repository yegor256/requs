/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import net.sf.saxon.expr.XPathContext;
import net.sf.saxon.lib.ExtensionFunctionCall;
import net.sf.saxon.lib.ExtensionFunctionDefinition;
import net.sf.saxon.om.Sequence;
import net.sf.saxon.om.StructuredQName;
import net.sf.saxon.trans.XPathException;
import net.sf.saxon.value.SequenceType;
import net.sf.saxon.value.StringValue;
import org.apache.commons.codec.digest.DigestUtils;

/**
 * Saxon extension function that computes an MD5 hash of a string.
 *
 * @since 2.0
 */
final class Md5Hex extends ExtensionFunctionDefinition {

    @Override
    public StructuredQName getFunctionQName() {
        return new StructuredQName(
            "",
            "org.apache.commons.codec.digest.DigestUtils",
            "md5Hex"
        );
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
                return new StringValue(
                    DigestUtils.md5Hex(arguments[0].head().getStringValue())
                );
            }
        };
    }
}
