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
package org.requs.facet.decor;

import com.jcabi.aspects.Immutable;
import com.jcabi.log.Logger;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.CharEncoding;
import org.requs.Docs;
import org.requs.Facet;

/**
 * Aggregate sources into one file.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.2
 */
@Immutable
@ToString(of = { })
@EqualsAndHashCode(of = "dir")
public final class Aggregate implements Facet {

    /**
     * Directory with sources.
     */
    private final transient String dir;

    /**
     * Ctor.
     * @param path Path to the directory with sources
     */
    public Aggregate(final File path) {
        this.dir = path.getAbsolutePath();
    }

    @Override
    public void touch(final Docs docs) throws IOException {
        final StringBuilder text = new StringBuilder(0);
        final Collection<File> files = FileUtils.listFiles(
            new File(this.dir), new String[]{"req"}, true
        );
        for (final File file : files) {
            Logger.info(this, "source file: %s", file);
            text.append(
                FileUtils.readFileToString(file, CharEncoding.UTF_8)
            ).append('\n');
        }
        docs.get("input.req").write(text.toString());
    }
}
