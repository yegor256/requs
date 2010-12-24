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
package com.rqdql.api;

// for logging
import com.rqdql.Log;

// for listing of instruments
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

/**
 * Factory of {@link Instrument}s.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class InstrumentFactory {

    /**
     * Signleton instance.
     */
    private static InstrumentFactory instance = new InstrumentFactory();

    /**
     * List of instruments discovered.
     */
    private Map<String, Instrument> instruments;

    /**
     * Private ctor, to avoid direct instantiation of the class.
     */
    private InstrumentFactory() {
        Log.trace("#InstrumentFactory()");
        this.instruments = new HashMap<String, Instrument>();
        // todo: let's implement it more effectively
        this.instruments.put(
            "scanner/Scanner",
            new com.rqdql.impl.scanner.antlr.AntlrScanner()
        );
        this.instruments.put(
            "thesaurus/Thesaurus",
            new com.rqdql.impl.thesaurus.simple.SimpleThesaurus()
        );
        this.instruments.put(
            "solm/Solm",
            new com.rqdql.impl.solm.simple.SimpleSOLM()
        );
    }

    /**
     * Get an instance of this class.
     * @return The factory to use
     */
    public static InstrumentFactory getInstance() {
        return InstrumentFactory.instance;
    }

    /**
     * Get a full list of instruments.
     * @return Ordered list of instruments
     */
    public Collection<Instrument> getInstruments() {
        Log.trace("#getInstruments()");
        return this.instruments.values();
    }

    /**
     * Find one instrument.
     * @param name Name of the instrument to find
     * @return The instrument found
     */
    public Instrument find(final String name) {
        Log.trace("#find('%s')", name);
        return this.instruments.get(name);
    }

}
