/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
 * @since 0.1
 * @checkstyle ClassDataAbstractionCouplingCheck (500 lines)
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
