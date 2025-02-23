/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.XML;
import java.io.IOException;

/**
 * Facet.
 *
 * @since 0.1
 */
@Immutable
public interface Facet {

    /**
     * Touch the spec from this facet.
     * @param spec Spec in XML
     * @return New XML
     * @throws IOException If fails on I/O operation
     * @since 1.9
     */
    XML touch(XML spec) throws IOException;

}
