/**
 * @version $Id$
 */
package com.rqdql.cli;

import org.junit.*;
import static org.junit.Assert.*;

public class MainTest {

    @Test
    public void testExecutesSimpleCli() {
        String[] args = { "version" };
        Main.main(args);
    }

    @Test(expected = java.lang.IllegalAccessException.class)
    public void testMakesAnIncorrectAttemptToInstantiateClass() throws Exception {
        String name = "com.rqdql.cli.Main";
        Class cls = Class.forName(name);
        cls.newInstance(); // exception here
    }

}
