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

import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Loggable;
import com.jcabi.log.Logger;
import java.io.File;
import java.io.IOException;
import javax.validation.constraints.NotNull;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.requs.facet.Transform;
import org.requs.facet.ambiguity.Overall;
import org.requs.facet.decor.Aggregate;
import org.requs.facet.decor.Scaffolding;
import org.requs.facet.markdown.MdMethods;
import org.requs.facet.sanity.Sealed;
import org.requs.facet.syntax.AntlrFacet;
import org.requs.facet.tbd.Tbds;

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
        final Facet[] facets = {
            new Scaffolding(),
            new Aggregate(new File(this.input)),
            new AntlrFacet(),
            new Sealed(),
            new Transform("sanity/signatures-check.xsl"),
            new Transform("sanity/types-check.xsl"),
            new Transform("sanity/seals-check.xsl"),
            new MdMethods(),
            new Overall(),
            new Tbds(),
        };
        final Docs docs = new Docs.InDir(new File(this.output));
        for (final Facet facet : facets) {
            facet.touch(docs);
            Logger.info(this, "%s done", facet);
        }
        Logger.info(this, "compiled and saved to %s", this.output);
    }

}
