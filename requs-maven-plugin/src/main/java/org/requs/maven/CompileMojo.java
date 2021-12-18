/*
 * Copyright (c) 2009-2021, Yegor Bugayenko
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
import com.jcabi.xml.XML;
import com.jcabi.xml.XMLDocument;
import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import javax.validation.constraints.NotNull;
import lombok.EqualsAndHashCode;
import lombok.ToString;
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
@ToString
@EqualsAndHashCode
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
    public transient @NotNull File input;

    /**
     * Output directory.
     */
    @Parameter(
        required = true,
        defaultValue = "${project.build.directory}/requs"
    )
    public transient @NotNull File output;

    /**
     * Optional properties/options.
     * @since 1.14
     */
    @SuppressWarnings("PMD.UseConcurrentHashMap")
    @Parameter()
    public transient @NotNull Map<String, String> options =
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
