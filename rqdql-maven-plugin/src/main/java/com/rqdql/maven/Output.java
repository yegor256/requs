/**
 * Copyright (c) 2009-2013, RQDQL.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the RQDQL.com nor
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
package com.rqdql.maven;

import com.jcabi.xml.XML;
import com.rqdql.Spec;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import javax.validation.constraints.NotNull;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.CharEncoding;

/**
 * Output XML.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.1
 */
@ToString
@EqualsAndHashCode
final class Output {

    /**
     * Source folder.
     */
    private final transient File dir;

    /**
     * Ctor.
     * @param path Directory path
     */
    Output(@NotNull final File path) {
        this.dir = path;
    }

    /**
     * Build output.
     * @return XML
     * @throws IOException If fails
     */
    public XML build() throws IOException {
        return new Spec(this.source()).xml();
    }

    /**
     * Read XML.
     * @return The output
     * @throws IOException If something goes wrong
     */
    private String source() throws IOException {
        if (!this.dir.exists()) {
            throw new IOException(
                String.format("directory %s is absent", this.dir)
            );
        }
        final StringBuilder text = new StringBuilder(0);
        final Collection<File> files = FileUtils.listFiles(
            this.dir, new String[] {"r"}, true
        );
        for (final File file : files) {
            text.append(
                FileUtils.readFileToString(file, CharEncoding.UTF_8)
            ).append('\n');
        }
        return text.toString();
    }

}
