/**
 * @version $Id: MainTest.java 2363 2010-12-24 13:28:55Z yegor256@yahoo.com $
 */
package com.rqdql.api;

import org.junit.*;
import static org.junit.Assert.*;

public class AuditorTest {

    @Test
    public void testValidatesSingletonPattern() throws Exception {
        Auditor a1 = Auditor.getInstance();
        Auditor a2 = Auditor.getInstance();
        assertTrue(a1 == a2);
    }

}
