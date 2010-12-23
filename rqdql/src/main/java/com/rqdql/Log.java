/**
 * RQDQL.com
 *
 * This source file is subject to the new BSD license that is bundled
 * with this package in the file LICENSE.txt. It is also available
 * through the world-wide-web at this URL: http://www.rqdql.com/LICENSE.txt
 * If you did not receive a copy of the license and are unable to
 * obtain it through the world-wide-web, please send an email
 * to license@rqdql.com so we can send you a copy immediately.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
package com.rqdql;

// for internal logging
import org.apache.log4j.Logger;

/**
 * Globall logger, very convenient to use.
 *
 * <p>Use it like this in any class, and in any package:
 *
 * <pre>
 * {@code
 * package com.rqdql.XXX;
 * import com.rqdql.Log;
 * public class MyClass {
 *   public void foo() {
 *     Log.debug("The method foo() was just called");
 *   }
 * }
 * [...]
 * }
 * </pre>
 *
 * <p>There is some discussion at
 * <a href="http://stackoverflow.com/questions/4106324">StackOverflow</a>
 * about this idea.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class Log {

    /**
     * Private ctor, to avoid a possibility to instantiate this
     * class directly.
     */
    private Log() {
        // intentionally empty
    }

    /**
     * Protocol one information message, through
     * a global {@link Logger}. This is just
     * a static wrapper of a non-static method of a {@link Logger}
     * class.
     *
     * @param msg The message to protocol
     * @param args Vararg list of params
     */
    public static void info(
        final String msg,
        final Object... args) {
        Log.logger().info(Log.compose(msg, args));
    }

    /**
     * Protocol one information message, through
     * a global {@link Logger}. This is just
     * a static wrapper of a non-static method of a {@link Logger}
     * class.
     *
     * @param msg The message to protocol
     * @param args Vararg list of params
     */
    public static void debug(
        final String msg,
        final Object... args) {
        Log.logger().debug(Log.compose(msg, args));
    }

    /**
     * Protocol one information message, through
     * a global {@link Logger}. This is just
     * a static wrapper of a non-static method of a {@link Logger}
     * class.
     *
     * @param msg The message to protocol
     * @param args Vararg list of params
     */
    public static void warn(
        final String msg,
        final Object... args) {
        Log.logger().warn(Log.compose(msg, args));
    }

    /**
     * Protocol one information message, through
     * a global {@link Logger}. This is just
     * a static wrapper of a non-static method of a {@link Logger}
     * class.
     *
     * @param msg The message to protocol
     * @param args Vararg list of params
     */
    public static void error(
        final String msg,
        final Object... args) {
        Log.logger().error(Log.compose(msg, args));
    }

    /**
     * Protocol one information message, through
     * a global {@link Logger}. This is just
     * a static wrapper of a non-static method of a {@link Logger}
     * class.
     *
     * @param msg The message to protocol
     * @param args Vararg list of params
     */
    public static void trace(
        final String msg,
        final Object... args) {
        Log.logger().trace(Log.compose(msg, args));
    }

    /**
     * Private supplementary class.
     * @see #logger()
     */
    private static class FakeException extends Throwable {
    }

    /**
     * Get the instance of the logger for this particular caller.
     *
     * <p>Here we retrieve the name of calling class from stack trace,
     * using the third position in it.
     *
     * @return The instance of {@link Logger} class
     */
    private static Logger logger() {
        final Throwable thr = new Log.FakeException();
        final StackTraceElement[] elements = thr.getStackTrace();
        String name = Log.class.getCanonicalName();
        for (int idx = 2; idx < elements.length; idx += 1) {
            name = elements[idx].getClassName();
            if (name.startsWith("com.rqdql.")) {
                break;
            }
        }
        return Logger.getLogger(name);
    }

    /**
     * Compose a message using varargs.
     *
     * @param msg The message
     * @param args List of args
     * @return The message composed
     */
    private static String compose(final String msg, final Object[] args) {
        return String.format(msg, args);
    }

}
