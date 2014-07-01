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
import com.jcabi.immutable.ArrayMap;
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
import java.util.Map;
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
     * Map of properties.
     */
    private final transient ArrayMap<String, String> properties;

    /**
     * Ctor.
     * @param src Directory with sources
     * @param dest Directory to write output
     * @throws IOException If fails
     */
    public Compiler(final File src, final File dest) throws IOException {
        this(src, dest, new ArrayMap<String, String>());
    }

    /**
     * Ctor.
     * @param src Directory with sources
     * @param dest Directory to write output
     * @param props Properties
     * @throws IOException If fails
     * @since 1.14
     */
    public Compiler(@NotNull final File src, @NotNull final File dest,
        @NotNull final Map<String, String> props) throws IOException {
        this.input = src.getAbsolutePath();
        this.output = dest.getAbsolutePath();
        this.properties = new ArrayMap<String, String>(props);
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
        assert this.properties != null;
        final long start = System.currentTimeMillis();
        final Facet[] facets = {
            new XeFacet.Wrap(new Aggregate(new File(this.input))),
            new XeFacet.Wrap(new AntlrFacet()),
            new Transform("cleanup/duplicate-step-numbers.xsl"),
            new Transform("cleanup/duplicate-step-signatures.xsl"),
            new Transform("cleanup/duplicate-step-objects.xsl"),
            new Transform("cleanup/duplicate-step-results.xsl"),
            new Transform("cleanup/lost-steps.xsl"),
            new Transform("cleanup/lost-methods.xsl"),
            new Transform("cleanup/duplicate-signatures.xsl"),
            new Transform("cleanup/duplicate-method-signatures.xsl"),
            new Transform("cleanup/duplicate-method-objects.xsl"),
            new Transform("cleanup/duplicate-method-bindings.xsl"),
            new Transform("cleanup/incomplete-step-object.xsl"),
            new Transform("cleanup/incomplete-step-signature.xsl"),
            new Transform("cleanup/incomplete-step-result.xsl"),
            new Transform("cleanup/incomplete-binding.xsl"),
            new Transform("cleanup/bindings-in-exception.xsl"),
            new Transform("seal-methods.xsl"),
            new Transform("sanity/signatures-check.xsl"),
            new Transform("sanity/types-check.xsl"),
            new Transform("sanity/seals-check.xsl"),
            new Transform("sanity/exception-rethrow-check.xsl"),
            new Transform("sanity/misplaced-failure-check.xsl"),
            new Transform("sanity/broken-order-of-steps.xsl"),
            new Transform("sanity/missed-step-numbers.xsl"),
            new Transform("sanity/too-many-steps.xsl"),
            new Transform("sanity/empty-re-throws.xsl"),
            new Transform("sanity/orphan-types.xsl"),
            new Transform("sanity/undeclared-bindings.xsl"),
            new Transform("sanity/actor-is-singleton.xsl"),
            new Transform("step-refs.xsl"),
            new Transform("methods-in-markdown.xsl"),
            new Transform("pages-in-html.xsl"),
            new Transform("count-ambiguity.xsl"),
            new Transform("find-tbds.xsl"),
            new Transform("uml/sequence-diagrams.xsl"),
            new Transform("uml/use-case-diagrams.xsl"),
            new Transform("uml/class-diagrams.xsl"),
            new XeFacet.Wrap(new Rules()),
            new XeFacet.Wrap(new XeFacet.Fixed(Compiler.decor())),
            new Transform("renumber.xsl"),
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
                "css-included-here",
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
