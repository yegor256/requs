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
import com.jcabi.manifests.Manifests;
import com.jcabi.xml.StrictXML;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import com.jcabi.xml.XSD;
import com.jcabi.xml.XSDDocument;
import java.io.File;
import java.io.IOException;
import java.util.Date;
import javax.validation.constraints.NotNull;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.CharEncoding;
import org.apache.commons.lang3.time.DateFormatUtils;
import org.requs.facet.Aggregate;
import org.requs.facet.Transform;
import org.requs.facet.sa.Rules;
import org.requs.facet.syntax.AntlrFacet;
import org.xembly.Directive;
import org.xembly.Directives;

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
     * XSD.
     */
    public static final XSD SCHEMA = XSDDocument.make(
        Compiler.class.getResource("requs.xsd")
    );

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
        final long start = System.currentTimeMillis();
        final Facet[] facets = {
            new XeFacet.Wrap(new Aggregate(new File(this.input))),
            new XeFacet.Wrap(new AntlrFacet()),
            new Transform("cleanup/lost-steps.xsl"),
            new Transform("cleanup/lost-methods.xsl"),
            new Transform("cleanup/duplicate-signatures.xsl"),
            new Transform("cleanup/duplicate-method-signatures.xsl"),
            new Transform("cleanup/duplicate-method-objects.xsl"),
            new Transform("cleanup/duplicate-method-bindings.xsl"),
            new Transform("cleanup/incomplete-steps-object.xsl"),
            new Transform("cleanup/incomplete-steps-signature.xsl"),
            new Transform("cleanup/incomplete-binding.xsl"),
            new Transform("seal-methods.xsl"),
            new Transform("sanity/signatures-check.xsl"),
            new Transform("sanity/types-check.xsl"),
            new Transform("sanity/seals-check.xsl"),
            new Transform("methods-in-markdown.xsl"),
            new Transform("pages-in-html.xsl"),
            new Transform("count-ambiguity.xsl"),
            new Transform("find-tbds.xsl"),
            new XeFacet.Wrap(new Rules()),
            new XeFacet.Wrap(
                new XeFacet() {
                    @Override
                    public Iterable<Directive> touch(final XML spec) {
                        return new Directives().xpath("/*").attr(
                            "msec",
                            Long.toString(System.currentTimeMillis() - start)
                        );
                    }
                }
            ),
            new XeFacet.Wrap(new XeFacet.Fixed(Compiler.decor())),
        };
        XML spec = new XMLDocument(
            "<?xml-stylesheet href='requs.xsl' type='text/xsl'?><spec/>"
        );
        for (final Facet facet : facets) {
            spec = facet.touch(spec);
            Logger.info(this, "%s done", facet);
        }
        this.copy();
        FileUtils.write(
            new File(this.output, "requs.xml"),
            new StrictXML(spec, Compiler.SCHEMA).toString(),
            CharEncoding.UTF_8
        );
        Logger.info(this, "compiled and saved to %s", this.output);
    }

    /**
     * Copy XSL.
     * @throws IOException If fails
     */
    private void copy() throws IOException {
        final String file = "requs.xsl";
        final String xsl = IOUtils.toString(
            this.getClass().getResourceAsStream(file),
            CharEncoding.UTF_8
        );
        FileUtils.write(
            new File(this.output, file),
            xsl.replace(
                "---css---",
                IOUtils.toString(
                    this.getClass().getResourceAsStream("requs.css"),
                    CharEncoding.UTF_8
                )
            ),
            CharEncoding.UTF_8
        );
    }

    /**
     * Decorating directives.
     * @return Directives
     */
    private static Iterable<Directive> decor() {
        return new Directives()
            .xpath("/spec")
            .attr(
                "time",
                DateFormatUtils.ISO_DATETIME_FORMAT.format(new Date())
            )
            .add("requs")
            .add("version").set(Manifests.read("Requs-Version")).up()
            .add("revision").set(Manifests.read("Requs-Revision")).up()
            .add("date").set(Manifests.read("Requs-Date")).up().up();
    }

}
