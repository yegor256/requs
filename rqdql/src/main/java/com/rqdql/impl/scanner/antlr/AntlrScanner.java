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
package com.rqdql.impl.scanner.antlr;

// parent interfaces, classes
import com.rqdql.Log;
import com.rqdql.api.scanner.Scanner;
import com.rqdql.api.thesaurus.Thesaurus;

/**
 * {@link Scanner} that uses Antlr3 for scanning of RQDQL text.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id: Log.java 2358 2010-12-23 15:40:20Z yegor256@yahoo.com $
 */
public final class AntlrScanner implements Scanner {

    /**
     * The {@link Thesaurus} to work with.
     */
    private Thesaurus thesaurus;

    /**
     * {@inheritDoc}
     */
    @Override
    public void setThesaurus(final Thesaurus thrs) {
        Log.trace(
            "setThesaurus(%s)",
            thrs.getClass().getCanonicalName()
        );
        this.thesaurus = thrs;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void scan(final String text) {
        Log.trace(
            "scan(%s.../%d bytes)",
            text.substring(0, 20),
            text.length()
        );
    }

}
