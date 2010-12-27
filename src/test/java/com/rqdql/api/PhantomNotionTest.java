/**
 * @version $Id$
 */
package com.rqdql.api;

import org.junit.*;
import static org.junit.Assert.*;

public class PhantomNotionTest {

    @Test
    public void testInstantiatesAndValidatesClass() throws Exception {
        String message = "some text";

        Notion notion = new PhantomNotion(message);
        assertTrue(notion.getMessage().contains(message));

        notion = new PhantomNotion(new Exception(message));
        assertTrue(notion.getMessage().contains(message));
    }

}
