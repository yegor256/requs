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
package org.requs.facet.syntax;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.StrictXML;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import com.jcabi.xml.XSD;
import com.jcabi.xml.XSDDocument;
import com.jcabi.xml.XSLDocument;
import java.io.IOException;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.TokenStream;
import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.CharEncoding;
import org.requs.Doc;
import org.requs.Docs;
import org.requs.Facet;
import org.requs.facet.syntax.ontology.Ontology;
import org.requs.facet.syntax.ontology.XeOntology;
import org.xembly.Directives;
import org.xembly.ImpossibleModificationException;
import org.xembly.Xembler;

/**
 * Syntax analysis.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @checkstyle ClassDataAbstractionCouplingCheck (500 lines)
 */
@Immutable
@ToString(of = { })
@EqualsAndHashCode
public final class AntlrFacet implements Facet {

    /**
     * XSD.
     */
    private static final XSD SCHEMA = XSDDocument.make(
        AntlrFacet.class.getResource("main.xsd")
    );

    @Override
    public void touch(final Docs docs) throws IOException {
        final Doc main = docs.get("main.xml");
        main.write(this.compile(docs.get("input.req").read()).toString());
        main.name("srs", "Software Requirements Specification, Main Document");
        // @checkstyle MultipleStringLiteralsCheck (1 line)
        docs.get("main.xsl").write(
            IOUtils.toString(
                this.getClass().getResourceAsStream("main.xsl"),
                CharEncoding.UTF_8
            )
        );
    }

    /**
     * Build main XML.
     * @param input Requs syntax
     * @return XML built
     */
    private XML compile(final String input) {
        final SpecLexer lexer = new SpecLexer(new ANTLRInputStream(input));
        final TokenStream tokens = new CommonTokenStream(lexer);
        final SpecParser parser = new SpecParser(tokens);
        final Errors errors = new Errors();
        lexer.removeErrorListeners();
        lexer.addErrorListener(errors);
        parser.removeErrorListeners();
        parser.addErrorListener(errors);
        final Ontology onto = new XeOntology();
        parser.setOntology(onto);
        try {
            parser.clauses();
        } catch (final RecognitionException ex) {
            errors.add(ex);
        } catch (final SyntaxException ex) {
            errors.add(ex);
        }
        final XML xml;
        try {
            xml = AntlrFacet.cleanup(
                new XMLDocument(
                    new Xembler(
                        new Directives()
                            .xpath("/")
                            .pi(
                                "xml-stylesheet",
                                "href='main.xsl' type='text/xsl'"
                            )
                            .append(onto).append(errors)
                    ).xml()
                )
            );
        } catch (final ImpossibleModificationException ex) {
            throw new IllegalStateException(ex);
        }
        return new StrictXML(xml, AntlrFacet.SCHEMA);
    }

    /**
     * Cleanup the XML.
     * @param xml Raw xml after syntax processing
     * @return Clean XML, compliant to XSD
     */
    private static XML cleanup(final XML xml) {
        final String[] sheets = {
            "cleanup/lost-steps.xsl",
            "cleanup/lost-methods.xsl",
            "cleanup/duplicate-signatures.xsl",
            "cleanup/duplicate-method-objects.xsl",
        };
        XML clean = xml;
        for (final String sheet : sheets) {
            clean = XSLDocument.make(
                AntlrFacet.class.getResourceAsStream(sheet)
            ).transform(clean);
        }
        return clean;
    }

}
