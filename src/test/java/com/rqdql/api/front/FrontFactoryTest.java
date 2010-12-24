/**
 * @version $Id$
 */
package com.rqdql.api.front;

import org.junit.*;
import static org.junit.Assert.*;

public class FrontFactoryTest {

    @Test
    public void testFindsSingleReporter() throws Exception {
        FrontFactory factory = new FrontFactory();
        Reporter rep = factory.find("Metrics");
        assertTrue(rep instanceof com.rqdql.impl.front.Metrics);
    }

    @Test(expected = ReporterNotFoundException.class)
    public void testMakesAnAttemplToFindNonExistingReporter() throws Exception {
        FrontFactory factory = new FrontFactory();
        Reporter rep = factory.find("there is no such reporter");
    }

}
