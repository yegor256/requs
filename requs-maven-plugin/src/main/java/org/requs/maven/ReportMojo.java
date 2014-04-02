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
package org.requs.maven;

import com.jcabi.log.Logger;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.Collections;
import java.util.Locale;
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
    private transient MavenProject project;

    /**
     * Output directory.
     */
    @Parameter(property = "project.reporting.outputDirectory", required = true)
    @NotNull
    private transient File output;

    /**
     * The source directory.
     */
    @Parameter(
        required = true,
        defaultValue = "${basedir}/src/main/requs"
    )
    @NotNull
    private transient File source;

    /**
     * Doxia Site Renderer component.
     */
    @Component
    @NotNull
    private transient Renderer renderer;

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
        return "Requs Facet";
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

    // @checkstyle ExecutableStatementCountCheck (100 lines)
    @Override
    public void generate(final Sink snk, final SinkFactory factory,
        final Locale locale) throws MavenReportException {
        StaticLoggerBinder.getSingleton().setMavenLog(this.getLog());
        final File home = new File(
            this.getOutputDirectory(),
            this.getOutputName()
        );
        if (home.mkdirs()) {
            Logger.info(this, "site directory %s created", home);
        }
        snk.section1();
        snk.sectionTitle1();
        snk.text("Requs Reports");
        snk.sectionTitle1_();
        snk.table();
        snk.tableRow();
        snk.tableHeaderCell();
        snk.text("Report");
        snk.tableHeaderCell_();
        snk.tableRow_();
        for (final String report : this.reports(home)) {
            snk.tableRow();
            snk.tableCell();
            snk.link(
                String.format(
                    "%s/%s.xml",
                    this.getOutputName(),
                    report
                )
            );
            snk.text(report);
            snk.link_();
            snk.tableCell_();
            snk.tableRow_();
        }
        snk.table_();
        snk.paragraph();
        snk.text("More information you can get at ");
        snk.link("http://www.requs.org");
        snk.text("www.requs.org");
        snk.link_();
        snk.text(".");
        snk.paragraph_();
        snk.section1_();
    }

    /**
     * All reports.
     * @param dir Where to save them
     * @return Names of reports
     * @throws MavenReportException If fails
     */
    private Collection<String> reports(final File dir)
        throws MavenReportException {
        try {
            new Compiler(this.source, dir).compile();
        } catch (final IOException ex) {
            throw new MavenReportException("failed to compile", ex);
        }
        return Collections.singleton("srs");
    }

}
