/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;

/**
 * Test case for {@link IndentationRule}.
 * @since 1.14
 */
public final class IndentationRuleTest {

    @Test
    public void checksInput() throws Exception {
        MatcherAssert.assertThat(
            new IndentationRule().check("    works fine"),
            Matchers.empty()
        );
    }

    @Test
    public void checksInvalidInput() throws Exception {
        MatcherAssert.assertThat(
            new IndentationRule().check("   works fine"),
            Matchers.not(Matchers.empty())
        );
    }

}
