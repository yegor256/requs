/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
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
final class IndentationRuleTest {

    @Test
    void checksInput() throws Exception {
        MatcherAssert.assertThat(
            "IndentationRule should accept correct 4-space indentation",
            new IndentationRule().check("    works fine"),
            Matchers.empty()
        );
    }

    @Test
    void checksInvalidInput() throws Exception {
        MatcherAssert.assertThat(
            "IndentationRule should detect incorrect 3-space indentation",
            new IndentationRule().check("   works fine"),
            Matchers.not(Matchers.empty())
        );
    }

}
