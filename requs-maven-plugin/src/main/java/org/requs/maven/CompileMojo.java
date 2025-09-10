/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */
package org.requs.maven;

import com.jcabi.log.Logger;
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;
import org.requs.Compiler;
import org.slf4j.impl.StaticLoggerBinder;

/**
 * Compile requs sources into XML.
 *
 * @since 1.1
 * @checkstyle VisibilityModifierCheck (500 lines)
 */
@Mojo(
    name = "compile", threadSafe = true,
    defaultPhase = LifecyclePhase.COMPILE
)
public final class CompileMojo extends AbstractMojo {

    /**
     * The source directory.
     */
    @Parameter(
        required = true,
        defaultValue = "${basedir}/src/main/requs"
    )
    public transient File input;

    /**
     * Output directory.
     */
    @Parameter(
        required = true,
        defaultValue = "${project.build.directory}/requs"
    )
    public transient File output;

    /**
     * Optional properties/options.
     * @since 1.14
     */
    @SuppressWarnings("PMD.UseConcurrentHashMap")
    @Parameter
    public transient Map<String, String> options =
        new ConcurrentHashMap<>(0);

    @Override
    public void execute() throws MojoFailureException {
        StaticLoggerBinder.getSingleton().setMavenLog(this.getLog());
        if (!this.input.exists()) {
            Logger.info(this, "input directory %s is absent", this.input);
            return;
        }
        try {
            new Compiler(this.input, this.output, this.options).compile();
            final XML srs = new XMLDocument(new File(this.output, "requs.xml"));
            final Collection<XML> errors = srs.nodes("//errors/error");
            final int prefix = this.input.getAbsolutePath().length() + 1;
            if (!errors.isEmpty()) {
                for (final XML error : errors) {
                    Logger.error(
                        this, "%s[%s:%s] %s",
                        srs.xpath(
                            String.format(
                                "/spec/files/file[@id='%d']/text()",
                                Integer.parseInt(error.xpath("@file").get(0))
                            )
                        ).get(0).substring(prefix),
                        error.xpath("@line").get(0),
                        error.xpath("@pos").get(0),
                        error.xpath("text()").get(0)
                    );
                }
                throw new MojoFailureException(
                    String.format(
                        "%d requs error(s), see log above",
                        errors.size()
                    )
                );
            }
        } catch (final IOException ex) {
            throw new IllegalArgumentException("IO failure", ex);
        }
    }

}
