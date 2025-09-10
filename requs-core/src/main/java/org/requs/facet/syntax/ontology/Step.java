/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Step.
 *
 * @since 1.1
 */
public interface Step extends Mentioned, Signature {

    /**
     * Exception at a step.
     * @param text Exception text
     * @return Flow for this exception
     */
    Flow exception(String text);

}
