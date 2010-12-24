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
import com.rqdql.api.front.Config;
import com.rqdql.api.front.FrontFactory;
import com.rqdql.api.front.Reporter;
import com.rqdql.api.solm.SOLM;
import com.rqdql.api.solm.SOLMFactory;
import com.rqdql.api.scanner.Scanner;
import com.rqdql.api.scanner.ScannerFactory;
import com.rqdql.api.thesaurus.Thesaurus;
import com.rqdql.api.thesaurus.ThesaurusFactory;

// for XML serialization
import java.io.ByteArrayOutputStream;

// for manipulations with options
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// for XML processing
import nu.xom.Document;
import nu.xom.Element;
import nu.xom.Serializer;

// for processing of words/names of reports
import org.apache.commons.lang.WordUtils;

/**
 * Dispatcher of CLI request.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 * @see Main
 */
public final class Dispatcher {

    /**
     * Name of XML root element.
     * @see #document(Map)
     */
    private static final String ROOT_NAME = "rqdql";

    /**
     * Name of XML element with report.
     * @see #document(Map)
     */
    private static final String REPORT_NAME = "report";

    /**
     * Max line length of the XML produced.
     * @see #toXML(Document)
     */
    private static final int MAX_LENGTH = 80;

    /**
     * XML indentation spaces.
     * @see #toXML(Document)
     */
    private static final int INDENTATION = 4;

    /**
     * Entry point of the entire JAR.
     *
     * @param args List of command-line arguments
     * @param XML produced
     */
    public String dispatch(final String[] args, final String input) {
        Log.trace("#dispatch(%d arguments)", args.length);
        final List<String> reps = new ArrayList<String>();
        for (String arg : args) {
            if (!arg.startsWith("-")) {
                reps.add(arg);
            }
        }
        final Map<String, Reporter> reporters = this.reporters(reps);

        Scanner scanner = new ScannerFactory().getScanner();
        Thesaurus thesaurus = new ThesaurusFactory().getThesaurus();
        SOLM solm = new SOLMFactory().getSOLM();
        scanner.setThesaurus(thesaurus);
        scanner.scan(input);
        thesaurus.convert(solm);

        Document dom = this.document(reporters);
        return this.toXML(dom);
    }

    /**
     * Build and return a list of front reporters.
     * @return Collection of reporters
     */
    private Map<String, Reporter> reporters(final List<String> reps) {
        Map<String, Reporter> reporters = new HashMap<String, Reporter>();
        FrontFactory factory = new FrontFactory();
        for (String rep : reps) {
            // todo: this is stub
            final String name = WordUtils.capitalize(rep);
            Reporter reporter;
            try {
                reporter = factory.find(name);
            } catch (com.rqdql.api.front.ReporterNotFoundException ex) {
                throw com.rqdql.Problem.raise(ex);
            }
            final Config config = new Config();
            // todo: inject data into config
            reporter.configure(config);
            reporter.init();
            reporters.put(name, reporter);
            Log.debug(
                "Reporter '%s' instantiated as %s",
                name,
                reporter.getClass().getCanonicalName()
            );
        }
        return reporters;
    }

    /**
     * Build {@link Document} from a list of {@link Reporter}s.
     * @return reporters The list of them
     * @return XML Document
     */
    private Document document(final Map<String, Reporter> reporters) {
        final Element root = new Element(this.ROOT_NAME);
        final Document dom = new Document(root);
        for (Map.Entry<String, Reporter> pair : reporters.entrySet()) {
            final Element element = new Element(pair.getKey());
            root.appendChild(element);
            final Element node = new Element(this.REPORT_NAME);
            element.appendChild(node);
            pair.getValue().report(node);
        }
        return dom;
    }

    /**
     * Convert DOM {@link Document} to {@link String}.
     * @return dom The Document
     * @return XML in string
     */
    private String toXML(final Document dom) {
        final ByteArrayOutputStream baos = new ByteArrayOutputStream();
        final Serializer serializer = new Serializer(baos);
        serializer.setIndent(this.INDENTATION);
        serializer.setMaxLength(this.MAX_LENGTH);
        try {
            serializer.write(dom);
        } catch (java.io.IOException ex) {
            throw com.rqdql.Problem.raise(ex);
        }
        return baos.toString();
    }


}
