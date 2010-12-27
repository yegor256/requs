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
package com.rqdql.cli;

// for internal logging
import com.rqdql.Log;

// for processing of incoming document
import com.rqdql.api.Instrument;
import com.rqdql.api.InstrumentFactory;
import com.rqdql.api.scanner.Scanner;

// for front reporting
import com.rqdql.xml.Assembler;

// for manipulations with options
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Dispatcher of CLI request.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 * @see Main
 */
public final class Dispatcher {

    /**
     * Miliseconds in one second.
     */
    private static final long MSEC = 1000;

    /**
     * Entry point of the entire JAR.
     *
     * @param args List of command-line arguments
     * @param input Incoming RQDQL stream
     * @return XML produced
     * @see Main#main(String[])
     */
    public String dispatch(final String[] args, final String input) {
        final long startTime = System.currentTimeMillis();
        Log.trace("#dispatch(%d arguments)", args.length);
        final List<String> reps = new ArrayList<String>();
        for (String arg : args) {
            if (arg.charAt(0) != '-') {
                reps.add(arg);
            }
        }

        final Assembler asm = new Assembler();
        try {
            asm.init(reps);
        } catch (com.rqdql.xml.ReporterNotFoundException ex) {
            throw com.rqdql.Problem.raise(ex);
        }
        this.parse(input);
        final String xml = asm.assemble();

        Log.info(
            "Dispatched %d bytes in %.2fsec",
            input.length(),
            (float) (System.currentTimeMillis() - startTime) / this.MSEC
        );
        return xml;
    }

    /**
     * Parse string via instruments available.
     * @param input Incoming RQDQL stream
     * @see #dispatch(String[], String)
     */
    private void parse(final String input) {
        final Scanner scanner = (Scanner) InstrumentFactory.getInstance()
            .find("scanner/Scanner");
        scanner.setInput(input);
        final Collection<Instrument> instruments =
            InstrumentFactory.getInstance().getInstruments();
        for (Instrument inst : instruments) {
            inst.run();
        }
    }

}
