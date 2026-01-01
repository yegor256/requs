/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.sa;

import com.jcabi.matchers.XhtmlMatchers;
import com.jcabi.xml.XMLDocument;
import java.io.IOException;
import org.apache.commons.lang3.StringUtils;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.requs.XeFacet;

/**
 * Test case for {@link Rules}.
 * @since 1.10
 */
final class RulesTest {

    @Test
    void checksInput() throws IOException {
        MatcherAssert.assertThat(
            "Rules should detect multiple style violations in input text",
            new XeFacet.Wrap(new Rules()).touch(
                new XMLDocument(
                    StringUtils.join(
                        "<spec><input>",
                        "User is\ta &quot;human being&quot;.  ",
                        "</input></spec>"
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors",
                "/spec/errors[count(error)>2]"
            )
        );
    }

}
