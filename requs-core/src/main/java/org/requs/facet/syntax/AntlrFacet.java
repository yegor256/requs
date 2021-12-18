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
package org.requs.facet.syntax;

import com.jcabi.aspects.Immutable;
import com.jcabi.xml.XML;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.TokenStream;
import org.requs.XeFacet;
import org.requs.facet.syntax.ontology.Ontology;
import org.requs.facet.syntax.ontology.XeOntology;
import org.xembly.Directive;
import org.xembly.Directives;

/**
 * Syntax analysis.
 *
 * @checkstyle ClassDataAbstractionCouplingCheck (500 lines)
 * @since 0.1
 */
@Immutable
@ToString
@EqualsAndHashCode
public final class AntlrFacet implements XeFacet {

    @Override
    public Iterable<Directive> touch(final XML spec) {
        final SpecLexer lexer = new SpecLexer(
            CharStreams.fromString(spec.xpath("/spec/input/text()").get(0))
        );
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
        } catch (final RecognitionException | SyntaxException
            | StringIndexOutOfBoundsException ex) {
            errors.add(ex);
        }
        return new Directives().append(onto).append(errors);
    }

}
