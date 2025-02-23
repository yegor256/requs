/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Flow.
 *
 * @since 1.1
 */
public interface Flow extends Informal {

    /**
     * SELF binding.
     */
    String SELF = "_self";

    /**
     * Get its step by number.
     * @param number Number of the step
     * @return Step
     */
    Step step(int number);

    /**
     * Declare a binding used in the method.
     * @param name Unique name of it
     * @param type Type of it
     */
    void binding(String name, String type);

}
