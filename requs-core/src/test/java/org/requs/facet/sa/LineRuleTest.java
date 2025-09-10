/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.aspects.Tv;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;

/**
 * Test case for {@link LineRule}.
 * @since 1.14
 */
final class LineRuleTest {

    @Test
    void checksInvalidInput() throws Exception {
        MatcherAssert.assertThat(
            "LineRule should correctly identify line number of violation",
            new LineRule.Wrap(new RegexRule("[a-z]+", "")).enforce(
                "\n\n\nhey"
            ).iterator().next().line(),
            Matchers.equalTo(Tv.FOUR)
        );
    }

}
