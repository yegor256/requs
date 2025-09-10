/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Type.
 *
 * @since 1.1
 */
public interface Type extends Mentioned, Informal {

    /**
     * Set parent.
     * @param type Name of parent type
     */
    void parent(String type);

    /**
     * Set TRUE if it's an actor.
     * @param act TRUE if an actor
     * @since 1.14
     */
    void actor(boolean act);

    /**
     * Found a slot of the type.
     * @param name Slot name
     * @return Slot
     */
    Slot slot(String name);

}
