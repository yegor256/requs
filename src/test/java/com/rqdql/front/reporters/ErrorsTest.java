/**
 * @version $Id$
 */
package com.rqdql.front.reporters;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;
import com.rqdql.front.*;
import com.rqdql.api.InstrumentFactory;
import com.rqdql.api.scanner.Scanner;
import nu.xom.Element;

/**
 *
 */
public class ErrorsTest {

    @Test
    public void testProcessesTextWithErrorsAndSpotsThemInXMLReport() throws Exception {
        Reporter rep = new Errors();
        rep.init();

        Scanner scanner = (Scanner) InstrumentFactory.getInstance().find("scanner/Scanner");
        scanner.setInput("This text is not RQDQL-valid.");

        // we expect grammar errors to be caught by Errors Reporter
        scanner.run();

        Element xml = new Element("test-report");
        rep.report(xml);

        // xml.query();
    }

}
