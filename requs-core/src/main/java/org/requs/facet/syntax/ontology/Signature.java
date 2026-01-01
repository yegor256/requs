/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Signature of a function call or declaration.
 *
 * @since 1.1
 */
public interface Signature extends Informal {

    /**
     * Sign it.
     * @param text Text to use (in quotes if informal)
     */
    void sign(String text);

    /**
     * Set the object.
     * @param name Variable of the object
     */
    void object(String name);

    /**
     * Result variable.
     * @param name Variable of the result
     */
    void result(String name);

    /**
     * Input argument.
     * @param name Name of the argument
     */
    void input(String name);

}
