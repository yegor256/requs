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

import com.google.common.io.Files;
import com.jcabi.aspects.Loggable;
import com.jcabi.log.Logger;
import com.jcabi.xml.XMLDocument;
import java.io.File;
import java.io.IOException;
import javax.validation.constraints.NotNull;
import javax.ws.rs.FormParam;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.CharEncoding;

/**
 * Instant syntax parser.
 *
 * <p>The class is mutable and NOT thread-safe.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
@Path("/instant")
public final class InstantRs extends BaseRs {

    /**
     * Parse text.
     * @param text Requs syntax to parse
     * @return The JAX-RS response
     * @throws IOException If fails
     */
    @POST
    @Path("/")
    @Produces(MediaType.APPLICATION_XML)
    @Loggable(Loggable.INFO)
    public String post(@NotNull @FormParam("text") final String text)
        throws IOException {
        final File input = Files.createTempDir();
        FileUtils.write(new File(input, "in.req"), text, CharEncoding.UTF_8);
        final File output = Files.createTempDir();
        String xml;
        try {
            new org.requs.Compiler(input, output).compile();
            xml = FileUtils.readFileToString(
                new File(output, "main.xml"),
                CharEncoding.UTF_8
            );
        } catch (final IllegalArgumentException ex) {
            xml = Logger.format("%[exception]s", ex);
        }
        FileUtils.deleteDirectory(input);
        FileUtils.deleteDirectory(output);
        return new XMLDocument(xml).nodes("/spec").get(0).toString();
    }

}
