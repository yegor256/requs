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
 * Test case for {@link CascadingRule}.
 * @since 1.14
 */
public final class CascadingRuleTest {

    @Test
    public void checksInput() {
        MatcherAssert.assertThat(
            new CascadingRule().enforce("hey\n  works\n    fine\nstart"),
            Matchers.empty()
        );
    }

    @Test
    public void checksInvalidInput() {
        MatcherAssert.assertThat(
            new CascadingRule().enforce(
                "\n\n\n  hey\n   three!"
            ).iterator().next().line(),
            Matchers.equalTo(Tv.FIVE)
        );
    }

}
