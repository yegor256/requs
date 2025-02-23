/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

/**
 * Slot of a type.
 *
 * @since 1.1
 */
public interface Slot extends Mentioned, Informal {

    /**
     * Arity.
     *
     * @since 1.1
     */
    enum Arity {
        /**
         * One or many.
         */
        MANY("1..*"),

        /**
         * Zero or many: 0..*.
         */
        ANY("0..*"),

        /**
         * Strictly one.
         */
        ONE("1");

        /**
         * Mnemo.
         */
        private final transient String text;

        /**
         * Ctor.
         * @param mnemo Mnemo
         */
        Arity(final String mnemo) {
            this.text = mnemo;
        }

        /**
         * Mnemo.
         * @return Mnemo
         */
        public String mnemo() {
            return this.text;
        }
    }

    /**
     * Assign a type to the slot.
     * @param type Type to assign
     */
    void assign(String type);

    /**
     * Set its arity.
     * @param arity Arity to set
     */
    void arity(Slot.Arity arity);

    /**
     * Is it a composition?
     * @param cmp TRUE if it's a composition
     * @since 1.14
     */
    void composition(boolean cmp);

}
