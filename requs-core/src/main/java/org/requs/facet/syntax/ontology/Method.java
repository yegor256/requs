/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Use case.
 *
 * @since 1.1
 */
public interface Method extends Flow, Mentioned, Signature {

    /**
     * Add an attributes.
     * @param name Attribute name
     * @param seal Seal to attach
     */
    void attribute(String name, String seal);

    /**
     * Get an NFR by name.
     * @param name NFR name
     * @return NFR
     */
    Nfr nfr(String name);

}
