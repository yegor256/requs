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
package com.rqdql.api.front;

// for internal logging
import com.rqdql.Log;

// for XML serialization
import java.io.ByteArrayOutputStream;

// for manipulations with options
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
 * Assembler of {@link Reporter}s.
 *
 * @author Yegor Bugayenko (yegor@rqdql.com)
 * @version $Id$
 */
public final class Assembler {

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
     * List of reporters, with their names.
     */
    private Map<String, Reporter> reporters;

    /**
     * Build a list of front reporters.
     * @param reps List of reporters to create (together with their args)
     * @see com.rqdql.cli.Dispatcher#dispatch(String[], String)
     * @throws ReporterNotFoundException If one of reporters are not found
     */
    public void init(final List<String> reps)
        throws ReporterNotFoundException {
        this.reporters = new HashMap<String, Reporter>();
        final FrontFactory factory = new FrontFactory();
        for (String rep : reps) {
            // todo: this is stub
            final String name = WordUtils.capitalize(rep);
            Reporter reporter;
            reporter = factory.find(name);
            final Config config = new Config();
            // todo: inject data into config
            reporter.configure(config);
            reporter.init();
            this.reporters.put(name, reporter);
            Log.debug(
                "Reporter '%s' instantiated as %s",
                name,
                reporter.getClass().getCanonicalName()
            );
        }
    }

    /**
     * Build XML from all {@link Reporter}s.
     * @return XML Document
     * @see com.rqdql.cli.Dispatcher#dispatch(String[], String)
     */
    public String assemble() {
        return this.toXML(this.document());
    }

    /**
     * Build {@link Document} from a list of {@link Reporter}s.
     * @return XML Document
     * @see #assemble()
     */
    private Document document() {
        final Element root = new Element(this.ROOT_NAME);
        final Document dom = new Document(root);
        for (Map.Entry<String, Reporter> pair : this.reporters.entrySet()) {
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
     * @param dom The Document
     * @return XML in string
     * @see #assemble()
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
