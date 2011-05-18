/**
 * @version $Id$
 */
package com.rqdql.cli.reporters;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;
import com.rqdql.cli.*;
import com.rqdql.api.InstrumentFactory;
import com.rqdql.api.scanner.Scanner;
import nu.xom.*;

public class ErrorsTest {

    /**
     * @todo #2:3hrs The test has to be implemented
     */
    @Ignore("#2:3hrs")
    @Test
    public void testProcessesTextWithErrorsAndSpotsThemInXMLReport() throws Exception {
        Reporter rep = new Errors();
        rep.init();

        Scanner scanner = (Scanner) InstrumentFactory.getInstance().find("scanner/Scanner");
        scanner.setInput("This text is not RQDQL-valid.");

        // we expect grammar errors to be caught by Errors Reporter
        scanner.run();

        Element xml = new Element("report");
        Document dom = new Document(xml);
        rep.report(xml);
        assertTrue(
            "No errors found in the document? How come?",
            dom.query("/report/errors/error[@line]").size() > 0
        );
    }

}
