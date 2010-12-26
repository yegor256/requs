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
package com.rqdql.front;

/**
 * Factory of {@link Reporter}s.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class FrontFactory {

    /**
     * Package, where all reporters are implemented.
     */
    private Package pack;

    /**
     * Public ctor with default value.
     * @todo #1! I don't know why the first line doesn't work,
     *           instead it returns NULL. Let's investigate further
     *           and fix the problem.
     */
    public FrontFactory() {
        // this(Package.getPackage("com.rqdql.impl.front"));
        this(com.rqdql.front.reporters.Errors.class.getPackage());
    }

    /**
     * Public ctor with pre-defined package.
     * @param pckg The package, where reporters are implemented
     */
    public FrontFactory(final Package pckg) {
        this.pack = pckg;
    }

    /**
     * Find and return a reporter.
     * @param name The name of reporter
     * @return The {@link Reporter} just found
     * @throws ReporterNotFoundException If the reporter is not found
     */
    public Reporter find(final String name)
        throws ReporterNotFoundException {
        final String clsName = this.pack.getName() + "." + name;
        try {
            return (Reporter) Class.forName(clsName).newInstance();
        } catch (java.lang.IllegalAccessException ex) {
            throw new ReporterNotFoundException(name, ex);
        } catch (java.lang.ClassNotFoundException ex) {
            throw new ReporterNotFoundException(name, ex);
        } catch (java.lang.InstantiationException ex) {
            throw new ReporterNotFoundException(name, ex);
        }
    }

}
