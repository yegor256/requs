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
package org.requs.rest;

import com.jcabi.http.Request;
import com.jcabi.http.request.JdkRequest;
import com.jcabi.http.response.RestResponse;
import com.jcabi.http.response.XmlResponse;
import java.net.HttpURLConnection;
import org.apache.commons.lang3.StringUtils;
import org.junit.Test;

/**
 * Integration case for {@link InstantRs}.
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.6
 */
public final class InstantRsITCase {

    /**
     * Tomcat home.
     */
    private static final String HOME = System.getProperty("tomcat.home");

    /**
     * InstantRs can process a Requs spec.
     * @throws Exception If some problem inside
     */
    @Test
    public void processesRequsSpec() throws Exception {
        final String spec = StringUtils.join(
            "Fraction is a \"math calculator\".",
            "Fraction needs:",
            "numerator as Float, and",
            "denominator as Float.",
            "UC1 where User (a user) divides two numbers:",
            "1. The user creates Fraction (a fraction);",
            "2. The fraction \"calculates\" Float (a quotient);",
            "3. The user \"receives results\" using the quotient.",
            "UC1/2 when \"division by zero\":",
            "1. Fail since \"denominator can't be zero\".",
            "UC1/PERF must \"be 700 msec per HTTP request\"."
        );
        new JdkRequest(InstantRsITCase.HOME)
            .uri().path("/instant").back()
            .body().formParam("text", spec).back()
            .method(Request.POST)
            .fetch()
            .as(RestResponse.class)
            .assertStatus(HttpURLConnection.HTTP_OK)
            .as(XmlResponse.class)
            .assertXPath("/spec/types/type[name='Fraction']");
    }

}
