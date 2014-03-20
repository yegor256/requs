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
package org.requs.exec;

import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import com.jcabi.log.Logger;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import javax.validation.constraints.NotNull;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.CharEncoding;
import org.requs.Spec;

/**
 * Compiler.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @checkstyle ClassDataAbstractionCoupling (500 lines)
 * @since 1.1
 */
@Immutable
@ToString
@EqualsAndHashCode(of = { "input", "output" })
@Loggable(Loggable.DEBUG)
public final class Compiler {

    /**
     * Source folder.
     */
    private final transient String input;

    /**
     * Output folder.
     */
    private final transient String output;

    /**
     * Ctor.
     * @param src Directory with sources
     * @param dest Directory to write output
     * @throws IOException If fails
     */
    public Compiler(@NotNull final File src, @NotNull final File dest)
        throws IOException {
        this.input = src.getAbsolutePath();
        this.output = dest.getAbsolutePath();
        if (!src.exists()) {
            throw new IOException(
                String.format("directory \"%s\" is absent", this.input)
            );
        }
        if (dest.mkdirs()) {
            Logger.info(
                Compiler.class, "output directory \"%s\" created",
                this.output
            );
        }
    }

    /**
     * Compile.
     * @throws IOException If fails
     */
    public void compile() throws IOException {
        FileUtils.write(
            new File(this.output, "srs.xml"),
            new Spec(this.source()).xml().toString(),
            CharEncoding.UTF_8
        );
        FileUtils.write(
            // @checkstyle MultipleStringLiteralsCheck (1 line)
            new File(this.output, "srs.xsl"),
            IOUtils.toString(
                this.getClass().getResourceAsStream("srs.xsl"),
                CharEncoding.UTF_8
            ),
            CharEncoding.UTF_8
        );
        Logger.info(this, "compiled and saved to %s", this.output);
    }

    /**
     * Read XML.
     * @return The output
     * @throws IOException If something goes wrong
     */
    private String source() throws IOException {
        final StringBuilder text = new StringBuilder(0);
        final Collection<File> files = FileUtils.listFiles(
            new File(this.input), new String[] {"req"}, true
        );
        for (final File file : files) {
            text.append(
                FileUtils.readFileToString(file, CharEncoding.UTF_8)
            ).append('\n');
        }
        return text.toString();
    }

}
