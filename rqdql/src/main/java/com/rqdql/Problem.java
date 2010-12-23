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

/**
 * Global creator of {@link RuntimeException} instances.
 *
 * Use it like this in any class, and in any package:
 *
 * <pre>
 * {@code
 * package com.rqdql.XXX;
 * import com.rqdql.Problem.raise;
 * public class MyClass {
 *   public void foo() {
 *     if (something is wrong) {
 *       throw Problem.raise("some problem");
 *     }
 *   }
 * }
 * [...]
 * }
 * </pre>
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class Problem extends RuntimeException {

    /**
     * Private ctor. It is private in order to avoid
     * a possibility to instantiate the class directly,
     * outside of factory method {@link #raise()}.
     * @param message The exception message
     * @see #raised(String)
     */
    private Problem(final String message) {
        super(message);
    }

    /**
     * Private ctor. It is private in order to avoid
     * a possibility to instantiate the class directly,
     * outside of factory method {@link #raise()}.
     * @param cause Previous problem
     * @see #raised(Throwable)
     */
    private Problem(final Throwable cause) {
        super(cause);
    }

    /**
     * Private ctor. It is private in order to avoid
     * a possibility to instantiate the class directly,
     * outside of factory method {@link #raise()}.
     * @param message The exception message
     * @param cause Previous problem
     * @see #raised(String,Throwable)
     */
    private Problem(final String message, final Throwable cause) {
        super(message, cause);
    }

    /**
     * Create a custom exception class, using the params provided.
     *
     * @param message The exception message
     * @return The problem created
     */
    public static Problem raise(final String message) {
        return new Problem(message);
    }

    /**
     * Create a custom exception class, using the params provided.
     *
     * @param cause Previous problem
     * @return The problem created
     */
    public static Problem raise(final Throwable cause) {
        return new Problem(cause);
    }

    /**
     * Create a custom exception class, using the params provided.
     *
     * @param message The exception message
     * @param cause Previous problem
     * @return The problem created
     */
    public static Problem raise(
        final String message, final Throwable cause) {
        return new Problem(message, cause);
    }

}
