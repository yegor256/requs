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
package com.rqdql.syntax;

import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import com.rqdql.ontology.XeOntology;
import javax.validation.constraints.NotNull;
import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CharStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.TokenStream;
import org.xembly.ImpossibleModificationException;
import org.xembly.Xembler;

/**
 * Syntax analysis.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 */
public final class AntlrSpec {

    /**
     * Text to parse.
     */
    private final transient String text;

    /**
     * Public ctor.
     * @param content The text to parse
     */
    public AntlrSpec(@NotNull final String content) {
        this.text = content;
    }

    /**
     * Get all clauses found in the text.
     * @return Clauses found
     */
    public XML xml() {
        final CharStream input = new ANTLRStringStream(this.text);
        final SpecLexer lexer = new SpecLexer(input);
        final TokenStream tokens = new CommonTokenStream(lexer);
        final SpecParser parser = new SpecParser(tokens);
        final XeOntology onto = new XeOntology();
        parser.setOntology(onto);
        try {
            parser.clauses();
        } catch (final RecognitionException ex) {
            throw new IllegalArgumentException(ex);
        }
        try {
            return new XMLDocument(new Xembler(onto).xml());
        } catch (final ImpossibleModificationException ex) {
            throw new IllegalStateException(ex);
        }
    }

}
