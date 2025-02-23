/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
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
public final class XeSignatureTest {

    @Test
    public void signsMethod() throws Exception {
        final Directives dirs = new Directives().add("s");
        final Signature signature = new XeSignature(dirs, "/s");
        signature.sign("\"informal one\"");
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(new Xembler(dirs).xml()),
            XhtmlMatchers.hasXPaths(
                "/s[signature='\"informal one\"']"
            )
        );
    }

}
