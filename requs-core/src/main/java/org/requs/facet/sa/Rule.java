/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.aspects.Immutable;
import java.util.Collection;

/**
 * Rule.
 *
 * @since 1.10
 */
@Immutable
public interface Rule {

    /**
     * Validate incoming text.
     * @param spec Spec in text format
     * @return Violations
     */
    Collection<Violation> enforce(String spec);

}
