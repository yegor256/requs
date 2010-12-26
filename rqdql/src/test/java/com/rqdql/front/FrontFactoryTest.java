/**
 * @version $Id$
 */
package com.rqdql.front;

import org.junit.*;
import static org.junit.Assert.*;
import java.io.File;
import org.apache.commons.io.FileUtils;

public class FrontFactoryTest {

    @Test
    public void testFindsSingleReporter() throws Exception {
        FrontFactory factory = new FrontFactory();
        Reporter rep = factory.find("Metrics");
        assertTrue(rep instanceof com.rqdql.front.reporters.Metrics);
    }

    @Test(expected = ReporterNotFoundException.class)
    public void testMakesAnAttemplToFindNonExistingReporter() throws Exception {
        FrontFactory factory = new FrontFactory();
        factory.find("there is no such reporter");
    }

    public abstract static class AbstractReporter {
    }

    @Test(expected = ReporterNotFoundException.class)
    public void testTriesToInstantiateAbstractReporter() throws Exception {
        Package p = this.getClass().getPackage();
        assert p != null;
        FrontFactory factory = new FrontFactory(p);
        factory.find("FrontFactoryTest$AbstractReporter");
    }

    private static class PrivateReporter {
    }

    @Test(expected = ReporterNotFoundException.class)
    public void testTriesToInstantiatePrivateReporter() throws Exception {
        Package p = this.getClass().getPackage();
        assert p != null;
        FrontFactory factory = new FrontFactory(p);
        factory.find("FrontFactoryTest$PrivateReporter");
    }

}
