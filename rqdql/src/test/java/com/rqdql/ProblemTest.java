/**
 * @version $Id$
 */
package com.rqdql;

import org.junit.*;
import static org.junit.Assert.*;

public class ProblemTest {

    @Test
    public void testValidatesExceptionClass() {
        String reason = "some reason";
        Throwable ex = Problem.raise(reason);
        assertTrue(ex instanceof Problem);
        assertTrue(ex.getMessage().contains(reason));
    }

    @Test
    public void testValidatesExceptionClassViaThrowableCause() {
        String reason = "some reason";
        Throwable ex = Problem.raise(new RuntimeException(reason));
        assertTrue(ex instanceof Problem);
        assertTrue(ex.getMessage().contains(reason));
    }

    @Test
    public void testValidatesExceptionClassViaThrowableCauseAndString() {
        String reason = "some reason";
        Throwable ex = Problem.raise(reason, new RuntimeException());
        assertTrue(ex instanceof Problem);
        assertTrue(ex.getMessage().contains(reason));
    }

}
