/*
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 */

import com.jcabi.matchers.XhtmlMatchers
import org.hamcrest.MatcherAssert
import org.hamcrest.Matchers

def log = new File(basedir, 'build.log')
MatcherAssert.assertThat(
    log.text,
    Matchers.containsString(' requs error(s)')
)
def xml = new File(basedir, 'target/requs/requs.xml')
if (!xml.exists()) {
    throw new IllegalStateException(
        'XML was not generated at ' + xml
    )
}
MatcherAssert.assertThat(
    XhtmlMatchers.xhtml(xml.text),
    XhtmlMatchers.hasXPaths(
        '/spec/types/type[name="Fraction"]',
        '/spec/errors/error'
    )
)
