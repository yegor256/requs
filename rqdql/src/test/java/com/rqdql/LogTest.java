/**
 * @version $Id$
 */
package com.rqdql;

import org.junit.*;
import static org.junit.Assert.*;
import org.apache.log4j.*;
import org.apache.log4j.spi.LoggingEvent;

public class LogTest {

    private static class MockAppender extends AppenderSkeleton {
        public LoggingEvent event;
        @Override
        public void append(LoggingEvent evt) {
            this.event = evt;
        }
        @Override
        public boolean requiresLayout() {
            return false;
        }
        @Override
        public void close() {
        }
        @Override
        public Level getThreshold() {
            return Level.ALL;
        }
    }

    private MockAppender appender;

    private Level savedLevel;

    @Before
    public void attachAppender() {
        this.appender = new MockAppender();
        Logger.getRootLogger().addAppender(this.appender);
        this.savedLevel = Logger.getLogger("com.rqdql").getLevel();
        Logger.getLogger("com.rqdql").setLevel(Level.TRACE);
    }

    @After
    public void dettachAppender() {
        Logger.getRootLogger().removeAppender(this.appender);
        this.appender = null;
        Logger.getLogger("com.rqdql").setLevel(this.savedLevel);
    }

    @Test
    public void testValidatesCorrectDetectionOfLogger() throws Exception {
        Log.debug("test message, ignore it");
        assertEquals("com.rqdql.LogTest", this.appender.event.getLoggerName());
    }

    @Test
    public void testValidatesCorrectPassingOfMessageToLogger() throws Exception {
        String msg = "ignore this message";
        Log.debug(msg);
        assertTrue(((String) this.appender.event.getMessage()).contains(msg));
    }

    @Test
    public void testValidatesCorrectLoggingLevel() throws Exception {
        String msg = "ignore this message";
        Log.debug(msg);
        assertEquals(Level.DEBUG, this.appender.event.getLevel());
        Log.info(msg);
        assertEquals(Level.INFO, this.appender.event.getLevel());
        Log.warn(msg);
        assertEquals(Level.WARN, this.appender.event.getLevel());
        Log.error(msg);
        assertEquals(Level.ERROR, this.appender.event.getLevel());
        Log.trace(msg);
        assertEquals(Level.TRACE, this.appender.event.getLevel());
    }

    @Test
    public void testExperimentsWithVarArgs() throws Exception {
        Log.debug("Log testing: we found %d files", 5);
        assertTrue(((String) this.appender.event.getMessage()).contains("5 files"));
        Log.debug(
            "Log testing: my name is '%s', I'm %d years old",
            "John Doe",
            55
        );
        assertTrue(((String) this.appender.event.getMessage()).contains("55 years old"));
    }

    private static class InnerClass {
        public void log() {
            this.innerLog();
        }
        private void innerLog() {
            Log.info("Inner log message");
        }
    }

    @Test
    public void testSendsLogMessageFromNestedClass() throws Exception {
        new InnerClass().log();
        assertEquals("com.rqdql.LogTest$InnerClass", this.appender.event.getLoggerName());
    }

    @Test
    public void testSendsLogMessageFromNonRqdqlClass() throws Exception {
        org.acme.Bookstore.ping("sample message, ignore it");
        assertEquals("com.rqdql.LogTest", this.appender.event.getLoggerName());
    }

}
