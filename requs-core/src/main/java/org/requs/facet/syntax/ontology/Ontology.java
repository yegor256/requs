/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import org.xembly.Directive;

/**
 * Ontology.
 *
 * <p>The ontology is write-only. This is how you're supposed to use it:
 *
 * <pre>
 * Ontology onto = // make it
 * Type type = onto.type("Employee");
 * type.mention("3-5");
 * type.explain("a person working in a Company");
 * </pre>
 *
 * @since 1.1
 */
public interface Ontology extends Iterable<Directive> {

    /**
     * Found new type.
     * @param name Name of it
     * @return Type
     */
    Type type(String name);

    /**
     * Find method.
     * @param name Name of it
     * @return Method
     */
    Method method(String name);

    /**
     * Find page.
     * @param name Name of it
     * @return Page
     */
    Page page(String name);

    /**
     * Get acronym.
     * @param name Name of it
     * @return Acronym
     */
    Acronym acronym(String name);

}
