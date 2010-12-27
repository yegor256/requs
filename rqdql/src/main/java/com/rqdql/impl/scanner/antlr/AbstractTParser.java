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

// for ANTLR3 parsing
import org.antlr.runtime.Parser;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.RecognizerSharedState;
import org.antlr.runtime.TokenStream;

public abstract class AbstractTParser extends Parser {

    /**
     * Create a new parser instance, pre-supplying the
     * input token stream.
     *
     * @param input The stream of tokens that will be pulled from the lexer
     */
    protected AbstractTParser(final TokenStream input) {
        super(input);
    }

    /**
     * Create a new parser instance, pre-supplying the input
     * token stream and the shared state. This is only used when
     * a grammar is imported into another grammar, but
     * we must supply this constructor to satisfy the super class contract.
     *
     * @param input The stream of tokesn that will be pulled from the lexer
     * @param state The shared state object created by an interconnectd grammar
     */
    protected AbstractTParser(final TokenStream input,
        final RecognizerSharedState state) {
        super(input, state);
    }

    /**
     * Creates the error/warning message that we need to show users/IDEs when
     * ANTLR has found a parsing error, has recovered from it and is now
     * telling us that a parsing exception occurred.
     *
     * @param tokenNames token names as known by ANTLR (which we ignore)
     * @param exp The exception that was thrown
     */
    @Override
    public final void displayRecognitionError(final String[] tokenNames,
        final RecognitionException exp) {
        // This is just a place holder that shows how to override this method
        super.displayRecognitionError(tokenNames, exp);
    }

}
