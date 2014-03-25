/**
 * Copyright (c) 2009-2014, requs.org
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package org.requs;

import com.rexsl.test.XhtmlMatchers;
import java.util.Collections;
import org.apache.commons.lang3.StringUtils;
import org.hamcrest.MatcherAssert;
import org.junit.Test;

/**
 * Test case for {@link Transformed}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
public final class TransformedTest {

    /**
     * Transformed can add metrics.
     */
    @Test
    public void addsMetrics() {
        MatcherAssert.assertThat(
            new Transformed(
                new Spec.Fixed("<spec a='x'/>"),
                Collections.singleton("metrics.xsl")
            ).xml(),
            XhtmlMatchers.hasXPath("/spec[@a]/metrics[ambiguity.overall]")
        );
    }

    /**
     * Transformed can check seals.
     */
    @Test
    public void checksSeals() {
        MatcherAssert.assertThat(
            new Transformed(
                new Spec.Fixed(
                    StringUtils.join(
                        "<spec><method seal='a12ef4'><id>UC5</id><attributes>",
                        "<attribute seal='b89e4e'>invalid</attribute>",
                        "<attribute seal='a12ef4'>valid</attribute>",
                        "</attributes></method><errors/></spec>"
                    )
                ),
                Collections.singleton("seals-check.xsl")
            ).xml(),
            XhtmlMatchers.hasXPaths(
                "/spec/errors[count(error)=1]",
                "/spec/errors/error[contains(.,'a12ef4')]"
            )
        );
    }

}
