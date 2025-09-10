/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.facet.syntax;

import java.util.Iterator;
import org.antlr.v4.runtime.BaseErrorListener;
import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.Recognizer;
import org.xembly.Directive;
import org.xembly.Directives;

/**
 * Syntax analysis.
 *
 * @since 0.1
 * @checkstyle MultipleStringLiteralsCheck (500 lines)
 */
@SuppressWarnings("PMD.AvoidDuplicateLiterals")
final class Errors extends BaseErrorListener implements Iterable<Directive> {

    /**
     * All directives collected.
     */
    private final transient Directives dirs =
        new Directives().xpath("/spec").addIf("errors");

    // @checkstyle ParameterNumberCheck (6 lines)
    @Override
    public void syntaxError(final Recognizer<?, ?> recognizer,
        final Object symbol, final int line, final int pos, final String msg,
        final RecognitionException exc) {
        this.dirs.add("error")
            .attr("type", "syntax")
            .attr("line", Integer.toString(line))
            .attr("pos", Integer.toString(pos))
            .set(msg).up();
    }

    @Override
    public Iterator<Directive> iterator() {
        return this.dirs.iterator();
    }

    /**
     * Add an exception.
     * @param error Exception to add
     * @since 1.4
     */
    public void add(final Exception error) {
        this.dirs.add("error")
            .attr("type", "exception")
            .attr("line", "1")
            .attr("pos", "0")
            .set(error.getLocalizedMessage()).up();
    }

}
