/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax;

/**
 * Syntax exception.
 *
 * @since 1.4
 */
final class SyntaxException extends RuntimeException {

    /**
     * Serialization marker.
     */
    private static final long serialVersionUID = 1497953278746134529L;

    /**
     * Ctor.
     * @param cause Cause of it
     */
    SyntaxException(final String cause) {
        super(cause);
    }

}
