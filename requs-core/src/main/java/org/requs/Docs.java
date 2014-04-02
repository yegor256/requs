/**
 * Copyright (c) 2009-2014, requs.org
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package org.requs;

import java.io.File;
import java.io.IOException;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.CharEncoding;

/**
 * Docs.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.2
 */
public interface Docs {

    /**
     * Get one doc.
     * @param name Name of the document
     * @return Doc
     * @throws IOException If fails
     */
    Doc get(String name) throws IOException;

    /**
     * In directory.
     */
    final class InDir implements Docs {
        /**
         * Directory to keep files in.
         */
        private final transient File dir;
        /**
         * Ctor.
         * @param path Directory path
         */
        public InDir(final File path) {
            this.dir = path;
        }
        @Override
        public Doc get(final String name) throws IOException {
            final File file = new File(this.dir, name);
            FileUtils.touch(file);
            // @checkstyle AnonInnerLengthCheck (50 lines)
            return new Doc() {
                @Override
                public void name(final String label, final String desc)
                    throws IOException {
                    final Doc csv = Docs.InDir.this.get("facets.csv");
                    csv.write(
                        String.format(
                            "%s\n%s,%s,%s",
                            csv.read(), name, label, desc
                        )
                    );
                }
                @Override
                public String read() throws IOException {
                    return FileUtils.readFileToString(file, CharEncoding.UTF_8);
                }
                @Override
                public void write(final String content) throws IOException {
                    FileUtils.write(file, content, CharEncoding.UTF_8);
                }
            };
        }
    }

}
