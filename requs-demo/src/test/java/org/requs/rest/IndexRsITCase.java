/**
 * Copyright (c) 2009-2021, Yegor Bugayenko
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

import com.jcabi.http.request.JdkRequest;
import com.jcabi.http.response.RestResponse;
import com.jcabi.http.response.XmlResponse;
import com.jcabi.matchers.NoBrokenLinks;
import java.net.HttpURLConnection;
import java.net.URI;
import javax.ws.rs.core.HttpHeaders;
import javax.ws.rs.core.MediaType;
import org.junit.Ignore;
import org.junit.Test;

/**
 * Integration case for {@link IndexRs}.
 * @author Yegor Bugayenko (yegor256@gmail.com)
 * @version $Id$
 * @since 1.6
 */
@SuppressWarnings("PMD.AvoidInstantiatingObjectsInLoops")
public final class IndexRsITCase {

    /**
     * Tomcat home.
     */
    private static final String HOME = System.getProperty("tomcat.home");

    /**
     * IndexRs can hit public pages.
     * @throws Exception If some problem inside
     */
    @Test
    public void hitsPublicPages() throws Exception {
        final String[] pages = {
            "/",
            "/robots.txt",
            "/xsl/layout.xsl",
            "/xsl/index.xsl",
            "/css/style.css",
        };
        for (final String page : pages) {
            new JdkRequest(IndexRsITCase.HOME)
                .uri().path(page).back()
                .header("accept", "text/plain")
                .fetch()
                .as(RestResponse.class)
                .assertStatus(HttpURLConnection.HTTP_OK);
        }
    }

    /**
     * IndexRs can hit not-found pages.
     * @throws Exception If some problem inside
     */
    @Test
    @Ignore
    public void hitsAbsentPages() throws Exception {
        final String[] pages = {
            "/page-doesnt-exist",
            "/xsl/xsl-stylesheet-doesnt-exist.xsl",
            "/css/stylesheet-is-absent.css",
        };
        for (final String page : pages) {
            new JdkRequest(IndexRsITCase.HOME)
                .uri().path(page).back()
                .fetch()
                .as(RestResponse.class)
                .assertStatus(HttpURLConnection.HTTP_NOT_FOUND)
                .as(XmlResponse.class)
                .assertXPath("//xhtml:h1[contains(.,'Page not found')]");
        }
    }

    /**
     * IndexRs can render version.
     * @throws Exception If some problem inside
     */
    @Test
    public void rendersVersion() throws Exception {
        new JdkRequest(IndexRsITCase.HOME)
            .header(HttpHeaders.ACCEPT, MediaType.APPLICATION_XML)
            .fetch()
            .as(RestResponse.class)
            .assertStatus(HttpURLConnection.HTTP_OK)
            .assertThat(new NoBrokenLinks(URI.create(IndexRsITCase.HOME)))
            .as(XmlResponse.class)
            .assertXPath("/page/version");
    }

    /**
     * IndexRs can render exception.
     * @throws Exception If some problem inside
     */
    @Test
    public void rendersException() throws Exception {
        new JdkRequest(IndexRsITCase.HOME)
            .uri().path("/trap").back()
            .fetch()
            .as(RestResponse.class)
            .assertStatus(HttpURLConnection.HTTP_OK)
            .as(XmlResponse.class)
            .assertXPath("//xhtml:title[.='Internal application error']");
    }

}
