/**
 * @version $Id$
 */
package com.rqdql.cli;

import org.junit.*;
import static org.junit.Assert.*;
import nu.xom.*;
import com.rqdql.ResourceLoader;

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

    @Test(expected = com.rqdql.Problem.class)
    public void testDispatchesWithInvalidReporter() throws Exception {
        String[] args = { "non-existing", "metrics" };
        new Dispatcher().dispatch(args, "nothing");
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
    }

}
