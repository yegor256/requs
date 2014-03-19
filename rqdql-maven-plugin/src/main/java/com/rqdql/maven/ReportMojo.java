/**
 * Copyright (c) 2009-2013, RQDQL.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the RQDQL.com nor
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
package com.rqdql.maven;

import com.jcabi.log.Logger;
import com.jcabi.xml.XML;
import java.io.File;
import java.io.IOException;
import java.util.Locale;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.CharEncoding;
import org.apache.maven.doxia.sink.Sink;
import org.apache.maven.doxia.sink.SinkFactory;
import org.apache.maven.doxia.siterenderer.Renderer;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.apache.maven.reporting.AbstractMavenReport;
import org.apache.maven.reporting.MavenReportException;

/**
 * Generate site reports.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.1
 * @checkstyle ClassDataAbstractionCoupling (500 lines)
 */
@ToString
@EqualsAndHashCode(callSuper = false)
@Mojo(name = "default")
@SuppressWarnings("PMD.ExcessiveImports")
public final class ReportMojo extends AbstractMavenReport {

    /**
     * The Maven Project.
     */
    @Component
    private transient MavenProject project;

    /**
     * Output directory.
     */
    @Parameter(property = "project.reporting.outputDirectory", required = true)
    private transient File output;

    /**
     * The source directory.
     */
    @Parameter(
        required = true,
        defaultValue = "${basedir}/src/main/rqdql"
    )
    private transient File source;

    /**
     * Doxia Site Renderer component.
     */
    @Component
    private transient Renderer renderer;

    @Override
    public String getOutputName() {
        return "rqdql";
    }

    @Override
    public String getName(final Locale locale) {
        return "RQDQL";
    }

    @Override
    public String getDescription(final Locale locale) {
        return "RQDQL Spec";
    }

    @Override
    protected Renderer getSiteRenderer() {
        return this.renderer;
    }

    @Override
    protected String getOutputDirectory() {
        return this.output.getAbsolutePath();
    }

    @Override
    protected MavenProject getProject() {
        return this.project;
    }

    @Override
    public void executeReport(final Locale locale) throws MavenReportException {
        throw new MavenReportException("not supported");
    }

    @Override
    public void generate(final Sink snk, final SinkFactory factory,
        final Locale locale) throws MavenReportException {
        final XML xml;
        try {
            xml = new Output(this.source).build();
        } catch (final IOException ex) {
            throw new MavenReportException("failed to compile", ex);
        }
        if (new File(this.getOutputDirectory()).mkdirs()) {
            Logger.info(this, "%s created", this.getOutputDirectory());
        }
        try {
            FileUtils.write(
                new File(this.getOutputDirectory(), this.getOutputName()),
                xml.toString(),
                CharEncoding.UTF_8
            );
        } catch (final IOException ex) {
            throw new MavenReportException("failed to save", ex);
        }
    }

}
