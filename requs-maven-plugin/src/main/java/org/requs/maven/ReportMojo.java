/**
 * Copyright (c) 2009-2017, requs.org
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
package org.requs.maven;

import com.jcabi.log.Logger;
import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import javax.validation.constraints.NotNull;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import org.apache.maven.doxia.sink.Sink;
import org.apache.maven.doxia.sink.SinkFactory;
import org.apache.maven.doxia.siterenderer.Renderer;
import org.apache.maven.plugins.annotations.Component;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.apache.maven.reporting.AbstractMavenReport;
import org.apache.maven.reporting.MavenReportException;
import org.requs.Compiler;
import org.slf4j.impl.StaticLoggerBinder;

/**
 * Generate site reports.
 *
 * @author Yegor Bugayenko (yegor@tpc2.com)
 * @version $Id$
 * @since 1.1
 * @checkstyle ClassDataAbstractionCoupling (500 lines)
 * @checkstyle VisibilityModifierCheck (500 lines)
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
    @NotNull
    public transient MavenProject project;

    /**
     * Output directory.
     */
    @Parameter(property = "project.reporting.outputDirectory", required = true)
    @NotNull
    public transient File output;

    /**
     * The source directory.
     */
    @Parameter(
        required = true,
        defaultValue = "${basedir}/src/main/requs"
    )
    @NotNull
    public transient File source;

    /**
     * Optional properties/options.
     * @since 1.14
     */
    @Parameter(required = false)
    @NotNull
    @SuppressWarnings("PMD.UseConcurrentHashMap")
    public transient Map<String, String> options =
        new ConcurrentHashMap<String, String>(0);

    /**
     * Doxia Site Renderer component.
     */
    @Component
    @NotNull
    public transient Renderer renderer;

    @Override
    public String getOutputName() {
        return "requs";
    }

    @Override
    public String getName(final Locale locale) {
        return "Requs";
    }

    @Override
    public String getDescription(final Locale locale) {
        return "Requs Specification";
    }

    @Override
    public Renderer getSiteRenderer() {
        return this.renderer;
    }

    @Override
    public String getOutputDirectory() {
        return this.output.getAbsolutePath();
    }

    @Override
    public MavenProject getProject() {
        return this.project;
    }

    @Override
    public void executeReport(final Locale locale) throws MavenReportException {
        throw new MavenReportException("not supported");
    }

    @Override
    public void generate(final Sink sink, final SinkFactory factory,
        final Locale locale) {
        if (!this.source.exists()) {
            Logger.info(this, "source directory %s is absent", this.source);
            return;
        }
        StaticLoggerBinder.getSingleton().setMavenLog(this.getLog());
        final File home = new File(
            this.getOutputDirectory(),
            this.getOutputName()
        );
        if (home.mkdirs()) {
            Logger.info(this, "site directory %s created", home);
        }
        try {
            new Compiler(this.source, home, this.options).compile();
        } catch (final IOException ex) {
            throw new IllegalStateException(ex);
        }
        this.front(sink);
    }

    /**
     * Make a front page.
     * @param sink Sink to use
     */
    private void front(final Sink sink) {
        sink.section1();
        sink.sectionTitle1();
        sink.text("Requs SRS");
        sink.sectionTitle1_();
        sink.paragraph();
        sink.text("This page contains ");
        sink.link(String.format("%s/requs.xml", this.getOutputName()));
        sink.text("Software Requirements Specification (SRS)");
        sink.link_();
        sink.text(" generated by requs compiler.");
        sink.paragraph();
        sink.text("More information you can get at ");
        sink.link("http://www.requs.org");
        sink.text("www.requs.org");
        sink.link_();
        sink.text(".");
        sink.paragraph_();
        sink.section1_();
    }

}
