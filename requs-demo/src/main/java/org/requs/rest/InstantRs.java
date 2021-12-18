/*
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

import com.google.common.io.Files;
import com.jcabi.aspects.Loggable;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import com.jcabi.xml.XSL;
import com.jcabi.xml.XSLDocument;
import java.io.File;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.nio.charset.StandardCharsets;
import javax.json.Json;
import javax.validation.constraints.NotNull;
import javax.ws.rs.FormParam;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.WebApplicationException;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.exception.ExceptionUtils;

/**
 * Instant syntax parser.
 *
 * <p>The class is mutable and NOT thread-safe.
 *
 * @since 0.1
 */
@Path("/instant")
public final class InstantRs extends BaseRs {

    /**
     * Parse text.
     * @param text Requs syntax to parse
     * @return The JAX-RS response
     * @throws IOException If fails
     * @checkstyle NonStaticMethodCheck (10 lines)
     */
    @POST
    @Path("/")
    @Produces(MediaType.APPLICATION_JSON)
    @Loggable
    @SuppressWarnings("PMD.AvoidCatchingGenericException")
    public String post(@NotNull @FormParam("text") final String text)
        throws IOException {
        final File input = Files.createTempDir();
        FileUtils.write(
            new File(input, "in.req"),
            text,
            StandardCharsets.UTF_8
        );
        final File output = Files.createTempDir();
        try {
            new org.requs.Compiler(input, output).compile();
            final XML xml = new XMLDocument(
                FileUtils.readFileToString(
                    new File(output, "requs.xml"),
                    StandardCharsets.UTF_8
                )
            );
            final XSL xsl = new XSLDocument(
                FileUtils.readFileToString(
                    new File(output, "requs.xsl"),
                    StandardCharsets.UTF_8
                )
            );
            return Json.createObjectBuilder()
                .add("spec", xml.nodes("/spec").get(0).toString())
                .add("html", xsl.applyTo(xml))
                .build().toString();
            // @checkstyle IllegalCatchCheck (1 line)
        } catch (final RuntimeException ex) {
            throw new WebApplicationException(
                Response.status(HttpURLConnection.HTTP_INTERNAL_ERROR)
                    .entity(ExceptionUtils.getStackTrace(ex))
                    .build()
            );
        } finally {
            FileUtils.deleteDirectory(input);
            FileUtils.deleteDirectory(output);
        }
    }

}
