/**
 * @version $Id$
 */
package com.rqdql.xml;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;

public class AssemblerTest {

    @Test
    public void testAssemblesXMLWithEmptyReporters() throws Exception {
        Assembler asm = new Assembler();
        List<String> list = new ArrayList<String>();
        list.add("metrics");
        list.add("errors");
        asm.init(list);
        String xml = asm.assemble();
        assertTrue(xml.length() > 0);
    }

    @Test(expected = ReporterNotFoundException.class)
    public void testAssemblesWithNonExistingReporter() throws Exception {
        Assembler asm = new Assembler();
        List<String> list = new ArrayList<String>();
        list.add("this one is absent");
        asm.init(list);
    }

}
