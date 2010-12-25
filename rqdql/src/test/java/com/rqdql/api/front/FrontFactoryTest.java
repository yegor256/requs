/**
 * @version $Id$
 */
package com.rqdql.api.front;

import org.junit.*;
import static org.junit.Assert.*;
import java.io.File;
import org.apache.commons.io.FileUtils;

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

    @Test
    public void testImmitatesBrokenJavaClassFile() throws Exception {
        FrontFactory factory = new FrontFactory();
        File f = new File("target/classes/com/rqdql/impl/front/Errors.class");
        assert f.exists();
        byte[] content = FileUtils.readFileToByteArray(f);
        FileUtils.writeStringToFile(f, "invalid content");
        try {
            factory.find("Errors");
            fail("Exception expected, but not thrown");
        } catch (java.lang.ClassFormatError ex) {
            // it's OK
        }
        FileUtils.writeByteArrayToFile(f, content);
    }

}
