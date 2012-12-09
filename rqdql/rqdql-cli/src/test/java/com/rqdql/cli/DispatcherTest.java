/**
 * Copyright (c) 2009-2011, RQDQL.com
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
package com.rqdql.cli;

import nu.xom.Builder;
import nu.xom.Document;
import nu.xom.Nodes;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.Ignore;
import org.junit.Test;

/**
 * Test case for {@link Dispatcher}.
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class DispatcherTest {

    /**
     * Dispatcher can work.
     * @throws Exception When necessary
     */
    @Test
    public void testGetsVersionNumber() throws Exception {
        final String out = new Dispatcher().dispatch(
            new String[] {"-v"},
            ""
        );
        MatcherAssert.assertThat(out, Matchers.containsString("2.0"));
    }

    /**
     * Dispatcher can work.
     * @throws Exception When necessary
     */
    @Test
    public void testGetsHelpMessage() throws Exception {
        final String out = new Dispatcher().dispatch(
            new String[] {"-?"},
            ""
        );
        MatcherAssert.assertThat(out, Matchers.containsString("usage:"));
    }

    /**
     * Dispatcher can work.
     * @throws Exception When necessary
     */
    @Test
    public void testRunsSimpleReportSet() throws Exception {
        final String[] args = {"errors", "metrics"};
        final String input = "ActorUser is a \"human being\".";
        final String xml = new Dispatcher().dispatch(args, input);
        MatcherAssert.assertThat(xml, Matchers.containsString("<?xml"));
    }

    /**
     * Dispatcher can work.
     * @throws Exception When necessary
     * @todo #3 Resolve the ticket, and implement everything
     *  properly with ANTLR3 parser.
     */
    @Ignore
    @Test
    public void testParsesANumberOfSpecifications() throws Exception {
        final String[] files = {
            "SRS-BookStore.xml",
        };
        for (String file : files) {
            this.parse(file);
        }
    }

    /**
     * Parse resource file.
     * @param file The file name (resource)
     * @throws Exception When necessary
     */
    private void parse(final String file) throws Exception {
        final Document dom = new Builder().build(
            this.getClass().getResourceAsStream(file)
        );
        final String input = dom.query("//SRS").get(0).getValue();
        final Nodes reporters = dom.query("//reporters/reporter");
        final int total = reporters.size();
        final String[] reports = new String[total];
        for (int idx = 0; idx < total; idx += 1) {
            reports[idx] = reporters.get(idx).getValue();
        }
        final String xml = new Dispatcher().dispatch(reports, input);
        final Document report = new Builder().build(xml, null);
        final Nodes invariants = dom.query("//invariants/invariant");
        for (int idx = 0; idx < invariants.size(); idx += 1) {
            final String xpath = invariants.get(idx).getValue();
            MatcherAssert.assertThat(
                report.query(xpath).size(),
                Matchers.describedAs(xpath, Matchers.greaterThan(0))
            );
        }
    }

}
