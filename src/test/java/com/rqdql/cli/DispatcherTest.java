/**
 * @version $Id$
 */
package com.rqdql.cli;

import org.junit.*;
import static org.junit.Assert.*;

public class DispatcherTest {

    @Test
    public void testRunsSimpleReportSet() throws Exception {
        String[] args = { "errors", "metrics" };
        String input = "ActorUser is a \"human being\".";
        String xml = new Dispatcher().dispatch(args, input);
    }

}
