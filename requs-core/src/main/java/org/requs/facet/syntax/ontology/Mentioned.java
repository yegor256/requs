/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Something mentioned in source code.
 *
 * @since 1.1
 */
public interface Mentioned {

    /**
     * Mention it in the given lines of source.
     * @param where Where was it mentioned
     */
    void mention(int where);

}
