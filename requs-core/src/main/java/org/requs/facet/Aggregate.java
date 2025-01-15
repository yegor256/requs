/*
 * Copyright (c) 2009-2025, Yegor Bugayenko
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
package org.requs.facet;

import com.google.common.collect.Lists;
import com.jcabi.aspects.Immutable;
import com.jcabi.aspects.Tv;
import com.jcabi.log.Logger;
import com.jcabi.xml.XML;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Collections;
import java.util.List;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.StringUtils;
import org.requs.XeFacet;
import org.xembly.Directive;
import org.xembly.Directives;

/**
 * Aggregate sources into one file.
 *
 * @since 1.2
 */
@Immutable
@ToString(of = { })
@EqualsAndHashCode(of = "dir")
public final class Aggregate implements XeFacet {

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
    public Iterable<Directive> touch(final XML spec) throws IOException {
        final StringBuilder text = new StringBuilder(Tv.THOUSAND);
        final List<File> files = Lists.newArrayList(
            FileUtils.listFiles(
                new File(this.dir), new String[]{"req"}, true
            )
        );
        Collections.sort(files);
        int idx = 0;
        final Directives dirs = new Directives().xpath("/spec").addIf("files");
        for (final File file : files) {
            int pos = StringUtils.countMatches(text.toString(), "\n");
            pos += 1;
            Logger.info(this, "source file: %s", file);
            text.append(
                FileUtils.readFileToString(file, StandardCharsets.UTF_8)
            ).append('\n');
            dirs.add("file")
                .attr("id", Integer.toString(idx))
                .attr("line", Integer.toString(pos))
                .set(file.getAbsolutePath()).up();
            ++idx;
        }
        return dirs.up().add("input").set(text.toString());
    }
}
