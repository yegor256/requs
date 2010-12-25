/**
 * @version $Id$
 */
package com.rqdql.impl.scanner.antlr;

import org.junit.*;
import static org.junit.Assert.*;
import com.rqdql.api.scanner.Scanner;

public class AntlrScannerTest {

    @Test
    public void testImmitatesSimpleScanningOperation() throws Exception {
        Scanner scanner = new AntlrScanner();
        scanner.setInput("File is a \"file\".");
        scanner.run();
    }

    @Test(expected = java.lang.AssertionError.class)
    public void testImmitatesInvalidRequest() throws Exception {
        Scanner scanner = new AntlrScanner();
        scanner.run(); // no input, error here
    }

}
