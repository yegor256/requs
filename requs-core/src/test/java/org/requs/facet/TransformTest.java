/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet;

import com.jcabi.matchers.XhtmlMatchers;
import com.jcabi.xml.XMLDocument;
import org.apache.commons.lang3.StringUtils;
import org.hamcrest.MatcherAssert;
import org.junit.jupiter.api.Test;

/**
 * Test case for {@link Transform}.
 * @since 0.1
 */
public final class TransformTest {

    @Test
    public void checksSeals() {
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(
                new Transform("sanity/seals-check.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><method seal='a12ef4'>",
                            "<id>UC5</id><attributes>",
                            "<attribute seal='b89e4e'>invalid</attribute>",
                            "<attribute seal='a12ef4'>valid</attribute>",
                            "</attributes></method><errors/></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1]",
                "/spec/errors/error[contains(.,'a12ef4')]"
            )
        );
    }

    @Test
    public void checksTypes() {
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(
                new Transform("sanity/types-check.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><types><type><name>User</name>",
                            "<slots><slot><type>Alpha</type></slot></slots>",
                            "</type></types><methods><method><bindings>",
                            "<binding><type>Beta</type></binding>",
                            "</bindings></method></methods><errors/></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=2]",
                "/spec/errors/error[contains(.,'Alpha')]"
            )
        );
    }

    @Test
    public void checksSignatures() {
        MatcherAssert.assertThat(
            XhtmlMatchers.xhtml(
                new Transform("sanity/signatures-check.xsl").touch(
                    new XMLDocument(
                        StringUtils.join(
                            "<spec><methods><method><signature>abc</signature>",
                            "</method><method><steps><step><signature>cde",
                            "</signature></step></steps></method></methods>",
                            "<errors/></spec>"
                        )
                    )
                )
            ),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1 ]",
                "/spec/errors/error[contains(.,'cde')]"
            )
        );
    }

}
