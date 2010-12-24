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

}
