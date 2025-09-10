/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
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
final class RegexRuleTest {

    @Test
    void checksInput() throws Exception {
        MatcherAssert.assertThat(
            "RegexRule should detect violations when input matches pattern",
            new RegexRule("[a-z]+", "").check("abjkljeklsf"),
            Matchers.not(Matchers.empty())
        );
    }

    @Test
    void checksInvalidInput() throws Exception {
        MatcherAssert.assertThat(
            "RegexRule should return empty result when input does not match pattern",
            new RegexRule("[0-9]", "").check("broken input"),
            Matchers.empty()
        );
    }

}
