/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
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
