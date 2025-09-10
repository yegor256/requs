/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax.ontology;

import com.jcabi.matchers.XhtmlMatchers;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;
import org.xembly.Directives;
import org.xembly.Xembler;

/**
 * Test case for {@link XeSignature}.
 * @since 1.8
 */
final class XeSignatureTest {

    @Test
    void signsMethod() throws Exception {
        final Directives dirs = new Directives().add("s");
        final Signature signature = new XeSignature(dirs, "/s");
        signature.sign("\"informal one\"");
        MatcherAssert.assertThat(
            "Method signature should be correctly added to XML",
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/s[signature='\"informal one\"']"
            )
        );
    }

}
