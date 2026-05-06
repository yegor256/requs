/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
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
     * Add a new step with the given number, even if a step with that
     * number already exists. Used by the parser to record duplicate
     * step numbers in source so they can be reported as errors.
     * @param number Number of the step
     * @return Step
     */
    default Step addStep(final int number) {
        return this.step(number);
    }

    /**
     * Declare a binding used in the method.
     * @param name Unique name of it
     * @param type Type of it
     */
    void binding(String name, String type);

}
