/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;

/**
 * Test case for {@link RegexRule}.
 * @since 1.14
 */
public final class RegexRuleTest {

    @Test
    public void checksInput() throws Exception {
        MatcherAssert.assertThat(
            new RegexRule("[a-z]+", "").check("abjkljeklsf"),
            Matchers.not(Matchers.empty())
        );
    }

    @Test
    public void checksInvalidInput() throws Exception {
        MatcherAssert.assertThat(
            new RegexRule("[0-9]", "").check("broken input"),
            Matchers.empty()
        );
    }

}
