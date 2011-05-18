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

import org.junit.*;
import static org.junit.Assert.*;
import nu.xom.*;
import com.rqdql.tk.ResourceLoader;

/**
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public class DispatcherTest {

    @Test
    public void testGetsVersionNumber() throws Exception {
        String out = new Dispatcher().dispatch(
            new String[] { "-v" },
            ""
        );
    }

    @Test
    public void testGetsHelpMessage() throws Exception {
        String out = new Dispatcher().dispatch(
            new String[] { "-?" },
            ""
        );
    }

    @Test
    public void testRunsSimpleReportSet() throws Exception {
        String[] args = { "errors", "metrics" };
        String input = "ActorUser is a \"human being\".";
        String xml = new Dispatcher().dispatch(args, input);
    }

    /**
     * @todo #3 Resolve the ticket, and implement everything
     *          properly with ANTLR3 parser.
     */
    @Ignore
    @Test
    public void testParsesANumberOfSpecifications() throws Exception {
        String[] files = {
            "SRS-BookStore.xml",
        };
        for (String file : files) {
            this.parse(file);
        }
    }

    private void parse(String file) throws Exception {
        Document dom = new Builder().build(ResourceLoader.find(file));
        String input = dom.query("//SRS").get(0).getValue();
        Nodes reporters = dom.query("//reporters/reporter");
        int total = reporters.size();
        String[] reports = new String[total];
        for (int i = 0; i < total; i++) {
            reports[i] = reporters.get(i).getValue();
        }
        String xml = new Dispatcher().dispatch(reports, input);
        Document report = new Builder().build(xml, null);

        Nodes invariants = dom.query("//invariants/invariant");
        for (int i = 0; i < invariants.size(); i++) {
            String xpath = invariants.get(i).getValue();
            assertTrue(
                "XPath failure, nothing found: " + xpath,
                report.query(xpath).size() > 0
            );
        }
    }

}
